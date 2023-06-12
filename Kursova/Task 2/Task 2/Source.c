#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define size 100

void manualInput(); // Function to manually input N x N matrix
void randomInput(); // Function to randomly input N x N matrix
void formVector(); // Function to form a vector and calculate the difference between the highest and lowest values in each row
void displayArray(); // Function to display the full array

int main() {
    int array[size][size];
    int N, ch;

    srand(time(NULL));

    printf("Enter the size of the matrix (6 <= N <= 10): ");
    scanf_s("%d", &N);

    if (N < 6 || N > 10) { // Check for valid size
        printf("Invalid size....");
        return 1;
    }

    printf("Choose the type of input (1 - Manual, 2 - Random): ");
    scanf_s("%d", &ch);

    switch (ch) {
        case 1:
            manualInput(array, N);
            break;
        case 2:
            randomInput(array, N);
            break;
        default:
            printf("Invalid option.");
            return 1;
    }

    displayArray(array, N, ch);

    formVector(array, N);

    return 0;
}

void manualInput(int array[size][size], int N) {
    printf("Input array manually: \n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf_s("%d", &array[i][j]); // Manually input array elements
        }
    }   
}

void randomInput(int array[size][size], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] = rand() % 201 - 100; // Randomly fill array with values from -100 to 200
        }
    }
}

void displayArray(int array[size][size], int N, int ch) {
    switch (ch) {
        case 1:
            printf("\tManually inputted matrix: \n");
            break;
        case 2:
            printf("\tRandomly inputted matrix: \n");
            break;
    }
        printf("   | ");
    for (int g = 1; g <= N; g++) {
        printf("%3d | ", g);
    }
        printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%2d | ", i + 1);
        for (int j = 0; j < N; j++) {
            printf("%3d | ", array[i][j]); // Print array elements
        }
        printf("\n");
    }
}

void formVector(int array[size][size], int N) {
    int diff[size];

    for (int i = 0; i < N; i++) {
        int min = array[i][0];
        int max = array[i][0];
        for (int j = 0; j < N; j++) {
            if (array[i][j] < min) {
                min = array[i][j];
            }
            if (array[i][j] > max) {
                max = array[i][j];
            }
        }
        diff[i] = max - min; // Calculate the difference between the highest and lowest values in each row
    }

    printf("Vector of differences of the largest and smallest values in each row:\n");

    printf("Value:"); // Print the values of the vector
    for (int i = 0; i < N; i++) {
        printf("Row [%d]: %d, ", (i + 1), diff[i]);
    }

    printf("\n");
}
