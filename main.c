#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "single_count.h"
#include "bigram.h"
#include "trigram.h"

int main() {
    char filename[80];
    char outfilename[80];
    int single_count[ALPHABET_SIZE] = {0};
    int bigram_counts[ALPHABET_SIZE][ALPHABET_SIZE] = {0};
    int trigram_counts [ALPHABET_SIZE][ALPHABET_SIZE][ALPHABET_SIZE] = {0};


    printf("Please enter name of encrypted file: ");
    scanf("%s", filename);

    printf("Please enter the name of the file to print the cipher output: ");
    scanf("%s", outfilename);

    single_count_funct(filename, single_count);
    desc_print(outfilename, single_count);

    digram_count_funct(filename, bigram_counts);
    digram_desc_print(outfilename, bigram_counts);

    trigram_count_funct(filename, trigram_counts);
    trigram_desc_print(outfilename, trigram_counts);

    return 0;
}
