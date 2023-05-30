#include <stdio.h>
#include <string.h>

unsigned int pack_char(char c1, char c2) {
    unsigned int packed = 0;
    packed |= (unsigned int)(c1 & 0xFF);
    packed <<= 8;
    packed |= (unsigned int)(c2 & 0xFF);
    return packed;
}

void print_binary(unsigned int num) {
    for (int i = 31; i >= 0; i--) {
        unsigned int mask = 1u << i;
        putchar((num & mask) ? '1' : '0');
        if (i % 8 == 0)
            putchar(' ');
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <char1> <char2>\n", argv[0]);
        return 1;
    }

    char c1 = argv[1][0];
    char c2 = argv[2][0];

    unsigned int packed = pack_char(c1, c2);

    printf("Initial characters: %c %c\n", c1, c2);
    printf("Decimal representation: %u\n", packed);
    printf("Binary representation: ");
    print_binary(packed);
    printf("\n");

    return 0;
}
