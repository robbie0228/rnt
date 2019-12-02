CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla -I/usr/X11/include
EXEC = RAIInet
OBJECTS = main.o game.o grid.o cell.o player.o link.o subject.o text_display.o graphics_display.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -L/usr/X11/lib

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
