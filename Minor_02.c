//Write C program to demonstrate indexing and associated operations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100

struct Record {
    int id;
    char name[50];
    int age;
};

struct IndexEntry {
    int id;
    long offset;
};

int main() {
    struct Record records[MAX_RECORDS];
    struct IndexEntry index[MAX_RECORDS];
    int numRecords = 0;
    FILE *fp;
    int choice;

    while (1) {
        printf("\n1. Add Record\n");
        printf("2. Create Index\n");
        printf("3. Search Record by ID\n");
        printf("4. Display All Records\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (numRecords >= MAX_RECORDS) {
                    printf("Error: Maximum number of records reached.\n");
                    break;
                }

                printf("Enter ID: ");
                scanf("%d", &records[numRecords].id);
                printf("Enter Name: ");
                scanf("%s", records[numRecords].name);
                printf("Enter Age: ");
                scanf("%d", &records[numRecords].age);

                numRecords++;
                break;

            case 2:
                fp = fopen("records.dat", "wb");
                if (fp == NULL) {
                    perror("Error opening file");
                    return 1;
                }

                for (int i = 0; i < numRecords; i++) {
                    index[i].id = records[i].id;
                    index[i].offset = ftell(fp);
                    fwrite(&records[i], sizeof(struct Record), 1, fp);
                }

                fclose(fp);
                printf("Index created successfully.\n");
                break;

            case 3:
                if (numRecords == 0) {
                    printf("Error: No records to search.\n");
                    break;
                }

                int searchID, found = 0;
                printf("Enter ID to search: ");
                scanf("%d", &searchID);

                for (int i = 0; i < numRecords; i++) {
                    if (index[i].id == searchID) {
                        fp = fopen("records.dat", "rb");
                        if (fp == NULL) {
                            perror("Error opening file");
                            return 1;
                        }

                        fseek(fp, index[i].offset, SEEK_SET);
                        fread(&records[i], sizeof(struct Record), 1, fp);
                        fclose(fp);

                        printf("Record found: ID = %d, Name = %s, Age = %d\n", records[i].id, records[i].name, records[i].age);
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("Record not found.\n");
                }

                break;

            case 4:
                if (numRecords == 0) {
                    printf("Error: No records to display.\n");
                    break;
                }

                printf("ID\tName\tAge\n");
                printf("---------------------\n");
                for (int i = 0; i < numRecords; i++) {
                    printf("%d\t%s\t%d\n", records[i].id, records[i].name, records[i].age);
                }
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}