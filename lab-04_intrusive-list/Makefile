.PHONY: all clean
all: lab-04_intrusive-list

CFLAGS = -Iinclude -Wall -Wextra -Werror -c

obj/:
	mkdir obj

obj/clist.o: src/clist.c include/clist.h | obj/
	gcc $(CFLAGS) src/clist.c -o obj/clist.o

obj/main.o: src/main.c obj/clist.o | obj/
	gcc $(CFLAGS) src/main.c -o obj/main.o

lab-04_intrusive-list: obj/main.o obj/clist.o | obj/
	gcc obj/main.o obj/clist.o -o lab-04_intrusive-list

clean:
	rm -rf obj/ lab-04_intrusive-list
