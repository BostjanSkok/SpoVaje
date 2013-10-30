#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

void WriteNTimes(int n , char *ToWriteStr , int fileNum)
{
    FILE *fp;

    char *fileName =  fileNum == 1 ? "izhod1.txt" : "izhod2.txt";
    char buf[10];
    char buf2[100];

    if ((fp = fopen(fileName, "w")) == NULL)
    {
        perror("file open failed");
        exit(EXIT_FAILURE);
    }
    printf(" sizeof buffer %i\n", fileNum == 1 ? sizeof(buf) : sizeof(buf2) );
    if (setvbuf(fp, fileNum == 1 ? buf : buf2, _IOFBF, fileNum == 1 ? sizeof(buf) : sizeof(buf2)) != 0)
    {
        perror("error setting file write buffer");
        exit(EXIT_FAILURE);

    }
    int i = 1;
    for (i; i <= n ; i++) //( fileNum==1?100: n)
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
    int nTimes = 100000;
    clock_t start = clock();
    WriteNTimes(nTimes, "Test for fprint to file extra long 100000000000000000000000000000000000000000000000", 1);
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Buffer %i written %i lines in %f seconds \n", 10, nTimes, seconds);



    start = clock();
    WriteNTimes(nTimes, "Test for fprint to file extra long 100000000000000000000000000000000000000000000000", 2);
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Buffer %i written %i lines in %f seconds  \n", 100, nTimes, seconds);
    exit(EXIT_SUCCESS);
}