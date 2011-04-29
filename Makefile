objects = main.o grid_map.o creep.o
flags = -Wall -DDEBUG
compiler = g++

yyatd : main.o grid_map.o creep.o
	$(compiler) $(objects) -o yyatd

main.o : main.cpp grid_map.h creep.h
	$(compiler) $(flags) -c main.cpp

grid_map.o : grid_map.h grid_map.cpp
	$(compiler) $(flags) -c grid_map.cpp

creep.o : creep.h creep.cpp grid_map.h
	$(compiler) $(flags) -c creep.cpp

.PHONY : clean
clean :
	rm yyatd $(objects)
