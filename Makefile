main:	main.c single_count.c bigram.c trigram.c
	gcc main.c single_count.c bigram.c trigram.c -o main

clean:
	rm main