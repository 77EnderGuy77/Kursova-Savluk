#include "Header.h"

void paste(char* s, const char* s1, int n) {
    int len = strlen(s);
    int len1 = strlen(s1);

    if (n < 0 || n > len)
    {
        printf("Invalid position.\n");
        return;
    }

    int newLen = len + len1;
    char* temp_s = (char*)malloc((newLen + 1) * sizeof(char));  // Cast the result of malloc to char*

    // Copy the main_s string up to position n into the new string
    strncpy(temp_s, s, n);
    temp_s[n] = '\0';

    // Append the sub_s substring to the new string
    strcat(temp_s, s1);

    // Append the rest of the main_s string after position n
    strcat(temp_s, s + n);

    // Copy the modified string back to s
    strcpy(s, temp_s);

    free(temp_s);
}

int Num2() {
    char main_s[100];
    char sub_s[50];
    int pos;

    printf("Enter the main string: ");
    scanf("%s", main_s);  // Remove & operator for arrays when using scanf

    printf("Enter the substring to insert: ");
    scanf("%s", sub_s);  // Remove & operator for arrays when using scanf

    printf("Enter the position to insert at: ");
    scanf("%d", &pos);

    paste(main_s, sub_s, pos);

    printf("Modified string: %s\n", main_s);

    return 0;
}
