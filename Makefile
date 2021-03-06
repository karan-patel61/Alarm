CC=gcc
CFLAGS=-lWarn -pedantic

alarm:	houseAlarm.o libmyifttt.a
	cc houseAlarm.o -L. -lmyifttt -lcurl -lwiringPi -o houseAlarm

tester: tester.o libmyifttt.a
	cc tester.o -L. -lmyifttt -lcurl -o tester

irtester: irtester.o 
	cc irtester.o -lwiringPi -o irtester

blink: blink.o 
	cc blink.o -lwiringPi -o blink

button: button.o 
	cc button.o -lwiringPi -o button

libmyifttt.a:	ifttt.o
	ar -rcs libmyifttt.a ifttt.o

ifttt.o: 	ifttt.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<
houseAlarm.o:	houseAlarm.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

tester.o:	tester.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

all:	tester irtester blink button alarm

clean:
	rm tester irtester *.o
