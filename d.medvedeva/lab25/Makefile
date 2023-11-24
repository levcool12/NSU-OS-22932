main: main.o to_upper
	gcc main.o -o main

to_upper: to_upper.o
	gcc to_upper.o -o to_upper

main.o: main.c
	gcc -Wall -c main.c

to_upper.o: to_upper.c
	gcc -Wall -c to_upper.c

clean:
	rm main to_upper *.o
