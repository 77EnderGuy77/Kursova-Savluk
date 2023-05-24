#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_MIN 6
#define N_MAX 10

void manualInput(int arr[N_MAX][N_MAX], int n) {
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf_s("%d", &arr[i][j]);
        }
    }
}

void randomFill(int arr[N_MAX][N_MAX], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = rand() % 10; // Generate random numbers between 0 and 9
        }
    }
}

void printMatrix(int arr[N_MAX][N_MAX], int n) {
    printf("Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d |", arr[i][j]);
        }
        printf("\n");
    }
}
void replaceZeros(int arr[N_MAX][N_MAX], int n) {
    int endRow = n - 1;
    int endCol;

    if (n % 2 == 0) {
        endCol = n / 2 - 1;
    }
    else {
        endCol = n / 2;
    }
    for (int i = 1; i < endRow; i++) {
        for (int j = 0; j < endCol; ++j) {
            if (i >= j) {
                arr[i][j] = 0;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the size of the matrix (6 <= N <= 10): ");
    scanf_s("%d", &n);

    if (n < N_MIN || n > N_MAX) {
        printf("Invalid matrix size. Please enter a value between %d and %d.\n", N_MIN, N_MAX);
        return 1;
    }

    int matrix[N_MAX][N_MAX];

    printf("Choose an option:\n");
    printf("1. Manual input\n");
    printf("2. Random fill\n");

    int option;
    scanf_s("%d", &option);

    switch (option) {
    case 1:
        manualInput(matrix, n);
        break;
    case 2:
        randomFill(matrix, n);
        break;
    default:
        printf("Invalid option. Exiting...\n");
        return 1;
    }

    printf("\n");
    printMatrix(matrix, n);

    replaceZeros(matrix, n);

    printf("\n");
    printf("Matrix after replacing zeros in the left sector:\n");
    printMatrix(matrix, n);

    return 0;
}
