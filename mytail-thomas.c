#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{

    if(argc != 3)
    {
        printf("Wrong number of arguments!\n");
        return 1;
    }

    char * num = argv[1];
    num = num + 1;

    char * fileName = argv[2];


    struct stat statBuffer;
    stat(fileName, &statBuffer);

    int fileSize = (int)statBuffer.st_size;
    

    int fileOpen = open(fileName, O_RDONLY);
    lseek(fileOpen, 1, SEEK_END);

    int lineCount = 0;
    int count = 0;
    char buffer[1];
    
    while(lineCount < atoi(num) )
    {
        read(fileOpen, buffer, 1);
        count++;
        if(*buffer == '\n')
            lineCount++;
        // subtract 2 so that the read goes backwards
        // An incremenet of 1 is builts into read
        lseek(fileOpen, -2, SEEK_CUR);

    }

    if(atoi(num) > fileSize)
    {
        char * maxResult[fileSize];
        read(fileOpen, maxResult, fileSize);
        printf("%s\n", maxResult);
        return 0;
    }


    char * result = malloc(sizeof(char *) * count);
    lseek(fileOpen, 1, SEEK_CUR);
    read(fileOpen, result, count);
    // Trim newlines at the top of file
    while(*result == '\n')
    {
        result++;
    }
    printf("%s\n", result);

    close(fileOpen);

    return 0;
}

