object = graph_prim.o
target = graph_prim

CC = g++
CFLAGS = -g
CPPFLAGS = -g

$(target) : $(object)
	$(CC) -o $(target) $(object)
	
.PHONY: clean
clean:
	-rm $(target) $(object)