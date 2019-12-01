CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
EXEC = raiinet
OBJECTS = main.o game.o grid.o cell.o player.o link.o subject.o text_display.o graphicsDisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -L/usr/X11/lib -I/usr/X11/include

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
