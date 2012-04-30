CC = g++
SOURCE = test.cpp Globals.cpp TimeTracker.cpp
HEADER = Globals.h TimeTracker.h
OBJ = test.o Globals.o TimeTracker.o
EXEC = test

build : $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

test.o : $(SOURCE) $(HEADER)
	$(CC) -c test.cpp

Globals.o : Globals.cpp Globals.h
	$(CC) -c Globals.cpp

Tracker.o : TimeTracker.cpp TimeTracker.h
	$(CC) -c TimeTracker.cpp

clean :
	rm -f *.o
