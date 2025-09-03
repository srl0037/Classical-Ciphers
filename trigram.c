#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "trigram.h"

//function to count frequency of each pair of letter
void trigram_count_funct(const char *filename, int trigram_count[ALPHABET_SIZE][ALPHABET_SIZE][ALPHABET_SIZE]) {
    FILE *fp;
    int first_letter = -1;
    int second_letter = -1;
    int third_letter;
    int first_index;
    int second_index;
    int third_index;



    //open file, throw error if file cannot open
    if (!(fp = fopen(filename, "r"))) {
        fprintf(stderr, "Failed opening file %s\n", filename);
        exit(1);
    }

    // start with the current char, if it is a letter, convert to lower, then look at previous
    while ((third_letter = fgetc(fp)) != EOF) {
        if (isalpha(third_letter)) {
            third_letter = tolower(third_letter);

            // if the current char 
            if (first_letter != -1 && second_letter != -1){
                first_index = first_letter - 'a';
                second_index = second_letter - 'a';
                third_index = third_letter - 'a';
                trigram_count[first_index][second_index][third_index]++;
            }
           
            //iterate through the letters
            first_letter = second_letter;
            second_letter = third_letter;
        }

        // if current char is not a letter, reset the previous char 
        else{
            first_letter = -1;
            second_letter = -1;
        }
    }
    // close the file
    fclose(fp);
}

void trigram_desc_print (const char *outfilename, const int trigram_counts[ALPHABET_SIZE][ALPHABET_SIZE][ALPHABET_SIZE]){
    FILE *outfile;

    //open read file, throw error if file cannot open
    if (!(outfile = fopen(outfilename, "a"))) {
        fprintf(stderr, "Failed opening file for writing %s\n", outfilename);
        exit(1);
    }

    // Create an matrix of structs to sort letters by count
    struct triple_letter_count letters [MAX_TRIGRAMS];
    int total_trigrams = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            for (int k = 0; k < ALPHABET_SIZE; k++){
                if (trigram_counts[i][j][k] > 0) {
                    letters[total_trigrams].first_letter = 'a' + i;
                    letters[total_trigrams].second_letter = 'a' + j;
                    letters[total_trigrams].third_letter = 'a' + j;
                    letters[total_trigrams].count = trigram_counts[i][j][k];
                    total_trigrams++;
                }
            }
        }


        // Sort using simple bubble sort
        for (int i = 0; i < total_trigrams - 1; i++) {
            for (int j = 0; j < total_trigrams - i -1; j++) {
                if (letters[j].count < letters[j +1].count) {
                    struct triple_letter_count temp= letters[j];
                    letters[j] = letters[j+1];
                    letters[j+1] = temp;
                }
            }
        }
    }

    // Print sorted bigrams
    fprintf(outfile, "\nTrigram frequencies (descending):\n");
    for (int i = 0; i < 30; i++) {
        fprintf(outfile, "%d. %c%c%c: %d\n", (i+1), letters[i].first_letter, letters[i].second_letter, letters[i].third_letter, letters[i].count);
    }

    fclose(outfile);
}

