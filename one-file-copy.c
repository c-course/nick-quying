#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int foo()
{
    int fd, size;
    char str[] = "MaxWit!!!\n123213\n";
    char buffer[80];

    fd = open("newt", O_RDWR|O_CREAT, 0600);
    write(fd, str, 10);
    close(fd);

    fd = open("newt", O_RDWR);
    size = read(fd, buffer, 10);
    close(fd);

    fd = open("newt2", O_WRONLY|O_CREAT, S_IRWXU);
    write(fd, buffer, 3);
    close(fd);


    return 0;
}
