#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Error, program on takes 1 argument, the path to the file!\n" );
        return 1;
    }

    struct stat statBuffer;
    stat(argv[1], &statBuffer);

    printf("File Size: %d\n" , (int)statBuffer.st_size );
    printf("# of Blocks: %d\n" , (int)statBuffer.st_blocks );
    printf("Link Count: %d\n" , (int)statBuffer.st_nlink );
    printf("File Permissions: %lo\n", (unsigned long)statBuffer.st_mode);
    printf( "File Permissions: ");
    // User read
    if (statBuffer.st_mode && S_IRUSR)
        printf("r");
    else
        printf("-");

    // User write
    if (statBuffer.st_mode && S_IWUSR)
        printf("w");
    else
        printf("-");
    // User execute
    if ( (statBuffer.st_mode && S_IXUSR ))
        printf("x");
    else
        printf("-");
    // Group read
    if (statBuffer.st_mode && S_IRGRP)
        printf("r");
    else
        printf("-");
    // Group write
    if (statBuffer.st_mode && S_IWGRP)
        printf("w");
    else
        printf("-");
    // Group execute 
    if (statBuffer.st_mode && S_IXGRP)
        printf("x");
    else
        printf("-");

    // Other read
    if (statBuffer.st_mode && S_IROTH)
        printf("r");
    else
        printf("-");
    // Other write
    if (statBuffer.st_mode && S_IWOTH)
        printf("w");
    else
        printf("-");
    // Other execute
    if (statBuffer.st_mode && S_IXOTH)
        printf("x");
    else
        printf("-");

    printf("\nFile iNode: %d\n" , statBuffer.st_ino );

    return 0;
}