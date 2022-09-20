.PHONY: all clean
all: lab-02_cstrings

CFLAGS = -Iinclude -Wall -Wextra -Werror -c

obj/:
	mkdir obj

obj/str.o: src/str.c include/str.h | obj/
	gcc $(CFLAGS) src/str.c -o obj/str.o

obj/test_str.o: src/test_str.c include/test_str.h obj/str.o | obj/
	gcc $(CFLAGS) src/test_str.c -o obj/test_str.o

obj/test.o: obj/test_str.o | obj/
	gcc $(CFLAGS) src/test.c -o obj/test.o

lab-02_cstrings: obj/str.o obj/test_str.o obj/test.o | obj/
	gcc obj/str.o obj/test_str.o obj/test.o -o lab-02_cstrings

clean:
	rm -rf obj/ lab-02_cstrings
