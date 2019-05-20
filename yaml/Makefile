OPTS = -Wall -g -std=c++11

all:  project

project: project.cpp Shape.o Client.o Circle.o Rectangle.o
	g++ $(OPTS) -o a.out project.cpp Client.o sd_fun.o str_util.o -lm

Client.o: Client.cpp Client.h
	g++ -g -Wall -std=c++11 -c Client.cpp

clean:
	\rm -f project *.o
