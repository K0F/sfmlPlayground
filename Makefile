
.PHONY: all

all:
	g++ -c Window.cpp
	g++ Window.o -o hello -lsfml-graphics -lsfml-window -lsfml-system -lGLU -lGL

clean:
	rm Window.o hello
