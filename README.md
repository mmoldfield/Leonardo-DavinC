# Leonardo-DavinC

Java program that reads in a .txt file containing instructions, and then draws an ASCII art picture according to these instructions. For example:

``

rotate -45

move 30

FG 1

Pattern #

DRAW 10

Rotate 90

draw 10

ROTATE 90

dRAW 10

ROTATE 90

DRAW 10

``

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

* [Java SE Development Kit 8](https://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html)

### Executing the program

Clone the project into the local directory of your choice

```
git clone https://github.com/mmoldfield/DSA_Assignment.git
```

Change directory into the project source directory 

```
cd AusPol-Campaign-Manager/source
```

Compile and run the program
```
javac *.java && java startup
```

### Using the program

This program has 4 main functions
1. List Nominees
2. Nominee Search
3. List by Margin
4. Itinerary by Margin (WORK IN PROGRESS)

For options 1 and 2, use the file 'Candidates.csv' when prompted.

For option 3, type in the name of a political party (For example, "Australian Labor Party") followed by the file 'Preferences.csv'

For option 4, first create a List by Margin and then load in the distances file 'Distances.csv'. When requested for an Airport Distances file, load in 'AirportDistances.csv'.

### Data structures used

The following data structures were created by myself, as part of the unit Data Structures and Algorithms at Curtin University:

``
Graph.java, HashTable.java, Heap.java, LinkedList.java, Stack.java
``

********************************************************************************
Name: Matthew Oldfield
File: readme.txt
********************************************************************************

List of files

    startup.c / startup.h
    - simple file that contains the main method

    core.c / core.h
    - controls the navigation of the program

    execute.c / execute.h
    - responsible for drawing ascii art

    fileio.c / fileio.h
    - responsible for reading in input file

    linkedlist.c / linkedlist.h
    - standard linkedlist implementation (program specific nodes)

    effects.c / effects.h
    - contains plotting functions - code by Dr. David Cooper

    universal.h
    - contains preprocessor macros needed by multiple files in the program

Instructions

    1. Navigate to program directory in a unix terminal and type in 'make'
    2. To run program, type './TurtleGraphics testfiles/charizard.txt'
        * Replace charizard.txt with whatever file you desire

Bugs and Improvements

    Functionality wise, this program is pretty much complete. With more time,
    I would have liked to clean up some of my control structures and perhaps
    write up some better error messages. That being said, the program should be
    fully functional for the purpose of this assignment (perhaps I will revamp
    it during the holidays)

Computer Used
    
    Curtin Building 314, Lab 220-c04 (Ubuntu Linux)
    Program may not compile on other hardware.

References

    All code is my own, however I owe credit to the Curtin University lecture
    slides for providing sample linked list code. I used this as a guide when
    designing my own code.







