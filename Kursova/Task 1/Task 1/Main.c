#include <stdio.h>

// Function to count the occurrences of a substring using array indexing
int quantity_indexed(char s[], char p[]) {
    int count = 0;
    int i, j;

    for (i = 0; s[i] != '\0'; i++) {
        // Check if the current character matches the first character of the substring
        if (s[i] == p[0]) {
            // Compare the remaining characters of the substring with the corresponding characters in the string
            for (j = 1; p[j] != '\0' && s[i + j] != '\0'; j++) {
                if (s[i + j] != p[j])
                    break;
            }

            // If the entire substring matches, increment the count and move the index accordingly
            if (p[j] == '\0') {
                count++;
                i += j - 1;
            }
        }
    }

    return count;
}

// Function to count the occurrences of a substring using pointers
int quantity_pointers(char* s, char* p) {
    int count = 0;
    char* s_ptr, * p_ptr;

    for (s_ptr = s; *s_ptr != '\0'; s_ptr++) {
        // Check if the current character matches the first character of the substring
        if (*s_ptr == *p) {
            // Compare the remaining characters of the substring with the corresponding characters in the string
            for (s_ptr++, p_ptr = p + 1; *p_ptr != '\0' && *s_ptr != '\0'; s_ptr++, p_ptr++) {
                if (*s_ptr != *p_ptr)
                    break;
            }

            // If the entire substring matches, increment the count
            if (*p_ptr == '\0') {
                count++;
            }
            
            s_ptr--;
            p_ptr--;
        }
    }

    return count;
}


int main() {
    char s[100], p[100];

    printf("Enter a string: ");
    fgets(s, sizeof(s), stdin);

    printf("Enter a substring: ");
    fgets(p, sizeof(p), stdin);

    // Removing the newline character from the input strings
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '\n') {
            s[i] = '\0';
            break;
        }
    }

    for (int i = 0; p[i] != '\0'; i++) {
        if (p[i] == '\n') {
            p[i] = '\0';
            break;
        }
    }

    // Counting the occurrences of the substring using both methods
    int count_indexed = quantity_indexed(s, p);
    int count_pointers = quantity_pointers(s, p);

    printf("Number of occurrences (indexed): %d\n", count_indexed);
    printf("Number of occurrences (pointers): %d\n", count_pointers);

    return 0;
}
