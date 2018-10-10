Everything works except for:
	-Correct type_name size
	-Deque_equal
	-Deque.clear
	-Deque.dtor
	-Sort

Correct type_name size always returns 8 because I initialized it as a const char *

Deque_equal does not work because I couldn't think of a way to compare structs and ints in the same fashion.

Clear and dtor don't actually get rid of the memory leaks

Sort doesn't work because I couldn't think of how to get the comparator function given into the compare function needed for qsort. Qsort's compare function must have two void* parameters but the compare function would require a deq pointer too to access the comparator function given.

The test file is almost the same as the given test file except with the stuff that doesn't work commented out.
