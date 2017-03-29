CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -g -O0

main: subject.o tile.o textdisplay.o gameboard.o builder.o residence.o road.o main.o
	${CXX} ${CXXFLAGS} ${^} -o Constructor

main.o: gameboard.h main.cc
	${CXX} ${CXXFLAGS} -c main.cc

subject.o: subscriptions.h subject.h subject.cc
	${CXX} ${CXXFLAGS} -c subject.cc

tile.o: subscriptions.h subject.h observer.h tile.h tile.cc
	${CXX} ${CXXFLAGS} -c tile.cc

textdisplay.o: observer.h textdisplay.h textdisplay.cc
	${CXX} ${CXXFLAGS} -c textdisplay.cc

gameboard.o: tile.h textdisplay.h gameboard.h gameboard.cc
	${CXX} ${CXXFLAGS} -c gameboard.cc

address.o: abstractaddress.h address.h address.cc
	${CXX} ${CXXFLAGS} -c address.cc

residence.o: abstractaddress.h residence.h residence.cc
	${CXX} ${CXXFLAGS} -c residence.cc

builder.o: observer.h builder.h builder.cc
	${CXX} ${CXXFLAGS} -c builder.cc

path.o: abstractpath.h path.h path.cc
	${CXX} ${CXXFLAGS} -c path.cc

road.o: abstractpath.h road.h road.cc
	${CXX} ${CXXFLAGS} -c road.cc

clean:
	rm *o *.gch

.PHONY: clean
