#ifndef SINGLE_COUNT_H
#define SINGLE_COUNT_H

#define ALPHABET_SIZE 26

//struct of a single letter count
struct single_letter_count{
    char letter;
    int count;
    float percent;
};

struct single_freq{
    char letter;
    float percent;
};

//function to count frequency of each letter
void single_count_funct(const char *filename, int *single_count);

//function to print letters out in descending order
void desc_print (const char *outfilename, const int *single_count);

#endif