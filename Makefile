CC = g++ -pedantic -Wall -g

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: start

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
start:  game.o main.o 
	$(CC)  -o a.out game.o main.o

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
game.o: game.hpp
	$(CC)  -c game.cpp

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
main.o: game.cpp
	$(CC)  -c main.cpp


# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) start *.o *~
