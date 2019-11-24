Gaus: Gaus.o millisecond.o
	cc -o Gaus Gaus.o -lmillisecond -L.

millisecond.o: millisecond.c
	cc -c millisecond.c
	ar -cr libmillisecond.a millisecond.o

Gaus.o: Gaus.c
	cc -c Gaus.c

clear:
	rm *.o

run:
	./Gaus
