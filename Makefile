objects = main.o grid_map.o creep.o creep_factory.o
flags = -Wall -DDEBUG
compiler = g++

yyatd : $(objects)
	$(compiler) $(objects) -o yyatd

main.o : main.cpp grid_map.h creep.h
	$(compiler) $(flags) -c main.cpp

grid_map.o : grid_map.h grid_map.cpp
	$(compiler) $(flags) -c grid_map.cpp

creep.o : creep.h creep.cpp grid_map.h
	$(compiler) $(flags) -c creep.cpp

creep_factory.o : creep_factory.h creep_factory.cpp creep_config.h
	$(compiler) $(flags) -c creep_factory.cpp

.PHONY : clean
clean :
	rm yyatd $(objects)
