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
void digram_desc_print (const char *infilename, const char *outfilename, const int bigram_counts[ALPHABET_SIZE][ALPHABET_SIZE]){
    FILE *outfile;

    //open read file, throw error if file cannot open
    if (!(outfile = fopen(outfilename, "a"))) {
        fprintf(stderr, "Failed opening file for writing %s\n", outfilename);
        exit(1);
    }

    // Create an matrix of structs to sort letters by count
    struct double_letter_count letters [MAX_BIGRAMS];
    int total_bigrams = 0;

    // calc total number of bigrams
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++){
            total_bigrams += bigram_counts[i][j];
        }
    }

    int all_bigrams = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (bigram_counts[i][j] > 0) {
                letters[all_bigrams].first_letter = 'a' + i;
                letters[all_bigrams].second_letter = 'a' + j;
                letters[all_bigrams].count = bigram_counts[i][j];
                letters[all_bigrams].percent = (100.0 * bigram_counts[i][j]) / total_bigrams;
                all_bigrams++;
            }
        }
    }
    
    // Sort using simple bubble sort
    for (int i = 0; i < all_bigrams - 1; i++) {
        for (int j = 0; j < all_bigrams - i -1; j++) {
            if (letters[j].count < letters[j +1].count) {
                struct double_letter_count temp= letters[j];
            letters[j] = letters[j+1];
            letters[j+1] = temp;
            }
        }
    }

    // struct of the english frequncy to print later
    struct double_freq english_freq [] = {
        {'t','h',1.52}, {'h','e',1.28}, {'i','n',0.94}, {'e','r',0.94},
        {'a','n',0.82}, {'r','e',0.68}, {'o','n',0.57}, {'a','t',0.56},
        {'e','n',0.55}, {'n','d',0.53}, {'t','o',0.52}, {'o','f',0.50},
        {'h','a',0.49}, {'t','i',0.47}, {'s','t',0.46}, {'e','s',0.46},
        {'e','n',0.45}, {'n','g',0.43}, {'o','u',0.43}, {'l','e',0.42},
        {'o','r',0.42}, {'a','l',0.40}, {'i','t',0.39}, {'a','s',0.38},
        {'i','s',0.38}, {'h','o',0.38}, {'u','n',0.37}, {'i','o',0.37},
        {'e','d',0.37}, {'c','o',0.36}
    };


    // Print sorted bigrams
    fprintf(outfile, "\nBigram frequencies (descending):\n");
    fprintf(outfile, "%-10s %-10s %-10s\n", "Cipher", "Cipher %", "Most Common in Enlgish");

    // int topN = english_freq < index ? english_freq : index;

    for (int i = 0; i < 30; i++) {
        fprintf(outfile, "%d. %c%c: %d (%.2f%%) →  %d. %c%c (%.2f%%)\n", (i+1), letters[i].first_letter, 
            letters[i].second_letter, letters[i].count, letters[i].percent, (i+1), 
            english_freq[i].first_letter, english_freq[i].second_letter, 
            english_freq[i].percent);
    }
    fclose(outfile);

    digram_decrypt(infilename, outfilename, letters, english_freq);

}

void digram_decrypt(const char *infilename, const char *outfilename, struct double_letter_count letters[], struct double_freq english_freq[]) {
    FILE *infile = fopen(infilename, "r");
    FILE *outfile = fopen(outfilename, "a");

    if (!infile || !outfile) {
        fprintf(stderr, "Failed opening input/output files.\n");
        if (infile) fclose(infile);
        if (outfile) fclose(outfile);
        exit(1);
    }

    // Create bigram mapping
    char bigram_map[ALPHABET_SIZE][ALPHABET_SIZE][2] = {{0}};

    for (int i = 0; i < 30; i++) {
        int ci1 = letters[i].first_letter - 'a';
        int ci2 = letters[i].second_letter - 'a';
        bigram_map[ci1][ci2][0] = english_freq[i].first_letter;
        bigram_map[ci1][ci2][1] = english_freq[i].second_letter;
    }

    fprintf(outfile, "\n\nDecrypted Text (via BIGRAM frequency mapping):\n\n");

    int c1 = EOF, c2;
    while ((c2 = fgetc(infile)) != EOF) {
        if (isalpha(c2)) {
            c2 = tolower(c2);

            if (c1 != EOF) {
                int i1 = c1 - 'a';
                int i2 = c2 - 'a';

                if (bigram_map[i1][i2][0] != 0 && bigram_map[i1][i2][1] != 0) {
                    fputc(bigram_map[i1][i2][0], outfile);
                    fputc(bigram_map[i1][i2][1], outfile);
                } else {
                    fputc(c1, outfile);
                    fputc(c2, outfile);
                }

                c1 = EOF; // reset to look for next bigram
            } else {
                c1 = c2;
            }
        } else {
            // If non-letter, write as-is and reset
            fputc(c2, outfile);
            c1 = EOF;
        }
    }

    fclose(infile);
    fclose(outfile);
}
