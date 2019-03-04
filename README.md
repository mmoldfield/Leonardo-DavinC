# Leonardo-DavinC

Java program that reads in a .txt file containing instructions, and then draws an ASCII art picture according to these instructions. For example...

rotate -45

move 30

FG 1

Pattern #

DRAW 10

Rotate 90

draw 10

ROTATE 90

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

* GCC, the GNU Compiler Collection (https://gcc.gnu.org/)

### Executing the program

Clone the project into the local directory of your choice

```
git clone https://github.com/mmoldfield/Leonardo-DavinC.git
```

Change directory into the project source directory 

```
cd Leonardo_DavinC/src
```

Compile and run the program (replace charizard.txt with any of the test files)
```
make clean
make
./TurtleGraphics testfiles/charizard.txt
```

To run the simple version (black and white)
```
make clean
make TurtleGraphicsSimple
./TurtleGraphicsSimple testfiles/charizard.txt
```

To run the proigram in debug mode
```
make clean
make TurtleGraphicsDebug
./TurtleGraphicsDebug testfiles/charizard.txt
```
### References

All code was created by myself, except for effects.c/effects.h which were created by Dr David Cooper of Curtin University.






