#include <stdio.h>
#include <stdlib.h>

void swap_words(char** words, int index_word_1, int index_word_2);
int is_bigger(char* pointer_word_1, char* pointer_word_2, int position);
char** sort(int number_words, char** words, int position);

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Insufficient arguments\n");
        return -1;
    }

    int position = atoi(*(argv + 1));
    char** sorted_words = sort(argc - 2, argv + 2, position);
    for (int i = 0; i < argc - 2; ++i) {
        printf("%s\n", *(sorted_words + i));
    }

    free(sorted_words);

    return 0;
}


void swap_words(char** words, int index_word_1, int index_word_2) {
    char* temp = *(words + index_word_1);
    *(words + index_word_1) = *(words + index_word_2);
    *(words + index_word_2) = temp;
}

int is_bigger(char* pointer_word_1, char* pointer_word_2, int position) {
    char char_word_1 = *(pointer_word_1 + position);
    char char_word_2 = *(pointer_word_2 + position);
    if (char_word_1 != char_word_2) {
        return char_word_1 > char_word_2;
    }
    return 0;
}

char** sort(int number_words, char** words, int position) {
    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < number_words - 1; ++i) {
            if (is_bigger(*(words + i), *(words + i + 1), position)) {
                swap_words(words, i, i + 1);
                sorted = 0;
            }
        }
        --number_words;
    }
    return words;
}
