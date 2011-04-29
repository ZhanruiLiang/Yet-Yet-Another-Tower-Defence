objects = main.o gridmap.o creep.o
flags = -Wall -DDEBUG
compiler = g++

yyatd : main.o gridmap.o creep.o
	$(compiler) $(objects) -o yyatd

main.o : main.cpp gridmap.h creep.h
	$(compiler) $(flags) -c main.cpp

gridmap.o : gridmap.h gridmap.cpp
	$(compiler) $(flags) -c gridmap.cpp

creep.o : creep.h creep.cpp gridmap.h
	$(compiler) $(flags) -c creep.cpp

.PHONY : clean
clean :
	rm yyatd $(objects)
