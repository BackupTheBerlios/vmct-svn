CC=gcc
CFLAGS=-Wall
CPPFLAGS=-Wall

OBJ=testsi.o test1.o snippets.o ConvertUTF.o

lib: snippets.o
	ar rcv libini.a snippets.o
	ranlib libini.a

testsi: $(OBJ)
	g++ -o testsi -lstdc++ $(OBJ)

clean:
	rm -f testsi $(OBJ)

data:
	sed 's/\r\n$$/\n/g' < test1-expected.ini > unix.out
	mv unix.out test1-expected.ini
