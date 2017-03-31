CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -g -O3

main: subject.o tile.o textdisplay.o builder.o path.o road.o gameboard.o loadeddice.o fairdice.o address.o basement.o house.o tower.o main.o
	${CXX} ${CXXFLAGS} ${^} -o Constructor

main.o: gameboard.h main.cc
	${CXX} ${CXXFLAGS} -c main.cc

subject.o: subscriptions.h subject.h subject.cc
	${CXX} ${CXXFLAGS} -c subject.cc

tile.o: subscriptions.h subject.h observer.h tile.h tile.cc
	${CXX} ${CXXFLAGS} -c tile.cc

textdisplay.o: observer.h textdisplay.h textdisplay.cc
	${CXX} ${CXXFLAGS} -c textdisplay.cc

gameboard.o: tile.h textdisplay.h abstractpath.h gameboard.h gameboard.cc
	${CXX} ${CXXFLAGS} -c gameboard.cc

address.o: abstractaddress.h address.h address.cc
	${CXX} ${CXXFLAGS} -c address.cc

basement.o: residence.h basement.h basement.cc
	${CXX} ${CXXFLAGS} -c basement.cc

house.o: residence.h house.h house.cc
	${CXX} ${CXXFLAGS} -c house.cc

tower.o: residence.h tower.h tower.cc
	${CXX} ${CXXFLAGS} -c tower.cc

builder.o: observer.h builder.h builder.cc
	${CXX} ${CXXFLAGS} -c builder.cc

path.o: abstractpath.h path.h path.cc
	${CXX} ${CXXFLAGS} -c path.cc

road.o: abstractpath.h road.h road.cc
	${CXX} ${CXXFLAGS} -c road.cc

fairdice.o: dice.h fairdice.h fairdice.cc
	${CXX} ${CXXFLAGS} -c fairdice.cc

loadeddice.o: dice.h loadeddice.h loadeddice.cc
	${CXX} ${CXXFLAGS} -c loadeddice.cc

clean:
	rm *o 

.PHONY: clean
