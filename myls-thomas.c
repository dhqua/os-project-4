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


//Prototype: functon prints the file permissions
// temp - path to the file to check
void printPerms (struct stat * temp);

int main (int argc , char* argv[])
{
    //Variable declarations
    DIR * openedDir;
    struct dirent * workingDir;
    char * cwd = malloc(sizeof(char *) * PATH_MAX);
    int hasLFlag = FALSE;
    int hasDirName = FALSE;
    // Stuct used to convert system time to readable tome
    struct tm local;

    // Handle command line arguments
    // checks for -l flag
    if(argc > 1 && strcmp(argv[1], "-l") == 0 )
    {
        hasLFlag = TRUE;
    }

    // Checks if user provides a path to a file and flips the flag
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
    //Defuaults to current work directory if no args passes
    if(!hasDirName)
    {
        getcwd(cwd, PATH_MAX);
    }

    // opens the directory
    openedDir = opendir(cwd);
    //Reads the entries of the directory
    workingDir = readdir(openedDir);

    struct stat fileStat;
    // Loops until the end of the directory
    while (workingDir != NULL)
    {
        // Skips the . and .. that are present in every directory
        if(workingDir->d_name[0] == '.')
        {
            workingDir = readdir(openedDir);
            continue;
        }

        // if he user provided -l flag print more info about the file
        // Extra info is stored in fileStart struct that was declared above
        if(hasLFlag)
        {
            stat(workingDir->d_name, &fileStat);
            printPerms(&fileStat);
            printf(" %d ", (int)fileStat.st_nlink);
            printf("%d ", fileStat.st_uid);
            printf("%d ", fileStat.st_gid);
            printf("%6d ", fileStat.st_size);
            char * accessDate = ctime(&fileStat.st_mtime);
            int size = strlen(accessDate) - 1;
            accessDate[size] = '\0';
            printf("%s ", accessDate);

        }

        // Print file name and move to next entry in the directory 
        printf("%s\n",workingDir->d_name);
        workingDir = readdir(openedDir);
    }
    return 0;
}

//Prints the permissions of a file
// temp - file struct that was filled by a call to stat()
void printPerms (struct stat * temp)
{

            //directory or link
            if( (temp->st_mode & S_IFMT) == S_IFDIR)
                printf("d");
            else if ( (temp->st_mode & S_IFMT) == S_IFLNK)
                printf("l");
            else
                printf("-");

            // User read
            if (temp->st_mode & S_IRUSR)
                printf("r");
            else
                printf("-");

            // User write
            if (temp->st_mode & S_IWUSR)
                printf("w");
            else
                printf("-");
            // User execute
            if ( (temp->st_mode & S_IXUSR ))
            {
                printf("x");
            }
            else
            {
                printf("-");
            }
            // Group read
            if (temp->st_mode & S_IRGRP)
                printf("r");
            else
                printf("-");
            // Group write
            if (temp->st_mode & S_IWGRP)
                printf("w");
            else
                printf("-");
            // Group execute 
            if ((temp->st_mode & S_IXGRP))
                printf("x");
            else
                printf("-");

            // Other read
            if (temp->st_mode & S_IROTH)
                printf("r");
            else
                printf("-");
            // Other write
            if (temp->st_mode & S_IWOTH)
                printf("w");
            else
                printf("-");
            // Other execute
            if ((temp->st_mode & S_IXOTH))
                printf("x");
            else
                printf("-");
}