objects_gra = sbox.o \
			  pen.o \
			  clipper.o \
			  parser.o \
			  graphic_engine.o
objects_ui = uicom.o\
			 ui_engine.o\
			 state.o

objects_game = main3.o \
			   grid_map.o \
			   creep.o \
			   creep_factory.o \
			   tower.o \
			   tower_factory.o \
			   game_engine.o \
			   bullet.o \
			   bullet_factory.o

flags = -g -DDEBUG -Wall -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx -std=c++0x
compiler = g++

#-------------------------------------------------------------------
yyatd : $(objects_game) $(objects_gra) $(objects_ui) 
	$(compiler) $(flags) $(objects_game) $(objects_gra) $(objects_ui) -o yyatd

main3.o : main3.cpp grid_map.h creep.h\
	creep_config.h creep_factory.h\
	tower.h tower_config.h tower_factory.h\
	direction.h\
	graphic_engine.h clipper.h sbox.h preinclude.h\
	uicom.h ui_engine.h
	$(compiler) $(flags) -c main3.cpp

uicom.o : uicom.cpp uicom.h clipper.h preinclude.h
	$(compiler) $(flags) -c uicom.cpp

state.o : state.cpp state.h preinclude.h
	$(compiler) $(flags) -c state.cpp

ui_engine.o : ui_engine.cpp graphic_engine.h ui_engine.h clipper.h state.h
	$(compiler) $(flags) -c ui_engine.cpp

graphic_engine.o: graphic_engine.cpp graphic_engine.h sbox.h clipper.h preinclude.h
	$(compiler) $(flags) -c graphic_engine.cpp

sbox.o : sbox.cpp sbox.h preinclude.h
	$(compiler) $(flags) -c sbox.cpp

pen.o : pen.cpp sbox.h pen.h preinclude.h
	$(compiler) $(flags) -c pen.cpp

clipper.o : clipper.cpp clipper.h parser.h sbox.h sysinfo.h preinclude.h
	$(compiler) $(flags) -c clipper.cpp

parser.o : parser.cpp parser.h
	$(compiler) $(flags) -c parser.cpp
#-------------------------------------------------------------------
grid_map.o : grid_map.h grid_map.cpp
	$(compiler) $(flags) -c grid_map.cpp

creep.o : creep.h creep.cpp grid_map.h
	$(compiler) $(flags) -c creep.cpp

creep_factory.o : creep_factory.h creep_factory.cpp creep_config.h
	$(compiler) $(flags) -c creep_factory.cpp

tower.o : tower.h tower.cpp creep.h
	$(compiler) $(flags) -c tower.cpp

tower_factory.o : tower_factory.h tower_factory.cpp tower_config.h
	$(compiler) $(flags) -c tower_factory.cpp

bullet.o : bullet.h bullet.cpp
	$(compiler) $(flags) -c bullet.cpp

bullet_factory.o : bullet_factory.h bullet_factory.cpp bullet_config.h \
				   tower.h
	$(compiler) $(flags) -c bullet_factory.cpp

game_engine.o : game_engine.h game_engine.cpp\
	grid_map.h tower.h tower_config.h tower_factory.h \
			    creep.h creep_config.h creep_factory.h
	$(compiler) $(flags) -c game_engine.cpp

.PHONY: clean

clean:
	-rm $(objects_gra) $(objects_game) $(objects_ui) yyatd

