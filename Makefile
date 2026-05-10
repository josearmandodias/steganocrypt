CC = gcc
CFLAGS = -Wall -Wextra -std=c99

steganocrypt: main.c crypto.c image.c steganographie.c traitement.c
	$(CC) $(CFLAGS) main.c crypto.c image.c steganographie.c traitement.c -o steganocrypt

clean:
	rm -f steganocrypt