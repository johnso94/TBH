OPTS = -Wall -g -std=c++11

all:  project

project: project.cpp
	g++ $(OPTS) -o a.out project.cpp sd_fun.o str_util.o -lm

clean:
	\rm -f project *.o
