#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


void WirteFileType(mode_t toConvert)
{
    if (S_ISDIR(toConvert))
        printf("d");
    /*else if(S_ISLNK(toConvert))
        printf("l");*/
    else if (S_ISCHR(toConvert))
        printf("c");
    else
        printf("-");

}
void WriteFilePerm(mode_t toConvert)
{
    printf( (toConvert & S_IRUSR) ? "r" : "-");
    printf( (toConvert & S_IWUSR) ? "w" : "-");
    printf( (toConvert & S_IXUSR) ? "x" : "-");
    /*  printf( (toConvert & S_IRGRP) ? "r" : "-");
      printf( (toConvert & S_IWGRP) ? "w" : "-");
      printf( (toConvert & S_IXGRP) ? "x" : "-");
      printf( (toConvert & S_IROTH) ? "r" : "-");
      printf( (toConvert & S_IWOTH) ? "w" : "-");
      printf( (toConvert & S_IXOTH) ? "x" : "-");*/

    printf(" ");
}

int main(int argc, char **argv)
{
    DIR *dp ;
    if ((dp = opendir(".")) == NULL)
    {
        perror("Can't open dir");
        exit(EXIT_FAILURE);
    }
    struct dirent *dirp;
    struct stat *buf = malloc(sizeof(struct stat));;
    while ((dirp = readdir(dp)) != NULL)
    {
        if (stat( dirp->d_name, buf) == -1)
        {
            printf("error getting stat for %s" , dirp->d_name);
            exit(EXIT_FAILURE);
        }

        WirteFileType(buf->st_mode);
        WriteFilePerm(buf->st_mode);
        // printf("%s ",buf->st_nlink);
        printf("%s\n", dirp->d_name);
    }

    closedir(dp);
    exit(EXIT_SUCCESS);
}