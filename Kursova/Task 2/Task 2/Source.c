#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define size 100

void manualInput(); //ability to input N x N matrix by hand
void randomInput(); //ability to randomly input N x N matrix
void formVector(); //Form vector and shows difference in highest and lowest value by module
void displayArray(); //Show full array 

int main() {
    int array[size][size];
    int N, ch;

    srand(time(NULL));

    printf("Enter the size of the matrix (6 <= N <= 10): ");
    scanf("%d", &N);

    if (N < 6 || N > 10) { //Fail check
        printf("Invalid size....");
        return 1;
    }

    printf("Choose type of input ( 1- Manual, 2 - Random): ");
    scanf("%d", &ch);
    
    switch (ch) //option of input
    {
    case 1:manualInput(array, N);
        break;
    case 2:randomInput(array, N);
        break;
    default:printf("Invalid option.");
        return 1;
    }

    displayArray(array, N, ch);

    formVector(array, N);

    return 0;
}

void manualInput(int array[size][size], int N) {

    printf("Input array manually: \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf_s("%d", &array[i][j]); //Manual input of array
        }
    }   
}

void randomInput(int array[size][size], int N) {
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] = rand() % 201 - 100; // random fill of array from -100 to 200
        }
    }
}

void displayArray(int array[size][size], int N, int ch) {
    switch (ch) //Just to make sure what type of fill
    {
    case 1: printf("Manually inputed matrix: \n");
        break;
    case 2:printf("Randomly inputed matrix: \n");
        break;
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d | ", array[i][j]);
        }
        printf("\n");
    }
}

void formVector(int array[size][size], int N) {
    int diff[size];

    for (int i = 0; i < N; i++)
    {
        int min = array[i][0];
        int max = array[i][0];
        for (int j = 0; j < N; j++)
        {
            if (array[i][j] < min) {
                min = array[i][j];
            }
            if (array[i][j] > max) {
                max = array[i][j];
            }
        }
        diff[i] = max - min;
    }

    printf("Vector of differences of the largest and smallest values in each row:\n");

    printf("Value:");
    for (int i = 0; i < N; i++) {
        printf("%d ", diff[i]);
    }

    printf("\n");
}