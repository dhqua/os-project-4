#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sysmacros.h>


int main(int argc, char* argv[])
{
    // Check command line args
    // Correct Usage: ./mystat fileName
    if(argc != 2)
    {
        printf("Error, program on takes 1 argument, the path to the file!\n" );
        return 1;
    }

    // Call stat interface to get more info on a file
    struct stat statBuffer;
    stat(argv[1], &statBuffer);

    //Print necessary info,saved in statBuffer by call to stat=()
    printf("File Size: %d\n" , (int)statBuffer.st_size );
    printf("# of Blocks: %d\n" , (int)statBuffer.st_blocks );
    printf("Link Count: %d\n" , (int)statBuffer.st_nlink );
    printf( "File Permissions: ");


    //---------------------------
    // Print file permissions
    //---------------------------

    //directory or link
    if( (statBuffer.st_mode & S_IFMT) == S_IFDIR)
        printf("d");
    else if ( (statBuffer.st_mode & S_IFMT) == S_IFLNK)
        printf("l");
    else
        printf("-");

    // User read
    if (statBuffer.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");

    // User write
    if (statBuffer.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");
    // User execute
    if ( (statBuffer.st_mode & S_IXUSR ))
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
    // Group read
    if (statBuffer.st_mode & S_IRGRP)
        printf("r");
    else
        printf("-");
    // Group write
    if (statBuffer.st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");
    // Group execute 
    if ((statBuffer.st_mode & S_IXGRP))
        printf("x");
    else
        printf("-");

    // Other read
    if (statBuffer.st_mode & S_IROTH)
        printf("r");
    else
        printf("-");
    // Other write
    if (statBuffer.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");
    // Other execute
    if ((statBuffer.st_mode & S_IXOTH))
        printf("x");
    else
        printf("-");

    printf("\nFile iNode: %d\n" , statBuffer.st_ino );

    return 0;
}