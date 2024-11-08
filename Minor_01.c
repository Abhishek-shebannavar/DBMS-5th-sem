//Write C program to demonstrate all file operations related to system calls supported by Unix OS and C libraries for file operations
#include <stdio.h>
#include <string.h>

int main() {
    FILE *file;
    size_t bytesRead, bytesWritten;
    char buffer[100], choice;

    // Open a file for reading and writing, create if it doesn't exist
    file = fopen("example.txt", "w+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Write to file\n");
        printf("2. Read from file\n");
        printf("3. Exit\n");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printf("Enter text to write: ");
                scanf(" %[^\n]", buffer);
                bytesWritten = fwrite(buffer, sizeof(char), strlen(buffer), file);
                if (bytesWritten < strlen(buffer)) {
                    perror("Error writing to file");
                    fclose(file);
                    return 1;
                }
                break;

            case '2':
                if (fseek(file, 0, SEEK_SET) != 0) {
                    perror("Error seeking in file");
                    fclose(file);
                    return 1;
                }
                bytesRead = fread(buffer, sizeof(char), sizeof(buffer) - 1, file);
                if (bytesRead == 0 && ferror(file)) {
                    perror("Error reading from file");
                    fclose(file);
                    return 1;
                }
                buffer[bytesRead] = '\0';
                printf("Read from file: %s\n", buffer);
                break;

            case '3':
                fclose(file);
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
