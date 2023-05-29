Program is written in C. It takes input from file "gamesales.csv" which contains data about different games' plateform, release date, genre, publisher, NA sales, EU sales, JP sales, other sales, and global sales. Program compiles and creates two object files: processing.o and sorting.o.

Processing.o simply prints how many games which publisher has released, sales percentage for each game, and summary statistic for global slaes. 

Sorting.o sorts the data according input by user and prints it into a new file called "gamesales_category.csv". 

lab13.h is a header file that contains all the important macros and function names for the program.

Makefile compiles the program into two object files as mentioned above. It takes one c file and creates two different objects files and accomplish different tasks.

You can compile the program by command: \make                                                                                                                          and run processing and sorting by: ./processing and ./sorting respectively 
