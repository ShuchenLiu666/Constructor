CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -g -Wall -MMD
OBJECTS = main.o ctorgame.o board.o  player.o strategy.o dice.o subject.o tile.o vertex.o edge.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = constructor

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

.PHONY: clean

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
