#include "Header.h"

void paste_num2(char* s, const char* s1, int n) {
    int len = strlen(s);
    int len1 = strlen(s1);

    if (n < 0 || n > len)
    {
        printf("Invalid position.\n");
        return;
    }

    int newLen = len + len1;
    char* temp_s = (char*)malloc((newLen + 1) * sizeof(char));

    strncpy(temp_s, s, n);
    temp_s[n] = '\0';

    strcat(temp_s, s1);

    strcat(temp_s, s + n);

    strcpy(s, temp_s);

    free(temp_s);
}

void Num2() {
    char main_s[100];
    char sub_s[50];
    int pos;

    printf("Enter the main string: ");
    scanf("%s", main_s);

    printf("Enter the substring to insert: ");
    scanf("%s", sub_s);

    printf("Enter the position to insert at: ");
    scanf("%d", &pos);

    paste_num2(main_s, sub_s, pos);

    printf("Modified string: %s\n", main_s);
}
