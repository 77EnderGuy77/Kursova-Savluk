#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUNTRY_LENGTH 50
#define MAX_BRAND_LENGTH 50

typedef struct {
    char country[MAX_COUNTRY_LENGTH];
    char brand[MAX_BRAND_LENGTH];
    int diagonalSize;
    float price;
    char date[11]; // Assuming date format: "yyyy-mm-dd"
} Television;

int compareDiagonalSize(const void* a, const void* b) {
    const Television* tv1 = (const Television*)a;
    const Television* tv2 = (const Television*)b;
    return tv1->diagonalSize - tv2->diagonalSize;
}

void shakerSort(Television* arr, int size) {
    int left = 0;
    int right = size - 1;
    int swapped = 0;

    do {
        swapped = 0;

        for (int i = left; i < right; i++) {
            if (strcmp(arr[i].date, arr[i + 1].date) > 0) {
                Television temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped) break;

        right--;

        for (int i = right; i > left; i--) {
            if (strcmp(arr[i - 1].date, arr[i].date) > 0) {
                Television temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = 1;
            }
        }

        left++;
    } while (swapped);
}

int countLgTelevisions(Television* arr, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].brand, "LG") == 0) {
            count++;
        }
    }
    return count;
}

int linearSearchByDiagonalSize(Television* arr, int size, int targetSize) {
    for (int i = 0; i < size; i++) {
        if (arr[i].diagonalSize == targetSize) {
            return i;
        }
    }
    return -1;
}

int binarySearchByDiagonalSize(Television* arr, int size, int targetSize) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid].diagonalSize == targetSize) {
            return mid;
        }

        if (arr[mid].diagonalSize < targetSize) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}

void printTable(Television* arr, int size) {
    printf("Country\t\tBrand\t\tDiagonal Size\tPrice\t\tDate\n");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < size; i++) {
        printf("%s %s %d\" %.2f %s",
            arr[i].country, arr[i].brand, arr[i].diagonalSize, arr[i].price, arr[i].date);
    }
}

void writeTableToFile(Television* arr, int size, const char* filename) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "Country\t\tBrand\t\tDiagonal Size\tPrice\t\tDate\n");
    fprintf(file, "---------------------------------------------------------------\n");

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s\t\t%s\t\t%d\"\t\t%.2f\t\t%s\n",
            arr[i].country, arr[i].brand, arr[i].diagonalSize, arr[i].price, arr[i].date);
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    char filename[100];
    int size;

    if (argc > 1) {
        strcpy(filename, argv[1]);
    }
    else {
        printf("Enter the file name: ");
        scanf("%s", filename);
    }

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Enter the number of televisions: ");
    scanf("%d", &size);

    Television* televisions = (Television*)malloc(size * sizeof(Television));

    if (televisions == NULL) {
        printf("Memory allocation failed!\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < size; i++) {
        fscanf(file, "%s %s %d %f %s",
            televisions[i].country, televisions[i].brand, &televisions[i].diagonalSize,
            &televisions[i].price, televisions[i].date);
    }

    fclose(file);

    shakerSort(televisions, size);

    printf("Table of televisions:\n");
    printTable(televisions, size);

    printf("\nNumber of LG televisions sold in the last three months: %d\n",
        countLgTelevisions(televisions, size));

    int targetSize;
    printf("\nEnter the diagonal size to search: ");
    scanf("%d", &targetSize);

    int linearIndex = linearSearchByDiagonalSize(televisions, size, targetSize);
    int binaryIndex = binarySearchByDiagonalSize(televisions, size, targetSize);

    if (linearIndex != -1) {
        printf("\nLinear Search: Television with diagonal size %d found at index %d\n",
            targetSize, linearIndex);
    }
    else {
        printf("\nLinear Search: Television with diagonal size %d not found\n", targetSize);
    }

    if (binaryIndex != -1) {
        printf("Binary Search: Television with diagonal size %d found at index %d\n",
            targetSize, binaryIndex);
    }
    else {
        printf("Binary Search: Television with diagonal size %d not found\n", targetSize);
    }

    writeTableToFile(televisions, size, "output.txt");

    free(televisions);

    return 0;
}
