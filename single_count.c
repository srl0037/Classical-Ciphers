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
    int total_letters = 0;

    //count all letters
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        total_letters += single_count[i];
    }


    for (int i = 0; i < ALPHABET_SIZE; i++) {
        letters[i].letter = 'a' + i;
        letters[i].count = single_count[i];
        letters[i].percent = (100.0 * single_count[i]) / total_letters;
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

    // struct of the english frequncy to print later
    struct single_freq english_freq [] = {
        {'e', 12.70}, {'t', 9.06}, {'a', 8.17}, {'o', 7.51},
        {'i', 6.97}, {'n', 6.75}, {'s', 6.33}, {'h', 6.09},
        {'r', 5.99}, {'d', 4.25}, {'l', 4.03}, {'c', 2.78},
        {'u', 2.76}, {'m', 2.41}, {'w', 2.36}, {'f', 2.23},
        {'g', 2.02}, {'y', 1.97}, {'p', 1.93}, {'b', 1.49},
        {'v', 0.98}, {'k', 0.77}, {'j', 0.15}, {'x', 0.15},
        {'q', 0.10}, {'z', 0.07}
    };


    // Print result
    // Print sorted bigrams
    fprintf(outfile, "\nSingle Letter frequencies (descending):\n");
    fprintf(outfile, "%-10s %-10s %-10s\n", "Cipher", "Cipher %", "Most Common in Enlgish");

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (letters[i].count > 0)
            fprintf(outfile, "%d. %c: %d (%.2f%%) →  %d. %c (%.2f%%)\n", (i+1), letters[i].letter, letters[i].count, 
                letters[i].percent, (i+1), english_freq[i].letter, 
                english_freq[i].percent);
    }
    fclose(outfile);
}
