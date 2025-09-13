OBJECTS=registers.o
CC=clang
BUILD_DIR=./out


.PHONY: test

test: $(OBJECTS)
	$(CC) -I src -o $(BUILD_DIR)/$@ $^ apps/test.c

%.o : src/%.c src/%.h
	$(CC) -c $^


clean:
	rm -f *.o
	rm -f $(BUILD_DIR)/*
	

