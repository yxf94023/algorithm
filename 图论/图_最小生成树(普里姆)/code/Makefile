object = graph_prim.o
target = graph_prim

$(target) : $(object)
	g++ -o $(target) -g -O0 $(object)
	
.PHONY: clean
clean:
	-rm $(target) $(object)