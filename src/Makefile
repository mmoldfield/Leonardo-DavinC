#makefile for all the programs in worksheet 6

CC = gcc  #our compiler of choice
CFLAGS = -Wall -ansi -pedantic -Werror -g 
OBJ1 = startup.o core.o effects.o linkedlist.o fileio.o execute.o
OBJ2 = startup.o core.o effects.o linkedlist.o fileio.o executesimple.o
OBJ3 = startup.o core.o effects.o linkedlist.o fileio.o executedebug.o
EXEC1 = TurtleGraphics
EXEC2 = TurtleGraphicsSimple
EXEC3 = TurtleGraphicsDebug

#execs to make
$(EXEC1) : $(OBJ1) #make exec given that the objects exist
	$(CC) $(OBJ1) -o $(EXEC1) -lm #include math flag 

$(EXEC2) : $(OBJ2) #make exec given that the objects exist
	$(CC) $(OBJ2) -o $(EXEC2) -lm 

$(EXEC3) : $(OBJ3) #make exec given that the objects exist
	$(CC) $(OBJ3) -o $(EXEC3) -lm

#object prereqs
startup.o : startup.c startup.h core.c core.h
	$(CC) $(CFLAGS) -c startup.c

core.o : core.c core.h universal.h linkedlist.h linkedlist.c fileio.c fileio.h \
execute.c execute.h
	$(CC) $(CFLAGS) -c core.c

effects.o : effects.c effects.h
	$(CC) $(CFLAGS) -c effects.c

linkedlist.o : linkedlist.c linkedlist.h universal.h
	$(CC) $(CFLAGS) -c linkedlist.c

fileio.o : fileio.c fileio.h universal.h linkedlist.c linkedlist.h execute.c \
execute.h
	$(CC) $(CFLAGS) -c fileio.c

execute.o : execute.c execute.h universal.h linkedlist.c linkedlist.h effects.c\
effects.h
	$(CC) $(CFLAGS) -c execute.c

#alternate version of execute for the simple version of the program 
executesimple.o : execute.c execute.h universal.h linkedlist.c \
linkedlist.h effects.c effects.h
	$(CC) $(CFLAGS) -c execute.c -DSIMPLE -o executesimple.o

#alternate version of the execute for the debug version of the program
executedebug.o : execute.c execute.h universal.h linkedlist.c linkedlist.h \
effects.c effects.h
	$(CC) $(CFLAGS) -c execute.c -DDEBUG -o executedebug.o

#clean
clean :
	rm -f $(OBJ1) $(OBJ2) $(OBJ3) $(EXEC1) $(EXEC2) $(EXEC3)

#this target was made for my own internal testing... I should have used \
variables for my valgrind flags, but I didn't anticipate needing to change these
test :
	make clean
	make $(EXEC1)
	make $(EXEC2)
	make $(EXEC3)

	valgrind --track-origins=yes --leak-check=full ./$(EXEC1) \
	testfiles/charizard.txt 
	#******************************* valid *************************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC1) \
	testfiles/diamond.txt
	#******************************* valid *************************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC1) \
	testfiles/blankfile.txt testfiles/charizard.txt
	#********************invalid: too many args ********************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC1) 
	#***************************invalid: not enough args ***********************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC1) \
	testfiles/blankfile.txt #blank file
	#*******************************invalid: blank file ************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC1) \
	testfiles/blanktop.txt 
	#*********************invalid: blank first line ****************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC1) \
	testfiles/invnumargs.txt
	#*********************invalid: too many instructions on one line ***********

	valgrind --track-origins=yes --leak-check=full ./$(EXEC1) \
	testfiles/invargsize.txt
	#*********************invalid: invalid arg size ****************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC1) \
	testfiles/invoverflow.txt
	#*********************invalid: line too long  ******************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC1) \
	testfiles/invname.txt
	#*********************invalid: wrong cmd name ******************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC1) \
	TurtleGraphics
	#*********************invalid: calling itself ******************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC2) \
	testfiles/charizard.txt 
	#******************************* valid *************************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC2) \
	testfiles/diamond.txt
	#******************************* valid *************************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC2) \
	testfiles/blankfile.txt testfiles/charizard.txt #too many args
	#********************invalid: too many args ********************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC2) 
	#***************************invalid: not enough args ***********************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC2) \
	testfiles/blankfile.txt #blank file
	#*******************************invalid: blank file ************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC2) \
	testfiles/blanktop.txt 
	#*********************invalid: blank first line ****************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC2) \
	testfiles/invnumargs.txt
	#*********************invalid: too many instructions on one line ***********

	valgrind --track-origins=yes --leak-check=full ./$(EXEC2) \
	testfiles/invargsize.txt
	#*********************invalid: invalid arg size ****************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC2) \
	testfiles/invoverflow.txt
	#*********************invalid: line too long  ******************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC2) \
	testfiles/invname.txt
	#*********************invalid: wrong cmd name ******************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC2) \
	TurtleGraphics
	#*********************invalid: calling itself ******************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC3) \
	testfiles/charizard.txt 
	#******************************* valid *************************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC3) \
	testfiles/diamond.txt
	#******************************* valid *************************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC3) \
	testfiles/blankfile.txt testfiles/charizard.txt #too many args
	#********************invalid: too many args ********************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC3) 
	#***************************invalid: not enough args ***********************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC3) \
	testfiles/blankfile.txt #blank file
	#*******************************invalid: blank file ************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC3) \
	testfiles/blanktop.txt 
	#*********************invalid: blank first line ****************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC3) \
	testfiles/invnumargs.txt
	#*********************invalid: too many instructions on one line ***********

	valgrind --track-origins=yes --leak-check=full ./$(EXEC3) \
	testfiles/invargsize.txt
	#*********************invalid: invalid arg size ****************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC3) \
	testfiles/invoverflow.txt
	#*********************invalid: line too long  ******************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC3) \
	testfiles/invname.txt
	#*********************invalid: wrong cmd name ******************************

	valgrind --track-origins=yes --leak-check=full ./$(EXEC3) \
	TurtleGraphics
	#*********************invalid: calling itself ******************************

