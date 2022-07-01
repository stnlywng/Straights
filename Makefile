CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = card.o gameManager.o main.o players.o table.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${DEPENDS} ${OBJECTS} ${EXEC}
