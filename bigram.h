#ifndef BIGRAM_H
#define BIGRAM_H

#define ALPHABET_SIZE 26
#define MAX_BIGRAMS (ALPHABET_SIZE * ALPHABET_SIZE)

//struct of a double letter count
struct double_letter_count{
    char first_letter;
    char second_letter;
    int count;
    float percent;
};

struct double_freq{
    char first_letter;
    char second_letter;
    float percent;
};

//function to count frequency of each pair of letters
void digram_count_funct(const char *filename, int bigram_counts[ALPHABET_SIZE][ALPHABET_SIZE]);

//function to print letters out in descending order
void digram_desc_print (const char *outfilename, const int bigram_counts[ALPHABET_SIZE][ALPHABET_SIZE]);

#endif