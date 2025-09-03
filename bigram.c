#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bigram.h"

//function to count frequency of each pair of letter
void digram_count_funct(const char *filename, int bigram_count[ALPHABET_SIZE][ALPHABET_SIZE]) {
    FILE *fp;
    int first_letter = -1;
    int second_letter;
    int first_index;
    int second_index;


    //open file, throw error if file cannot open
    if (!(fp = fopen(filename, "r"))) {
        fprintf(stderr, "Failed opening file %s\n", filename);
        exit(1);
    }

    // start with the current char, if it is a letter, convert to lower, then look at previous
    while ((second_letter = fgetc(fp)) != EOF) {
        if (isalpha(second_letter)) {
            second_letter = tolower(second_letter);

            // if the current char 
            if (first_letter != -1){
                first_index = first_letter - 'a';
                second_index = second_letter - 'a';
                bigram_count[first_index][second_index]++;
            }
           
            //iterate through the letters
            first_letter = second_letter;
        }

        // if current char is not a letter, reset the previous char 
        else{
            first_letter = -1;
        }
    }
    // close the file
    fclose(fp);
}


//function to pair of print letters out in descending
void digram_desc_print (const char *outfilename, const int bigram_counts[ALPHABET_SIZE][ALPHABET_SIZE]){
    FILE *outfile;

    //open read file, throw error if file cannot open
    if (!(outfile = fopen(outfilename, "a"))) {
        fprintf(stderr, "Failed opening file for writing %s\n", outfilename);
        exit(1);
    }

    // Create an matrix of structs to sort letters by count
    struct double_letter_count letters [MAX_BIGRAMS];
    int total_bigrams = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (bigram_counts[i][j] > 0) {
                letters[total_bigrams].first_letter = 'a' + i;
                letters[total_bigrams].second_letter = 'a' + j;
                letters[total_bigrams].count = bigram_counts[i][j];
                total_bigrams++;
            }
        }

        // Sort using simple bubble sort
        for (int i = 0; i < total_bigrams - 1; i++) {
            for (int j = 0; j < total_bigrams - i -1; j++) {
                if (letters[j].count < letters[j +1].count) {
                    struct double_letter_count temp= letters[j];
                letters[j] = letters[j+1];
                letters[j+1] = temp;
                }
            }
        }
    }
    // Print sorted bigrams
    fprintf(outfile, "\nBigram frequencies (descending):\n");
    for (int i = 0; i < 30; i++) {
        fprintf(outfile, "%d. %c%c: %d\n", (i+1), letters[i].first_letter, letters[i].second_letter, letters[i].count);
    }
    fclose(outfile);
}
