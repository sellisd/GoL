CC=clang++
CFLAGS=-lgsl -lgslcblas
DEPS = entropy.h gameOfLife.h generateStatic.h randomv.h lodepng.h system.h
run:	main.cpp entropy.cpp gameOfLife.cpp generateStatic.cpp randomv.cpp lodepng.cpp system.cpp
	$(CC) -Wall -o run main.cpp entropy.cpp gameOfLife.cpp generateStatic.cpp randomv.cpp system.cpp lodepng.cpp $(CFLAGS)