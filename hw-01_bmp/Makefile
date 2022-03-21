.PHONY: all clean
all: hw-01_bmp

CFLAGS = -Iinclude -Wall -Wextra -Werror -c

obj/:
	mkdir obj

obj/bmp.o: src/bmp.c include/bmp.h | obj/
	gcc $(CFLAGS) src/bmp.c -o obj/bmp.o
	
obj/stego.o: src/stego.c include/stego.h obj/bmp.o | obj/
	gcc $(CFLAGS) src/stego.c -o obj/stego.o

obj/main.o: src/main.c obj/bmp.o | obj/
	gcc $(CFLAGS) src/main.c -o obj/main.o

hw-01_bmp: obj/main.o obj/bmp.o obj/stego.o | obj/
	gcc obj/main.o obj/bmp.o obj/stego.o -o hw-01_bmp

clean:
	rm -rf obj/ hw-01_bmp
