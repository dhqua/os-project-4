#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int main (int argc , char* argv[])
{
    //if (arc )

    DIR * test;
    struct dirent * workingDir;

    //test = opendir("/home/t/thomasq/os_cop4600/project4/os-project-4");
    test = opendir("/home/t/thomasq/os_cop4600/project4");
    workingDir = readdir(test);
    while (workingDir != NULL)
    {
        printf("%s\n",workingDir->d_name);
        workingDir = readdir(test);
    }
    return 0;
}