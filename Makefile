all: add-nbo

add-nbo : main.o nhcvt.o
	g++ main.o nhcvt.o -o add-nbo

main.o : main.cpp nhcvt.h
	g++ main.cpp -c -o main.o

nhcvt.o : nhcvt.S
	g++ nhcvt.S -c -o nhcvt.o

clean :
	rm -f *.o