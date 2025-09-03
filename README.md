This is a classical cipher program.

The goal of this project was to become more familiar with monoalphabetic substiution 
ciphers and to user letter frequencies to cryptanalyze an inputted cipher text.

A program has been created to analyze the letter frequencies in an inputted text. This 
program can analyze the frequency of single letters, digrams, and trigrams. The program
reads an inputted text file and then writes the non-zero frequencies in decending order
to an output file. Please note that only the first most common 30 values are printed the 
bigrams and trigrams.

In order to run, please pull down all files in this repository. Then, run "make" to create an executable called "main." Run "./main" You will then be asked which file you would like to analyze (the encrypted file). Within this repository, I have included hamlet_input.txt and test2.txt. hamlet_input.txt is the full text of "Hamlet." This shows how effecively the program can run. test2.txt is an encrypted text that can be decoded.