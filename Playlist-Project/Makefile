################################################################################
## Makefile
## Copyright (C) 2018 Garo Bournoutian
## San Francisco State University
##
## DO *NOT* EDIT THIS FILE
##
## This file is similar to how I will run your code, so ensure you are able to
## compile and run your code on a modern Linux system with g++. I'm using g++
## version 7.3, but other modern versions are fine as long as they support C++11
################################################################################

CXX = g++
CXXFLAGS = -std=c++11 -Wall

OBJECTS = playlist.o playlist_test.o

playlist_test: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJECTS): playlist.h

clean:
	rm -f $(OBJECTS) playlist_test
