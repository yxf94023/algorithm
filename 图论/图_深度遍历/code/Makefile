object = stack_list.o graph_dfs.o
target = graph_dfs

$(target) : $(object)
	g++ -g -o $(target) $(object)
	
.PHONY: clean
clean:
	-rm $(target) $(object)