OPTS = -Wall -g -std=c++11

all: ClientDriver

ClientDriver: ClientDriver.cpp Location.o Client.o Util.o
	g++ $(OPTS) -o a.out ClientDriver.cpp Location.o Client.o Util.o
	
Util.o: Util.cpp Util.h
	g++ $(OPTS) -c Util.cpp

Location.o: Location.cpp Location.h Util.h
	g++ $(OPTS) -c Location.cpp

Client.o: Client.cpp Client.h Location.h Util.h
	g++ $(OPTS) -c Client.cpp


clean:
	\rm -f NavigatorDriver *.o



