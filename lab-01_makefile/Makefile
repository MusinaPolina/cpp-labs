.PHONY: all clean
all: lab-01_makefile

CFLAGS = -Iinclude -Wall -Wextra -Werror -c

obj/:
	mkdir obj

obj/io.o: src/io.c include/io.h | obj/ 
	gcc $(CFLAGS) src/io.c -o obj/io.o

obj/util.o: src/util.c include/util.h obj/io.o | obj/
	gcc $(CFLAGS) src/util.c -o obj/util.o

obj/algorithm.o: src/algorithm.c include/algorithm.h obj/util.o obj/io.o | obj/
	gcc $(CFLAGS) src/algorithm.c -o obj/algorithm.o

obj/main.o: src/main.c obj/algorithm.o obj/ obj/util.o obj/io.o | obj/
	gcc $(CFLAGS) src/main.c -o obj/main.o

lab-01_makefile: obj/main.o obj/algorithm.o obj/util.o obj/io.o
	gcc obj/io.o obj/util.o obj/algorithm.o obj/main.o -o lab-01_makefile

clean:
	rm -rf obj/ lab-01_makefile
