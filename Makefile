OPTS = -Wall -g -std=c++11

all:  project

project: project.cpp Shape.o Circle.o Rectangle.o
	g++ $(OPTS) -o a.out project.cpp Shape.o Circle.o Rectangle.o sd_fun.o str_util.o -lm

Shape.o: Shape.cpp Shape.h
	g++ $(OPTS) -c Shape.cpp

Circle.o: Circle.cpp Circle.h Shape.h
	g++ $(OPTS) -c Circle.cpp

Rectangle.o: Rectangle.cpp Rectangle.h Shape.h
	g++ $(OPTS) -c Rectangle.cpp

clean:
	\rm -f project *.o
