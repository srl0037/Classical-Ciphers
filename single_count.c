#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "single_count.h"

//function to count frequency of each letter
void single_count_funct(const char *filename, int *single_count) {
    FILE *fp;
    int letter;
    int index;

    //open read file, throw error if file cannot open
    if (!(fp = fopen(filename, "r"))) {
        fprintf(stderr, "Failed opening file %s\n", filename);
        exit(1);
    }

    // for each char until EOF, if letter, change to lower case, increment count
    while ((letter = fgetc(fp)) != EOF) {
        if (isalpha(letter)) {
            letter = tolower(letter);
            index = letter - 'a';
            single_count[index]++;
        }
    }

    fclose(fp);
}

//function to print letters out in descending
void desc_print (const char *outfilename, const int *single_count){
    FILE *outfile;

    //open read file, throw error if file cannot open
    if (!(outfile = fopen(outfilename, "a"))) {
        fprintf(stderr, "Failed opening file for writing %s\n", outfilename);
        exit(1);
    }

    // Create an array of structs to sort letters by count
    struct single_letter_count letters[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        letters[i].letter = 'a' + i;
        letters[i].count = single_count[i];
    }

    // Sort using simple bubble sort
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (letters[i].count < letters[j].count) {
                struct single_letter_count temp = letters[i];
                letters[i] = letters[j];
                letters[j] = temp;
            }
        }
    }

    // Print result
    fprintf(outfile, "\nSingle Letter frequencies (descending):\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (letters[i].count > 0)
            fprintf(outfile, "%c: %d\n", letters[i].letter, letters[i].count);
    }
    fclose(outfile);
}
