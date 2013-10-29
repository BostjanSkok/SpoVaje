#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

void WriteNTimes(int n , char *buf, char *ToWriteStr , int fileNum)
{
    FILE *fp;

    char *fileName =  fileNum == 1 ? "izhod1.txt" : "izhod2.txt";
    if ((fp = fopen(fileName, "w")) == NULL)
    {
        perror("file open failed");
        exit(EXIT_FAILURE);
    }
    if (setvbuf(fp, buf, _IOFBF, sizeof(buf)) != 0)
    {
        perror("error setting file write buffer");
        exit(EXIT_FAILURE);

    }
    int i = 1;
    for (i; i <= 100; i++)
    {
        if (fprintf( fp, "%s \n", ToWriteStr) < 0)
        {
            perror("error when writing to file");
            exit(EXIT_FAILURE);
        }
    }

    if (fclose(fp) == EOF)
    {
        perror("error closing file");
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char **argv)
{
	char buf[10];
    WriteNTimes(100,buf,"Test for fprint to file",1);
    exit(EXIT_SUCCESS);
}