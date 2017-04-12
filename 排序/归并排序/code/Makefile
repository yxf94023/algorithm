object = main.o merge_sort.o
target = merge_sort

CFLAGS = -g
CPPFLAGS = -g
CC = g++

$(target) : $(object)
	$(CC) -o $(target) $(object)
	
.PHONY: clean
clean:
	-rm $(target) $(object)
	