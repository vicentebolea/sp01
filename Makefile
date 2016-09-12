SHELL := /bin/bash

all: lru bonus1 p2

lru: driver.c lru.c main.c
	$(CC) -std=c99 -Wall -pedantic -ggdb -o $@ $^

bonus1: driver.c lru.c bonus1_LRU_20131780.c
	$(CC) -std=c99 -Wall -pedantic -ggdb -o $@ $^

p2: driver.c lru.c s4lru.c problem2_S4LRU_20131780.c
	$(CC) -std=c99 -Wall -pedantic -ggdb -o $@ $^

clean:
	-rm lru bonus1

test: all
	@./lru 4 input.txt; \
	diff <(echo "$$lru_expected_output") list.txt;  \
	if [ "$$?" == "0" ];  then  \
	  echo "Passed LRU";      \
  else                     \
	  echo "Failed LRU";  \
  fi;                  \
\
	./bonus1 4 input_r.txt; \
	diff <(echo "$$bonus1_expected_output") list.txt;  \
	if [ "$$?" == "0" ];  then  \
	  echo "Passed Bonus1";      \
  else                     \
	  echo "Failed Bonus2";  \
  fi

define lru_expected_output
1
2 1
3 2 1
4 3 2 1
1 4 3 2
2 1 4 3
5 2 1 4
1 5 2 4
2 1 5 4
3 2 1 5
4 3 2 1
endef

define bonus1_expected_output
1
2 1
3 2 1
4 3 2 1
1 4 3 2
2 1 4 3
5 2 1 4
1 5 2 4
2 1 5 4
3 2 1 5
4 3 2 1
4 3 2 1
5 4 3 2 1
6 5 4 3 2 1
endef

export lru_expected_output
export bonus1_expected_output
