#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "handson12.txt";    
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    int fd = fileno(file); 
    
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        perror("Error getting file flags");
        fclose(file);
        return 1;
    }
    
    if (flags & O_RDONLY) {
        printf("File is opened in read-only mode.\n");
    } else if (flags & O_WRONLY) {
        printf("File is opened in write-only mode.\n");
    } else if (flags & O_RDWR) {
        printf("File is opened in read-write mode.\n");
    } else {
        printf("Unable to determine file opening mode.\n");
    }
    
    fclose(file); // Close the FILE* stream
    
    return 0;
}

