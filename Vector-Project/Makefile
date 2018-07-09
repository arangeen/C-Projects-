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

OBJECTS = csc340_vector_test.o

csc340_vector_test: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJECTS): csc340_vector.h

clean:
	rm -f $(OBJECTS) csc340_vector_test
