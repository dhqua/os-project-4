#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

void printDirs(char * currDir, char * prefix);

int main (int argc , char* argv[])
{

    DIR * openedDir;
    struct dirent * workingDir;
    char * cwd = malloc(sizeof(char *) * PATH_MAX);
    int hasDirName = FALSE;

    // Handle command line arguments
    if(argc > 1 )
    {
        cwd = argv[1];
        hasDirName = TRUE;
    }

    // Stores current working directory in cwd string
    if(!hasDirName)
    {
        getcwd(cwd, PATH_MAX);
    }

    // openedDir = opendir(cwd);
    // workingDir = readdir(openedDir);

    // struct stat fileStat;
    // while (workingDir != NULL)
    // {
    //     if(workingDir->d_name[0] == '.')
    //     {
    //         workingDir = readdir(openedDir);
    //         continue;
    //     }

    //     printf("%s\n",workingDir->d_name);
    //     workingDir = readdir(openedDir);
    // }
    printDirs(cwd, "");

    return 0;
}

void printDirs(char * currDir, char * prefix)
{
    DIR * tempOpen = opendir(currDir);
    if(tempOpen == NULL)
        return;
    struct dirent * tempWorkDir = readdir(tempOpen);

    struct stat fileStat;
    while (tempWorkDir != NULL)
    {
        if(tempWorkDir->d_name[0] == '.')
        {
            tempWorkDir = readdir(tempOpen);
            continue;
        }

        printf("%s\n",tempWorkDir->d_name);
        char * tempPath = malloc(sizeof(char) * (strlen(currDir) + strlen(prefix) + 2));
        strcat(tempPath,currDir);
        strcat(tempPath,"/");
        strcat(tempPath,tempWorkDir->d_name);

        //printf("RESULT PATH: %s\n", tempPath);

        stat(tempPath, &fileStat);
        //If it is a directory, call the functon recursively
        // int tempFile = opendir(tempWorkDir->d_name, O_RDONLY);
        // if( tempFile )
        // {
            // struct dirent * newDir = read
            printDirs(tempPath, "");
        // }

        tempWorkDir = readdir(tempOpen);
    }

    return;
}
