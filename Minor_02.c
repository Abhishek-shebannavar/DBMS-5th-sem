//Write C program to demonstrate indexing and associated operations
#include <stdio.h>

#define MAX 100

void display(int arr[], int size) {
    printf("Array elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void addElement(int arr[], int size, int element) {
    if (size < MAX) {
        arr[size] = element;
        size++;
    } else {
        printf("Array is full, cannot add more elements.\n");
    }
}

void deleteElement(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    } else {
        printf("Invalid index, cannot delete element.\n");
    }
}

void modifyElement(int arr[], int size, int index, int newValue) {
    if (index >= 0 && index < size) {
        arr[index] = newValue;
    } else {
        printf("Invalid index, cannot modify element.\n");
    }
}

int main() {
    int arr[MAX];
    int size = 0;
    int choice, element, index, newValue;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Element\n");
        printf("2. Delete Element\n");
        printf("3. Modify Element\n");
        printf("4. Display Elements\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to add: ");
                scanf("%d", &element);
                addElement(arr, size, element);
                size++;  // Update size after adding element
                break;
            case 2:
                printf("Enter index to delete: ");
                scanf("%d", &index);
                deleteElement(arr, size, index);
                size--;  // Update size after deleting element
                break;
            case 3:
                printf("Enter index to modify: ");
                scanf("%d", &index);
                printf("Enter new value: ");
                scanf("%d", &newValue);
                modifyElement(arr, size, index, newValue);
                break;
            case 4:
                display(arr, size);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}