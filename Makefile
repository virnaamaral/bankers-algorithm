all: banker.c
	gcc banker.c -o banker
clean:
	rm banker