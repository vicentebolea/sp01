SHELL := /bin/bash

all: p1 bonus1 p2 bonus2

p1: driver.c lru.c problem1_LRU_20131780.c
	$(CC) -std=c99 -Wall -pedantic -ggdb -o $@ $^

p2: driver.c lru.c s4lru.c problem2_S4LRU_20131780.c
	$(CC) -std=c99 -Wall -pedantic -ggdb -o $@ $^

bonus1: driver.c lru.c bonus1_LRU_20131780.c
	$(CC) -std=c99 -Wall -pedantic -ggdb -o $@ $^

bonus2: driver.c lru.c s4lru.c bonus2_LRU_20131780.c
	$(CC) -std=c99 -Wall -pedantic -ggdb -o $@ $^

clean:
	-rm p1 bonus1 p2 bonus2

test: all
	@./p1 4 input.txt;                                \
	diff <(echo "$$lru_expected_output") list.txt;     \
	if [ "$$?" == "0" ];  then                         \
	  echo "Passed LRU";                               \
  else                                               \
	  echo "Failed LRU";                               \
  fi;                                                \
                                                     \
	./bonus1 4 input_r.txt;                            \
	diff <(echo "$$bonus1_expected_output") list.txt;  \
	if [ "$$?" == "0" ];  then                         \
	  echo "Passed Bonus1";                            \
  else                                               \
	  echo "Failed Bonus2";                            \
  fi;                                                \
                                                     \
	./p2 3 input2.txt;                                 \
	diff <(echo "$$p2_expected_output_0") list_0.txt;  \
  out1="$$?";                                        \
	diff <(echo "$$p2_expected_output_1") list_1.txt;  \
  out2="$$?";                                        \
	if [ "$$out1" == "0" -a "$$out2" == "0" ];  then   \
	  echo "Passed program2";                          \
  else                                               \
	  echo "Failed program2";                          \
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

define p2_expected_output_0
1
2 1
3 2 1
3 2
3
4 3
5 4 3
5 4 3
6 5 4
6 5
6
2
2
7 2
8 7 2
4 8 2
9 4 8
endef

define p2_expected_output_1



1
2 1
2 1
2 1
2
2
4 2
5 4 2
6 5 4
6 5 4
6 5 4
6 5 4
7 6 5
7 6 5
endef

define bonus2_expected_output

endef

export lru_expected_output
export bonus1_expected_output
export p2_expected_output_0
export p2_expected_output_1
export bonus2_expected_output
