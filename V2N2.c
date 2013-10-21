#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


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
        printf("%s", str1) ;

        if (str1 == "-n")
        {
            char str2[2];
            strncpy(str2, argv[1]+2, sizeof(str2));
            numberOfLines = atoi(str2);
        }
        else
        {
            fprintf(stderr, "Invalid option \n");
            exit(EXIT_FAILURE);
        }
        printf("%s\n", numberOfLines) ;
        printf("%s\n", argv[1]) ;

        sourceFile = argv[2];
    }
    else if (argc == 2)
    {
        sourceFile = argv[1];
    }



    exit(EXIT_SUCCESS);
}