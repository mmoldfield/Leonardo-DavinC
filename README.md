# Leonardo-DavinC

Java program that reads in election poll data and allows the user to search, sort and filter this information. Also allows the user to compute which locations will benefit the most from additional campaiging, and creates an itinerary based on this.

All data structures used in this program were created by myself, to cement my understanding of how they work.

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




