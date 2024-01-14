CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

program: Main.cpp LibrarySystem.cpp LibrarySystem.h
	$(CXX) $(CXXFLAGS) -o program Main.cpp LibrarySystem.cpp

clean:
	rm -f *.o
	rm -f program
