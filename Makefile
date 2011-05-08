objects = sbox.o pen.o clipper.o parser.o res_manager.o graphic_engine.o\
		  graTest.o
flags = -g -Wall -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx -DDEBUG
compiler = g++

graTest: $(objects) 
	$(compiler) $(flags) $(objects) -o graTest

graTest.o: graTest.cpp graphic_engine.h clipper.h sbox.h preinclude.h
	$(compiler) $(flags) -c graTest.cpp

graphic_engine.o: graphic_engine.cpp graphic_engine.h sbox.h clipper.h preinclude.h
	$(compiler) $(flags) -c graphic_engine.cpp

sbox.o : sbox.cpp sbox.h preinclude.h
	$(compiler) $(flags) -c sbox.cpp

pen.o : pen.cpp sbox.h pen.h preinclude.h
	$(compiler) $(flags) -c pen.cpp

clipper.o : clipper.cpp clipper.h parser.h sbox.h sysinfo.h preinclude.h\
	res_manager.h
	$(compiler) $(flags) -c clipper.cpp

parser.o : parser.cpp parser.h
	$(compiler) $(flags) -c parser.cpp

res_manager.o : res_manager.cpp res_manager.h preinclude.h
	$(compiler) $(flags) -c res_manager.cpp

.PHONY: clean

clean:
	rm $(objects) graTest





