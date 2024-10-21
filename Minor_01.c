//Write C program to demonstrate all file operations related to system calls supported by Unix OS and C libraries for file operations
#include <stdio.h>
#include <string.h>

int main() {
    FILE *file;
    size_t bytesRead, bytesWritten;
    char buffer[100];

    // Open a file for reading and writing, create if it doesn't exist
    file = fopen("example.txt", "w+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write to the file
    const char *text = "Hello, UNIX file system!";
    bytesWritten = fwrite(text, sizeof(char), strlen(text), file);
    if (bytesWritten < strlen(text)) {
        perror("Error writing to file");
        fclose(file);
        return 1;
    }

    // Move the file pointer to the beginning
    if (fseek(file, 0, SEEK_SET) != 0) {
        perror("Error seeking in file");
        fclose(file);
        return 1;
    }

    // Read from the file
    bytesRead = fread(buffer, sizeof(char), sizeof(buffer) - 1, file);
    if (bytesRead == 0 && ferror(file)) {
        perror("Error reading from file");
        fclose(file);
        return 1;
    }

    // Null-terminate the buffer and print the content
    buffer[bytesRead] = '\0';
    printf("Read from file: %s\n", buffer);

    // Close the file
    if (fclose(file) != 0) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}
