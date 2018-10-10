#Albert Yeung
#Liang Hsun Tseng

all:	Policies Generator

Policies:	Policies.o
		gcc Policies.o -o prog4swap

Policies.o:	Policies.c
		gcc -c Policies.c

Generator:	Generator.c
	gcc Generator.c -o generator

clean:
	rm -f *.o
	rm prog4swap
	rm generator