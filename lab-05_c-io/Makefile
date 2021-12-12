.PHONY: all clean
all: lab-05_c-io

CFLAGS = -Iinclude -Wall -Wextra -Werror -c

obj/:
	mkdir obj

obj/clist.o: src/clist.c include/clist.h | obj/
	gcc $(CFLAGS) src/clist.c -o obj/clist.o

obj/point_list.o: src/point_list.c include/point_list.h obj/clist.o | obj/
	gcc $(CFLAGS) src/point_list.c -o obj/point_list.o

obj/main.o: src/main.c obj/point_list.o | obj/
	gcc $(CFLAGS) src/main.c -o obj/main.o

lab-05_c-io: obj/main.o obj/point_list.o obj/clist.o | obj/
	gcc obj/main.o obj/point_list.o obj/clist.o -o lab-05_c-io

clean:
	rm -rf obj/ lab-05_c-io
