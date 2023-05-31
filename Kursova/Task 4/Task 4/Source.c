#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store TV information
typedef struct {
    char country[50];
    char brand[50];
    int diagonalSize;
    float price;
    char date[11]; // Assuming date format: "dd-mm-yyyy"
} Television;

// Function prototypes
void linearSearch(Television* tvArray, int size, float searchDiagonal);
void cocktailSort(Television* tvArray, int size);
void printTable(Television* tvArray, int size);
void saveToFile(Television* tvArray, int size, const char* filename);

int compareDiagonalSize(const void* a, const void* b) {
    const Television* tv1 = (const Television*)a;
    const Television* tv2 = (const Television*)b;
    return tv1->diagonalSize - tv2->diagonalSize;
}

int main(int argc, char* argv[]) {
    char filename[100];
    if (argc > 1) {
        strncpy(filename, argv[1], sizeof(filename));
    }
    else {
        printf("Enter the filename: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0';
    }

    int size;
    printf("Enter the number of TVs: ");
    scanf("%d", &size);
    getchar(); // Clear the newline character from the input buffer

    Television* tvArray = (Television*)malloc(size * sizeof(Television));
    if (tvArray == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        printf("\nEnter information for TV %d:\n", i + 1);
        printf("Country: ");
        fgets(tvArray[i].country, sizeof(tvArray[i].country), stdin);
        tvArray[i].country[strcspn(tvArray[i].country, "\n")] = '\0';

        printf("Brand: ");
        fgets(tvArray[i].brand, sizeof(tvArray[i].brand), stdin);
        tvArray[i].brand[strcspn(tvArray[i].brand, "\n")] = '\0';

        printf("Diagonal Size: ");
        scanf("%d", &tvArray[i].diagonalSize);
        getchar(); // Clear the newline character from the input buffer

        printf("Price: ");
        scanf("%f", &tvArray[i].price);
        getchar(); // Clear the newline character from the input buffer

        printf("Sale Date: ");
        fgets(tvArray[i].date, sizeof(tvArray[i].date), stdin);
        tvArray[i].date[strcspn(tvArray[i].date, "\n")] = '\0';

        getchar(); // Clear the newline character from the input buffer
    }


    // Search TVs by diagonal size
    float searchDiagonal;
    printf("\nEnter the diagonal size to search for: ");
    scanf("%f", &searchDiagonal);

    linearSearch(tvArray, size, searchDiagonal);

    // Sort TVs by diagonal size using qsort
    qsort(tvArray, size, sizeof(Television), compareDiagonalSize);

    // Print the table of TVs
    printf("\nTV Sales Information:\n");
    printTable(tvArray, size);

    // Save the table to a file
    saveToFile(tvArray, size, filename);

    // Free dynamically allocated memory
    free(tvArray);

    return 0;
}

void linearSearch(Television* tvArray, int size, float searchDiagonal) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (tvArray[i].diagonalSize == searchDiagonal && strcmp(tvArray[i].brand, "LG") == 0) {
            count++;
        }
    }
    printf("\nNumber of sold LG TVs with diagonal size %.2f: %d\n", searchDiagonal, count);
}

void cocktailSort(Television* arr, int size) {
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

void printTable(Television* tvArray, int size) {
    printf("\n-------------------------------------------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-15s | %-15s | %-15s |\n", "Country", "Brand", "Diagonal Size", "Price", "Sale Date");
    printf("-------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < size; i++) {
        printf("| %-15s | %-15s | %-15d | %-15.2f | %-15s |\n",
            tvArray[i].country, tvArray[i].brand, tvArray[i].diagonalSize, tvArray[i].price, tvArray[i].date);
    }

    printf("-------------------------------------------------------------------------------------------\n");
}

void saveToFile(Television* tvArray, int size, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open the file for writing.\n");
        return;
    }

    fprintf(file, "Country,Brand,Diagonal Size,Price,Sale Date\n");
    for (int i = 0; i < size; i++) {
        fprintf(file, "%s,%s,%d,%.2f,%s\n",
            tvArray[i].country, tvArray[i].brand, tvArray[i].diagonalSize, tvArray[i].price, tvArray[i].date);
    }

    fclose(file);
    printf("Table saved to %s.\n", filename);
}
