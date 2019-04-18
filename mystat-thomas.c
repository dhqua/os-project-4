#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "Error, program on takes 1 argument, the path to the file!" << endl;
        return 1;
    }

    struct stat statBuffer;
    stat(argv[1], &statBuffer);

    cout << "File Size: " << statBuffer.st_size << endl;
    cout << "# of Blocks: " << statBuffer.st_blocks << endl;
    cout << "Link Count: " << statBuffer.st_nlink << endl;
    printf("File Permissions: %lo\n", (unsigned long)statBuffer.st_mode);
    cout <<  "File Permissions: ";
    // User read
    if (statBuffer.st_mode && S_IRUSR)
        cout << 'r';
    else
        cout << '-';

    // User write
    if (statBuffer.st_mode && S_IWUSR)
        cout << 'w';
    else
        cout << '-';
    // User execute
    if ( (statBuffer.st_mode && S_IXUSR ))
        cout << 'x';
    else
        cout << '-';
    // Group read
    if (statBuffer.st_mode && S_IRGRP)
        cout << 'r';
    else
        cout << '-';
    // Group write
    if (statBuffer.st_mode && S_IWGRP)
        cout << 'w';
    else
        cout << '-';
    // Group execute 
    if (statBuffer.st_mode && S_IXGRP)
        cout << 'x';
    else
        cout << '-';

    // Other read
    if (statBuffer.st_mode && S_IROTH)
        cout << 'r';
    else
        cout << '-';
    // Other write
    if (statBuffer.st_mode && S_IWOTH)
        cout << 'w';
    else
        cout << '-';
    // Other execute
    if (statBuffer.st_mode && S_IXOTH)
        cout << 'x';
    else
        cout << '-';

    cout << endl;
    cout << "File iNode: " << statBuffer.st_ino << endl;

    return 0;
}