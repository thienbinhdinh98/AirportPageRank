# Add all object files needed for compiling:
EXENAME = flight
TEST = test
OBJS = main.o airportData.o edge.o vertex.o graph.o
CC = clang++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm
CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic


output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(EXENAME)

main.o : main.cpp airportData.h graph.h vertex.h
	$(CC) $(CFLAGS) main.cpp

vertex.o : vertex.h vertex.cpp
	$(CC) $(CFLAGS) vertex.cpp

edge.o : edge.cpp edge.h vertex.h
	$(CC) $(CFLAGS) edge.cpp

airportData.o : airportData.cpp airportData.h edge.h vertex.h
	$(CC) $(CFLAGS) airportData.cpp

graph.o : graph.h graph.cpp vertex.h edge.h airportData.h
	$(CC) $(CFLAGS) graph.cpp

catchmain.o : cs225/catch/catchmain.cpp cs225/catch/catch.hpp
	$(CXX) $(CXXFLAGS) cs225/catch/catchmain.cpp

tests-unit.o : tests/tests-unit.cpp cs225/catch/catch.hpp airportData.cpp airportData.h edge.cpp edge.h graph.cpp graph.h vertex.cpp vertex.h
	$(CXX) $(CXXFLAGS) tests/tests-unit.cpp airportData.cpp edge.cpp graph.cpp vertex.cpp

test: output_msg catchmain.o tests-unit.o 
	$(LD) catchmain.o tests-unit.o airportData.o graph.o vertex.o edge.o $(LDFLAGS) -o test

clean :
	\rm *.o flight test