.PHONY: all clean
all: lab-03_mergesort

CFLAGS = -Iinclude -Wall -Wextra -Werror -c

obj/:
	mkdir obj

obj/mergesort.o: src/mergesort.c include/mergesort.h | obj/
	gcc $(CFLAGS) src/mergesort.c -o obj/mergesort.o

obj/main.o: src/main.c obj/mergesort.o | obj/
	gcc $(CFLAGS) src/main.c -o obj/main.o

lab-03_mergesort: obj/mergesort.o obj/main.o | obj/
	gcc obj/mergesort.o obj/main.o -o lab-03_mergesort

clean:
	rm -rf obj/ lab-03_mergesort
