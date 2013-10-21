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

    int sFd; //source file
    int dFd; //destination file

    sFd = open(sourceFile, O_RDONLY);
    if (sFd == -1) //open readonly
    {
        perror("open sourceFile");
        exit(EXIT_FAILURE);
    }

    dFd = open(destiantionFile, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR);
    if (dFd == -1)
    {
        perror("open destiantionFile");
        exit(EXIT_FAILURE);
    }

    int endOfSource = lseek(sFd, 0, SEEK_END );
    if ( endOfSource == -1)
    {
        perror("Seek end of file");
        exit(EXIT_FAILURE);
    }


    int offset = 0;
    for (offset; offset <= endOfSource ; offset++)
    {
        int ReadChar ;

        if (lseek(sFd, -offset, SEEK_END) == -1)
        {
            perror("Seek next char");
            exit(EXIT_FAILURE);
        }

        if (read(sFd, &ReadChar, 1) == -1)
        {
            perror("Read next char from source");
            exit(EXIT_FAILURE);
        }

        if (write(dFd, &ReadChar, 1) == -1)
        {
            perror("Write next char to destination");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);

}