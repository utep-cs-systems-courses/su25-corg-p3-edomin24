all: main.elf

CPU       = msp430g2553
CFLAGS    = -mmcu=${CPU} -Os -I../h
LDFLAGS   = -L/opt/ti/msp430_gcc/include -L../lib
CC        = msp430-elf-gcc
AS        = msp430-elf-as
AR        = msp430-elf-ar

LCDLIB_OBJS = \
	../lcdLib/font-11x16.o \
	../lcdLib/font-8x12.o \
	../lcdLib/font-5x7.o \
	../lcdLib/lcdutils.o \
	../lcdLib/lcddraw.o

../lib/libLcd.a: $(LCDLIB_OBJS)
	$(AR) crs $@ $^

../lcdLib/%.o: ../lcdLib/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

OBJS = main.o wdt_handler.o
main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

wdt_handler.o: wdt_handler.s
	$(AS) -mmcu=${CPU} -o $@ $<

main.elf: $(OBJS) ../lib/libLcd.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lTimer

load: main.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
