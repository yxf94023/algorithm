objects = game_bash.o
target = game_bash

CC = g++
CFLAGS = -g
CPPFLAGS = -g

$(target) : $(objects)
	$(CC) -o $(target) $(objects)
	
.PHONY : clean
clean :
	-rm $(target) $(objects)
