#include <stdio.h>

unsigned int pack_char(char ch1, char ch2) {
    unsigned int result = 0;
    result |= ch1;
    result <<= 8;
    result |= ch2;
    return result;
}

void print_binary(unsigned int num) {
    unsigned int mask = 1 << (sizeof(unsigned int) * 8 - 1);
    while (mask > 0) {
        if (num & mask)
            printf("1");
        else
            printf("0");
        mask >>= 1;
    }
    printf("\n");
}

int main(char *argv[], int argc) {
    if (argc < 3) {
        printf("Please provide two characters as command line arguments.\n");
        return 1;
    }

    char ch1 = argv[1][0];
    char ch2 = argv[2][0];

    unsigned int packed = pack_char(ch1, ch2);

    printf("Character 1: %c\n", ch1);
    printf("Character 2: %c\n", ch2);
    printf("Result (Decimal): %u\n", packed);
    printf("Result (Binary): ");
    print_binary(packed);

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    fprintf(outputFile, "Character 1: %c\n", ch1);
    fprintf(outputFile, "Character 2: %c\n", ch2);
    fprintf(outputFile, "Result (Decimal): %u\n", packed);
    fprintf(outputFile, "Result (Binary): ");
    unsigned int mask = 1 << (sizeof(unsigned int) * 8 - 1);
    while (mask > 0) {
        if (packed & mask)
            fprintf(outputFile, "1");
        else
            fprintf(outputFile, "0");
        mask = mask >> 1;
    }
    fprintf(outputFile, "\n");

    fclose(outputFile);

    return 0;
}
