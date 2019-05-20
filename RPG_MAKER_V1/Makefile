OPTS = -Wall -g -std=c++11

all: project

project: project.cpp Shape.o Rectangle.o Location.o Client.o Util.o 
	g++ $(OPTS) -o a.out project.cpp Shape.o Rectangle.o Location.o Client.o Util.o sd_fun.o str_util.o -lm

Shape.o: Shape.cpp Shape.h
	g++ $(OPTS) -c Shape.cpp

Rectangle.o: Rectangle.cpp Rectangle.h Shape.h
	g++ $(OPTS) -c Rectangle.cpp
	
Util.o: Util.cpp Util.h
	g++ $(OPTS) -c Util.cpp

Location.o: Location.cpp Location.h Util.h
	g++ $(OPTS) -c Location.cpp

Client.o: Client.cpp Client.h Location.h Util.h
	g++ $(OPTS) -c Client.cpp

clean:
	\rm -f project *.o



