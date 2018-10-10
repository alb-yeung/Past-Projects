Simply using `make` will make all three programs.
Use by
./program1 <input-file1> <input-file2> <output-file>
./program2 <input-file1> <input-file2> <output-file>
./program3 <input-file1> <input-file2> <output-file>

Program 1 and Program 3 use a 2D array to store the LCS for certain substrings.
Program 2 doesn't use any special data structures.

Program 1 and Program 3 are psuedo-linear, and therefore much faster than Program 2, which is exponential in time.

timeProg.h is a header file that stores two times and then the difference between the two times.