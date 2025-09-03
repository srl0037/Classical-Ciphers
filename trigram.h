#ifndef TRIGRAM_H
#define TRIGRAM_H

#define ALPHABET_SIZE 26
#define MAX_TRIGRAMS (ALPHABET_SIZE * ALPHABET_SIZE * ALPHABET_SIZE)

//struct of a double letter count
struct triple_letter_count{
    char first_letter;
    char second_letter;
    char third_letter;
    int count;
};

//function to count frequency of each pair of letters
void trigram_count_funct(const char *filename, int trigram_counts[ALPHABET_SIZE][ALPHABET_SIZE][ALPHABET_SIZE]);

//function to print letters out in descending order
void trigram_desc_print (const char *outfilename, const int trigram_counts[ALPHABET_SIZE][ALPHABET_SIZE][ALPHABET_SIZE]);

#endif