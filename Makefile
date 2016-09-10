all:
	$(CC) -std=c99 -Wall -pedantic -ggdb driver.c lru.c main.c
