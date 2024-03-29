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
    // Gets rid of the '-'
    num = num + 1;


    // Gets info on the file passed as an argument
    char * fileName = argv[2];
    struct stat statBuffer;
    stat(fileName, &statBuffer);
    int fileSize = (int)statBuffer.st_size;
    
    // Open the file and set the cursor to the end
    int fileOpen = open(fileName, O_RDONLY);
    lseek(fileOpen, -1, SEEK_END);

    int lineCount = 0;
    int count = 0;
    char buffer[1];
    off_t resultOffset;

    while(read(fileOpen, buffer, 1) )
    {
        //Counts chars and '\n' as we read
        count++;
        if(*buffer == '\n')
            lineCount++;

        // subtract 2 so that the read goes backwards
        // An incremenet of 1 is builts into read
        resultOffset = lseek(fileOpen, -2, SEEK_CUR);
        
        //Stop reading once we reach the passed number of lines
        if(lineCount == atoi(num) + 1)
            break;

        if(count >= fileSize)
            break;
    }

    // Handles the case where n is greater than lines in the file
    if(count >= fileSize)
    {
        char * maxResult[fileSize * 2];
        lseek(fileOpen, 0, SEEK_SET);
        read(fileOpen, maxResult, fileSize + 2);
        close(fileOpen);
        printf("%s\n", maxResult);
        return 0;
    }


    char * result = malloc(sizeof(char) * count * 2);
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

