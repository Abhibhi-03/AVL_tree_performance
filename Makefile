CC=g++
CFLAGS=-Wall
FILES=AVLTree.cpp timer.cpp Source.cpp tester_Linux.cpp
TARGET=avlTree

# Default build target
all: $(TARGET)

# Rule to build the avlTree executable
$(TARGET): $(FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Clean rule for removing compiled objects and the executable
clean:
	rm -f *.o $(TARGET)

# Rule for checking memory leaks with Valgrind
memcheck:
	valgrind --leak-check=full ./$(TARGET)