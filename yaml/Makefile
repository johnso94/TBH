OPTS = -Wall -g -std=c++11

all:  project

project: project.cpp Inventory.o fighter.o commands.o PC.o Enemy.o 
	g++ $(OPTS) -o a.out project.cpp Inventory.o fighter.o commands.o PC.o Enemy.o sd_fun.o str_util.o -lm

Inventory.o: Inventory.cpp Inventory.h
	g++ $(OPTS) -c Inventory.cpp

fighter.o: fighter.cpp fighter.h Inventory.h
	g++ $(OPTS) -c fighter.cpp

commands.o: commands.cpp commands.h
	g++ $(OPTS) -c commands.cpp

PC.o: PC.cpp PC.h fighter.h Enemy.h
	g++ $(OPTS) -c PC.cpp

Enemy.o: Enemy.cpp Enemy.h fighter.h Inventory.h PC.h
	g++ $(OPTS) -c Enemy.cpp

clean:
	\rm -f project *.o
