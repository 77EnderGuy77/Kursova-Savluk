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
int compareDate(const void* a, const void* b);
void cocktailSort(Television* arr, int size);
void printTable(Television* tvArray, int size);
void saveToFile(Television* tvArray, int size, const char* filename);

int main(int argc, char* argv[]) {
    char filename[100];
    int fromFile = 0;

    if (argc > 1) {
        strncpy(filename, argv[1], sizeof(filename));
        fromFile = 1;
    }
    else {
        printf("Enter the filename (or leave it blank to input from keyboard): ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0';

        if (strlen(filename) > 0) {
            fromFile = 1;
        }
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


    if (fromFile) {
        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            printf("Failed to open the file.\n");
            free(tvArray);
            return 1;
        }

        for (int i = 0; i < size; i++) {
            fscanf(file, "%[^,], %[^,], %d, %f, %[^\n]%*c",
                tvArray[i].country, tvArray[i].brand, &tvArray[i].diagonalSize, &tvArray[i].price, tvArray[i].date);
        }

        fclose(file);
    }
    else {
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

            printf("Sale Date (dd-mm-yyyy): ");
            fgets(tvArray[i].date, sizeof(tvArray[i].date), stdin);
            tvArray[i].date[strcspn(tvArray[i].date, "\n")] = '\0';

            getchar(); // Clear the newline character from the input buffer
        }
    }

    printf("\nTV Sales Information:\n");
    printTable(tvArray, size);

    // Search TVs by diagonal size
    float searchDiagonal;
    printf("\nEnter the diagonal size to search for: ");
    scanf("%f", &searchDiagonal);

    // Sort TVs by date using cocktail sort
    int srt;
    printf("Do you want to sort information (1 - yes, 0 - no)?: ");
    scanf("%d", &srt);
    if (srt == 1) {
        qsort(tvArray, size, sizeof(Television), compareDate);
    }

    linearSearch(tvArray, size, searchDiagonal);

    // Print the table of TVs
    printf("\nTV Sales Information:\n");
    printTable(tvArray, size);

    if (fromFile) {
        char saveOption;
        printf("Do you want to save the table to a file? (Y/N): ");
        scanf(" %c", &saveOption);

        if (saveOption == 'Y' || saveOption == 'y') {
            char saveFilename[100];
            printf("Enter the filename to save the table: ");
            scanf("%s", saveFilename);
            saveToFile(tvArray, size, saveFilename);
        }
    }
    else {
        char saveOption;
        printf("Do you want to save the table to a file? (Y/N): ");
        scanf(" %c", &saveOption);

        if (saveOption == 'Y' || saveOption == 'y') {
            char saveFilename[100];
            printf("Enter the filename to save the table: ");
            scanf("%s", saveFilename);
            saveToFile(tvArray, size, saveFilename);
        }
    }

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

int compareDate(const void* a, const void* b) {
    const Television* tv1 = (const Television*)a;
    const Television* tv2 = (const Television*)b;

    int day1, month1, year1;
    int day2, month2, year2;

    sscanf(tv1->date, "%d-%d-%d", &day1, &month1, &year1);
    sscanf(tv2->date, "%d-%d-%d", &day2, &month2, &year2);

    if (year1 != year2)
        return year1 - year2;
    if (month1 != month2)
        return month1 - month2;
    return day1 - day2;
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
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Failed to open the file for writing.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s, %s, %d, %.2f, %s\n",
            tvArray[i].country, tvArray[i].brand, tvArray[i].diagonalSize, tvArray[i].price, tvArray[i].date);
    }

    fclose(file);
    printf("Table saved to %s.\n", filename);
}
