
.PHONY: all

all:
	g++ -c Hello.cpp -o hello.o
	g++ hello.o -o hello -lsfml-graphics -lsfml-window -lsfml-system -lGLU -lGL

clean:
	rm hello.o hello
