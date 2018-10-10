CPPFLAGS= -Wall -Wextra -pedantic

all:	test.cpp	Deque.hpp
	g++ test.cpp Deque.hpp -ldl -Wextra -pedantic -Wall
	# Insert command to compile the code and generate executable

run:	a.out
	./a.out
	# Insert command to run the executable

checkmem:	a.out
	valgrind ./a.out
	# Insert command to run the executable with valgrind

clean:
	rm a.out
	rm Deque.hpp.gch
	# Insert command to clean object files, executables
