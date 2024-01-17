CXX = g++
EXEC = main.exe

build: compileSource compileObject
start: compileSource compileObject run clean

compileSource: src/Main.cpp
	$(CXX) -c src/*.cpp

compileObject: Main.o
	$(CXX) *.o -o bin/$(EXEC)

run: bin/$(EXEC)
	./bin/$(EXEC)

clean:
	rm *.o