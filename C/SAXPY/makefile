saxpy: saxpy.o millisecond.o
	cc -o saxpy saxpy.o -lmillisecond -L.

millisecond.o: millisecond.c
	cc -c millisecond.c
	ar -cr libmillisecond.a millisecond.o

saxpy.o: saxpy.c
	cc -c saxpy.c

clear:
	rm *.o

run:
	./saxpy
