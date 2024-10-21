#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    ssize_t bytesRead, bytesWritten;
    char buffer[100];

    // Open a file for reading and writing, create if it doesn't exist
    fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Write to the file
    const char *text = "Hello, UNIX file system!";
    bytesWritten = write(fd, text, strlen(text));
    if (bytesWritten == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Move the file pointer to the beginning
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error seeking in file");
        close(fd);
        return 1;
    }

    // Read from the file
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }

    // Null-terminate the buffer and print the content
    buffer[bytesRead] = '\0';
    printf("Read from file: %s\n", buffer);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}
