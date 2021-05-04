# lager

## Compilation
### Build
Clone the repository and run:

    # make

To insert the module into the kernel, run:

    # sudo insmod lager.ko

To unload the module (and clear the logs), run:

    # sudo rmmod lager


## Usage
To view the pressed keys, run:

```
# sudo cat /sys/kernel/debug/lager/keys

```


