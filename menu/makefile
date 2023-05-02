CC = g++
CFLAGS = -g -Wall -Wextra -std=c++17 -Iinclude
TFLAGS = -lgtest -lgtest_main -lpthread
EXEC = main

all : menu.cc
	$(CC) $(CFLAGS) -o $(EXEC).out menu.cc
clean :
	rm -rf $(EXEC).out
	rm build/*.o

.PHONY : clean