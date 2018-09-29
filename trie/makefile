CC= g++
CFLAGS= -Wall -std=c++11 -ggdb

main: main.cpp Trie.h
	$(CC) $(CFLAGS) -o main main.cpp

clean:
	rm -rf main Trie.h.gch

valgrind:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --track-origins=yes ./main
