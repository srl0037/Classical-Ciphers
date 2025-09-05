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
    char buffer[3] = {0}; // sliding window of last 3 valid letters
    int ch;

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

    // calc total number of trigrams
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            for (int k = 0; k < ALPHABET_SIZE; k++){
                // total_trigrams += total_trigrams[i][j][k];
                total_trigrams += trigram_counts[i][j][k];
            }
        }
    }

    int all_trigrams = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            for (int k = 0; k < ALPHABET_SIZE; k++){
                if (trigram_counts[i][j][k] > 0) {
                    letters[all_trigrams].first_letter = 'a' + i;
                    letters[all_trigrams].second_letter = 'a' + j;
                    letters[all_trigrams].third_letter = 'a' + j;
                    letters[all_trigrams].count = trigram_counts[i][j][k];
                    letters[all_trigrams].percent = (100.0 * trigram_counts[i][j][k]) / total_trigrams;
                    all_trigrams++;
                }
            }
        }


        // Sort using simple bubble sort
        for (int i = 0; i < all_trigrams - 1; i++) {
            for (int j = 0; j < all_trigrams - i -1; j++) {
                if (letters[j].count < letters[j +1].count) {
                    struct triple_letter_count temp= letters[j];
                    letters[j] = letters[j+1];
                    letters[j+1] = temp;
                }
            }
        }
    }

    // struct of the english frequncy to print later
    struct triple_freq english_freq [] = {
        {'t','h','e',1.81}, {'a','n','d',0.73}, {'i','n','g',0.72}, {'h','e','r',0.71},
        {'e','n','t',0.42}, {'t','i','o',0.42}, {'e','r','e',0.42}, {'t','h','a',0.33},
        {'n','t','h',0.33}, {'w','a','s',0.28}, {'e','t','h',0.27}, {'f','o','r',0.26},
        {'d','t','h',0.25}, {'h','a','t',0.24}, {'t','h','i',0.24}, {'w','i','t',0.23},
        {'w','i','l',0.22}, {'i','o','n',0.22}, {'o','f','t',0.21}, {'h','i','s',0.21},
        {'e','s','t',0.20}, {'o','n','e',0.20}, {'r','e','s',0.19}, {'o','u','t',0.19},
        {'h','a','v',0.19}, {'n','g','t',0.18}, {'o','f','f',0.18}, {'t','h','e',0.18},
        {'t','e','r',0.17}, {'s','t','a',0.17}
    };


    // Print sorted bigrams
    fprintf(outfile, "\nTrigram frequencies (descending):\n");
    fprintf(outfile, "%-10s %-10s %-10s\n", "Cipher", "Cipher %", "Most Common in Enlgish");
    
    for (int i = 0; i < 30; i++) {
        fprintf(outfile, "%d. %c%c%c: %d (%.2f%%) →  %d. %c%c%c (%.2f%%)\n", 
            (i+1), letters[i].first_letter, letters[i].second_letter, 
            letters[i].third_letter, letters[i].count, letters[i].percent,
            (i+1), english_freq[i].first_letter, english_freq[i].second_letter,
            english_freq[i].third_letter, english_freq[i].percent);
    }

    fclose(outfile);
}