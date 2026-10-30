CC = clang++
CFLAGS = -Wall -Wextra -std=c++20 -I include

TEST_SRCS = tests/test_main.cpp tests/tests.cpp tests/assert.cpp
HEADERS = $(wildcard include/*.hpp) tests/assert.hpp tests/tests.hpp
FORMAT_FILES = include/*.hpp src/*.cpp tests/*.cpp tests/*.hpp

TARGET = test_runner

all: format test valgrind

lab: src/main.cpp $(HEADERS)
	$(CC) $(CFLAGS) src/main.cpp -o lab

run: lab
	./lab

$(TARGET): $(TEST_SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o $(TARGET)

test: $(TARGET)
	./$(TARGET)

valgrind: $(TEST_SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -g -O0 $(TEST_SRCS) -o test_runner_valgrind
	valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=definite,possible --error-exitcode=1 ./test_runner_valgrind

format:
	clang-format -i $(FORMAT_FILES)

clean:
	rm -f lab $(TARGET) test_runner_valgrind

.PHONY: all run test valgrind format clean