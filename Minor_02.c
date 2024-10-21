//Write C program to demonstrate indexing and associated operations
#include <stdio.h>

int main() {
    // Declare and initialize an array
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    // Accessing array elements using indexing
    printf("First element: %d\n", numbers[0]);
    printf("Third element: %d\n", numbers[2]);
    printf("Last element: %d\n", numbers[size - 1]);

    // Modifying array elements using indexing
    numbers[1] = 25;
    numbers[3] = 45;

    // Iterating through the array and printing elements
    printf("Array elements after modification:\n");
    for (int i = 0; i < size; i++) {
        printf("Element at index %d: %d\n", i, numbers[i]);
    }

    return 0;
}
