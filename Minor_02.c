//Write C program to demonstrate indexing and associated operations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "records.dat"
#define INDEXFILE "index.dat"

typedef struct {
    int id;
    char name[30];
    float score;
} Record;

typedef struct {
    int id;
    long position;
} Index;

void createRecord(FILE *file, FILE *indexFile) {
    Record record;
    printf("Enter ID: ");
    scanf("%d", &record.id);
    printf("Enter Name: ");
    scanf("%s", record.name);
    printf("Enter Score: ");
    scanf("%f", &record.score);

    fseek(file, 0, SEEK_END);
    long position = ftell(file);
    if (fwrite(&record, sizeof(Record), 1, file) != 1) {
        perror("Error writing record");
        return;
    }

    Index index;
    index.id = record.id;
    index.position = position;
    if (fwrite(&index, sizeof(Index), 1, indexFile) != 1) {
        perror("Error writing index");
        return;
    }

    printf("Record created successfully.\n");
}

void readRecord(FILE *file, FILE *indexFile) {
    int id;
    printf("Enter ID to read: ");
    scanf("%d", &id);

    Index index;
    fseek(indexFile, 0, SEEK_SET);
    while (fread(&index, sizeof(Index), 1, indexFile)) {
        if (index.id == id) {
            Record record;
            fseek(file, index.position, SEEK_SET);
            if (fread(&record, sizeof(Record), 1, file) != 1) {
                perror("Error reading record");
                return;
            }
            printf("ID: %d\nName: %s\nScore: %.2f\n", record.id, record.name, record.score);
            return;
        }
    }
    printf("Record with ID %d not found.\n", id);
}

void updateRecord(FILE *file, FILE *indexFile) {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    Index index;
    fseek(indexFile, 0, SEEK_SET);
    while (fread(&index, sizeof(Index), 1, indexFile)) {
        if (index.id == id) {
            Record record;
            fseek(file, index.position, SEEK_SET);
            if (fread(&record, sizeof(Record), 1, file) != 1) {
                perror("Error reading record");
                return;
            }

            printf("Enter new Name: ");
            scanf("%s", record.name);
            printf("Enter new Score: ");
            scanf("%f", &record.score);

            fseek(file, index.position, SEEK_SET);
            if (fwrite(&record, sizeof(Record), 1, file) != 1) {
                perror("Error updating record");
                return;
            }
            printf("Record updated successfully.\n");
            return;
        }
    }
    printf("Record with ID %d not found.\n", id);
}

void searchRecord(FILE *file) {
    char name[30];
    printf("Enter Name to search: ");
    scanf("%s", name);

    Record record;
    fseek(file, 0, SEEK_SET);
    while (fread(&record, sizeof(Record), 1, file)) {
        if (strcmp(record.name, name) == 0) {
            printf("ID: %d\nName: %s\nScore: %.2f\n", record.id, record.name, record.score);
            return;
        }
    }
    printf("Record with Name %s not found.\n", name);
}

int main() {
    FILE *file = fopen(FILENAME, "rb+");
    FILE *indexFile = fopen(INDEXFILE, "rb+");

    if (!file || !indexFile) {
        perror("Error opening file");
        return 1;
    }

    int choice;
    while (1) {
        printf("\n1. Create Record\n2. Read Record\n3. Update Record\n4. Search Record\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createRecord(file, indexFile);
                break;
            case 2:
                readRecord(file, indexFile);
                break;
            case 3:
                updateRecord(file, indexFile);
                break;
            case 4:
                searchRecord(file);
                break;
            case 5:
                fclose(file);
                fclose(indexFile);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}