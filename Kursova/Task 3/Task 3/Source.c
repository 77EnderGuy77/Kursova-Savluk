#include <stdio.h>

// Function to pack two characters into one unsigned int
unsigned int pack_char(char c1, char c2) {
    unsigned int result = 0;
    result |= (unsigned int)c1;
    result <<= 8;  // Shift left by 8 bits 
    result |= (unsigned int)c2;
    return result;
}

// Function to display a binary representation with leading zeros
void print_binary(unsigned int num, int total_bits, FILE* file) {
    for (int i = total_bits - 1; i >= 0; i--) {
        unsigned int bit = (num >> i) & 1;
        fprintf(file, "%u", bit);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./program_name input_file output_file\n");
        return 1;
    }

    char* input_file = argv[1];
    char* output_file = argv[2];

    FILE* input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    FILE* output = fopen(output_file, "w");
    if (output == NULL) {
        printf("Failed to open the output file.\n");
        fclose(input);
        return 1;
    }

    char c1, c2;
    if (fscanf(input, "%c %c", &c1, &c2) != 2) {
        printf("Failed to read input characters.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    unsigned int packed = pack_char(c1, c2);

    printf("Initial characters: %c %c\n", c1, c2);
    printf("Decimal representation: %u\n", packed);
    printf("Binary representation: ");
    print_binary(packed, sizeof(packed) * 4, stdout);  // Print on screen

    printf("\n");

    fprintf(output, "Initial characters: %c %c\n", c1, c2);
    fprintf(output, "Decimal representation: %u\n", packed);
    fprintf(output, "Binary representation: ");
    print_binary(packed, sizeof(packed) * 4, output);  // Print into the file

    fprintf(output, "\n");

    if (fclose(input) == EOF) {
        printf("Failed to close the input file.\n");
        return 1;
    }

    if (fclose(output) == EOF) {
        printf("Failed to close the output file.\n");
        return 1;
    }

    return 0;
}
