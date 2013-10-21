#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int main(int argc, char **argv)
{

    if (argc != 3)
    {
        fprintf(stderr, "Not enough params\n");
        exit(EXIT_FAILURE);
    }

    char *sourceFile = argv[1];
    char *destiantionFile = argv[2];

    int sFd;
    int dFd;

    sFd = open(sourceFile, O_RDONLY );
    perror("open sourceFile");
    dFd = open(destiantionFile, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR);
    perror("open destiantionFile");

    int ReadChar ;
    int endOfSource = lseek(sFd, 0, SEEK_END );
    int offset = 0;
    for (offset; offset <= endOfSource ; offset++)
    {
        lseek(sFd,-offset, SEEK_END);
        read(sFd, &ReadChar, 1);
        write(dFd, &ReadChar, 1);
    }









}