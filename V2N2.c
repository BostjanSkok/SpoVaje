#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int GoToFirstLineToPrint(int sFd, int number)
{

    int linesWalked = 0;
    int offset = 0;
    int lastChar = -1;
    int endOfSource = lseek(sFd, 0, SEEK_END );
    while (linesWalked < number && offset <= endOfSource)
    {
        int ReadChar ;
        // printf("%i\n", offset);
        if (lseek(sFd, -offset, SEEK_END) == -1)
        {
            perror("Seek next char -- GoToFirstLineToPrint");
            exit(EXIT_FAILURE);
        }

        if (read(sFd, &ReadChar, 1) == -1)
        {
            perror("Read next char from source -- GoToFirstLineToPrint");
            exit(EXIT_FAILURE);
        }
       // printf("%c\n",ReadChar );
        if (ReadChar ==10 )
        {
           // printf("%s\n", "New line" );
            linesWalked++;
        }

        lastChar = ReadChar;
        offset++;
    }
   // printf("%i\n", offset);
   // printf("%i\n", endOfSource);


    return --offset;
}


void printTail(int number , char *sourceFile )
{
    int sFd; //source file

    sFd = open(sourceFile, O_RDONLY);
    if (sFd == -1) //open readonly
    {
        perror("open sourceFile");
        exit(EXIT_FAILURE);
    }


    int endOfSource = lseek(sFd, 0, SEEK_END );
    if ( endOfSource == -1)
    {
        perror("Seek end of file");
        exit(EXIT_FAILURE);
    }

    int offset = GoToFirstLineToPrint(sFd, number);

    for (offset; offset > 0 ; offset--)
    {
        //printf("%i\n", offset );

        int ReadChar ;

        if (lseek(sFd, -offset, SEEK_END) == -1)
        {
            perror("Seek next char -- printTail");
            exit(EXIT_FAILURE);
        }

        if (read(sFd, &ReadChar, 1) == -1)
        {
            perror("Read next char from source");
            exit(EXIT_FAILURE);
        }
        printf("%c", ReadChar);

    }
}

int main(int argc, char **argv)
{
    int numberOfLines = 5 ;
    char *sourceFile ;

    if (argc < 2)
    {
        fprintf(stderr, "Not enough params\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 3)
    {
        char str1[2];
        /* copy to sized buffer (overflow safe): */
        strncpy(str1, argv[1], sizeof(str1));
        //printf("%s", str1) ;
        //printf("%c\n",str1[0]);
        //printf("%c\n",str1[1]);

        if (str1[0] == '-' && str1[1]=='n')
        {
            char str2[2];
            strncpy(str2, argv[1] + 2, sizeof(str2));

            numberOfLines = atoi(str2);
          //  printf("%i", numberOfLines);

        }
        else
        {
            fprintf(stderr, "Invalid option \n");
            exit(EXIT_FAILURE);
        }

        sourceFile = argv[2];
    }
    else if (argc == 2)
    {
        sourceFile = argv[1];
    }

    printTail(numberOfLines, sourceFile);

    exit(EXIT_SUCCESS);
}