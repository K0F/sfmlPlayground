
.PHONY: clean all

all:
	g++ -c src/Hello.cpp -o bin/hello.o
	g++ bin/hello.o -o bin/hello -lsfml-graphics -lsfml-window -lsfml-system -lGLU -lGL
	cp -r assets bin/assets
clean:
	rm -rf bin/*
run: .PHONY
	cd bin/ && ./hello
