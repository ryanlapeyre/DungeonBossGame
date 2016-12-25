all: Gauntlet
#Executable Name

Gauntlet: game.o shop.o heroes.o io.o parse.o boss.o fight.o
	gcc -g -Wall -Werror game.o shop.o heroes.o io.o parse.o boss.o fight.o -o Gauntlet
#Builds an executable from the object files. The -o compiles the files as ".o" files.
#Compiles with proper flags as well.

game.o : game.h game.c
	gcc -g -Wall -Werror -c game.c
#Builds the .o file from the .h header file and the original .c file.
#Compiles with -c so it's know that the file is a "C" language file. Repeats for the other "C" files.
	
shop.o : game.h shop.c
	gcc -g -Wall -Werror -c shop.c
heroes.o : game.h heroes.c
	gcc -g -Wall -Werror -c heroes.c
io.o : game.h io.c
	gcc -g -Wall -Werror -c io.c
parse.o : game.h parse.c
	gcc -g -Wall -Werror -c parse.c

boss.o : game.h boss.c
	gcc -g -Wall -Werror -c boss.c

fight.o : game.h fight.c
	gcc -g -Wall -Werror -c fight.c

clean: 
	rm -f game.o shop.o heroes.o io.o parse.o boss.o fight.o Gauntlet
#The make clean command. Removes the object file when called as "make clean" in conjunction with the executable. 
