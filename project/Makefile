CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h -I../lcdLib
LDFLAGS		        = -L../lib -L/opt/ti/msp430_gcc/include/
CC              	= msp430-elf-gcc
AS              	= msp430-elf-gcc -mmcu=${CPU} -c

COMMON_OBJECTS  	= main.o statemachines.o switch.o buzzer.o

all: project.elf

project.elf: ${COMMON_OBJECTS} wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

main.o: main.c statemachines.h switch.h buzzer.h
	${CC} ${CFLAGS} -c main.c -o main.o

statemachines.o: statemachines.c statemachines.h switch.h buzzer.h
	${CC} ${CFLAGS} -c statemachines.c -o statemachines.o

switch.o: switch.c switch.h
	${CC} ${CFLAGS} -c switch.c -o switch.o

wdt_handler.o: wdt_handler.s
	${AS} wdt_handler.s -o wdt_handler.o

load: project.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf *~
