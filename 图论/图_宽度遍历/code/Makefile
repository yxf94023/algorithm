graph_bfs:graph_bfs.o queue_list.o
	g++ -o graph_bfs graph_bfs.o queue_list.o

graph_bfs.o:graph_bfs.cc queue_list.h graph_bfs.h
	g++ -g -c graph_bfs.cc

queue_list.o:queue_list.cc queue_list.h
	g++ -g -c queue_list.cc
	
clean:
	rm graph_bfs *.o