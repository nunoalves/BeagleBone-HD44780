CFLAGS= -Wall -Wshadow -Wwrite-strings -Wsign-compare -Wfloat-equal \
	-Wmissing-noreturn -Wbad-function-cast \
	-Wmissing-prototypes -Winline -Wredundant-decls -O3

all: example_04 example_03 example_02

example_04: example_04.o beagle_gpio.o beagle_hd44780.o
	gcc $(CFLAGS) -o $@ $+
	strip $@

example_03: example_03.o beagle_gpio.o beagle_hd44780.o
	gcc $(CFLAGS) -o $@ $+
	strip $@

example_02: example_02.o beagle_gpio.o beagle_hd44780.o
	gcc $(CFLAGS) -o $@ $+
	strip $@

example_01: example_01.o beagle_gpio.o beagle_hd44780.o
	gcc $(CFLAGS) -o $@ $+
	strip $@

clean:
	rm -f a.out *.o example_04 example_03 example_02 example_01

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $+
