objects = main.o gridmap.o
flags = -Wall -DDEBUG
compiler = g++

yyatd : main.o gridmap.o
	$(compiler) $(objects) -o yyatd

main.o : main.cpp gridmap.h
	$(compiler) $(flags) -c main.cpp

gridmap.o : gridmap.cpp gridmap.h
	$(compiler) $(flags) -c gridmap.cpp

.PHONY : clean
clean :
	rm yyatd $(objects)
