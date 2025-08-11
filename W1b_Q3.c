#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_LEN 1000
#define WORD_LEN 50

// Convert string to lowercase
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Remove punctuation characters
void removePunctuation(char *str) {
    char temp[MAX_LEN];
    int j = 0;
    for (int i = 0; str[i]; i++) {
        if (isalnum((unsigned char)str[i]) || isspace((unsigned char)str[i])) {
            temp[j++] = str[i];
        }
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

int main() {
    char paragraph[MAX_LEN];
    char words[MAX_WORDS][WORD_LEN];
    int count[MAX_WORDS] = {0};
    int wordCount = 0;

    printf("Enter a paragraph:\n");
    fgets(paragraph, sizeof(paragraph), stdin);

    // Remove punctuation and convert to lowercase
    removePunctuation(paragraph);
    toLowerCase(paragraph);

    // Tokenize into words
    char *token = strtok(paragraph, " \t\n");
    while (token != NULL) {
        int found = -1;
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(words[i], token) == 0) {
                found = i;
                break;
            }
        }

        if (found != -1) {
            count[found]++;
        } else {
            strcpy(words[wordCount], token);
            count[wordCount] = 1;
            wordCount++;
        }

        token = strtok(NULL, " \t\n");
    }

    // Print word frequencies
    printf("\nWord frequencies:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s: %d\n", words[i], count[i]);
    }

    return 0;
}
