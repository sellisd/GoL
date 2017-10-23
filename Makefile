UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
        CC=g++
    endif
    ifeq ($(UNAME_S),Darwin)
        CC=clang++
    endif
CFLAGS=-lgsl -lgslcblas
DEPS = entropy.h gameOfLife.h ca.h generateStatic.h randomv.h lodepng.h system.h
run:	main.cpp entropy.cpp gameOfLife.cpp ca.cpp generateStatic.cpp randomv.cpp lodepng.cpp system.cpp
	$(CC) -Wall -o run main.cpp entropy.cpp gameOfLife.cpp ca.cpp generateStatic.cpp randomv.cpp system.cpp lodepng.cpp $(CFLAGS)
