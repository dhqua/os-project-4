#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#define TRUE 1
#define FALSE 0

int main (int argc , char* argv[])
{
    //if (arc )

    DIR * openedDir;
    struct dirent * workingDir;
    char * cwd = malloc(sizeof(char *) * PATH_MAX);
    int hasLFlag = FALSE;
    int hasDirName = FALSE;

    // Handle command line arguments
    if(argc > 1 && strcmp(argv[1], "-l") == 0 )
    {
        hasLFlag = TRUE;
    }

    if(hasLFlag && argc > 2 && (argv[2] != NULL) )
    {
        cwd = argv[2];
        hasDirName = TRUE;
    }

    if(argc > 1 && !hasLFlag && (argv[1] != NULL))
    {
        cwd = argv[1];
        hasDirName = TRUE;
    }

    // Stores current working directory in cwd string
    if(!hasDirName)
    {
        getcwd(cwd, PATH_MAX);
    }

    //test = opendir("/home/t/thomasq/os_cop4600/project4/os-project-4");
    openedDir = opendir(cwd);
    workingDir = readdir(openedDir);
    while (workingDir != NULL)
    {
        printf("%s\n",workingDir->d_name);
        workingDir = readdir(openedDir);
    }
    return 0;
}