all: processing sorting

processing: ex13q1.o ex13q10.o
	gcc -DFLAG=1 -o processing ex13q1.c ex13q10.o

sorting: ex13q1.o ex13q10.o ex13q11.o
	gcc -DFLAG=2 -o sorting ex13q1.c ex13q10.o ex13q11.o

ex13q1.o: ex13q1.c lab13.h
	gcc -c ex13q1.c

ex13q10.o: ex13q10.c lab13.h
	gcc -c ex13q10.c

ex13q11.o: ex13q11.c lab13.h
	gcc -c ex13q11.c