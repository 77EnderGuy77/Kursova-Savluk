#include "Header.h"

void paste_num1(char s[], char s1[], int n) {
    int i, j;
    int len1 = strlen(s1);
    int len = strlen(s);
    if (n > len) {
        printf("Error: position n is out of bounds.\n");
        return;
    }
    if (len + len1 >= sizeof(s)) {
        printf("Error: the resulting string is too long.\n");
        return;
    }
    for (i = len; i >= n; i--) {
        s[i + len1] = s[i];
    }
    for (j = 0; j < len1; j++) {
        s[n + j] = s1[j];
    }
}

void Num1() {
    char s[100], s1[100];
    int n;

    printf("Enter a string: ");
    scanf("%s", s);
    s[strcspn(s, "\n")] = 0;

    printf("Enter a string to paste: ");
    scanf("%s", s1);
    s1[strcspn(s1, "\n")] = 0;

    printf("Enter a position to paste: ");
    scanf_s("%d", &n);

    paste_num1(s, s1, n);

    printf("Resulting string: %s\n", s);
}