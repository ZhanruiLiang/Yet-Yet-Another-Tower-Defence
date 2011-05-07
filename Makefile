objects = clipper_main.o sbox.o pen.o clipper.o parser.o res_manager.o
flags = -g -Wall -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx -DDEBUG
compiler = g++

cltest: $(objects)
	$(compiler) $(flags) $(objects) -o cltest

clipper_main.o: clipper_main.cpp sbox.h pen.h clipper.h preinclude.h
	$(compiler) $(flags) -c clipper_main.cpp

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
	rm $(objects) cltest





