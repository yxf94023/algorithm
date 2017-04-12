objects = graph_bfs.o queue_list.o
target = graph_bfs

CC = g++
CFLAGS = -g
CPPFLAGS = -g

$(target) : $(objects)
	$(CC) -o $(target) $(objects)
	
.PHONY : clean 
clean:
	-rm $(target) $(objects)
