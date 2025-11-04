CC=clang -std=c17 -Wall -Wextra -Werror
BIN_DIR=./out
.PHONY: init format test-auto
INCLUDES=-Isrc -Itest

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)
TEST_SRCS=$(wildcard test/*.c)
TEST_OBJS=$(TEST_SRCS:.c=.o)

init:
	mkdir -p $(BIN_DIR)


format:
	clang-format -i src/cwave.h src/cwave.c test/cwave_test.c

run-test: test
	$(BIN_DIR)/cwave-test

test: gen-test-main test-objects

test-objects: $(OBJS) $(TEST_OBJS)
	$(CC) -o $(BIN_DIR)/cwave-test $^

gen-test-main:
	python3 test/auto.py

%.o: %.c
	$(CC) $(INCLUDES) -o $@ -c $^


delete: 
	find . -type f -name "*.o" -delete
	rm -rf $(BIN_DIR)/*

clean: delete init
	

