#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {

        return -1;
    }

    int fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0)
    {

        perror(argv[1]);

        return -1;
    }

    struct stat info;
    if (fstat(fd_in, &info) < 0)
    {

        perror("Error stating input file");

        return -1;
    }

    void *addr_in = mmap(0, info.st_size, PROT_READ, MAP_SHARED, fd_in, 0);

    if (addr_in == MAP_FAILED)
    {
        perror("Error mapping input file");
        return -1;
    }

    char *asChar = (char *)addr_in;
    int dataSize = info.st_size / sizeof(asChar[0]);

    for (int i = 0; i < dataSize; i++)
    {
        if (asChar[i] == 'X')
        {
            printf("Success! X was found. \n");
            return 0;
        }
    }
    printf("Failure! X was not found. \n");
    return 0;
}