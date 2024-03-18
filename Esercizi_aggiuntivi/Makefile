CFLAGS += -Wall -Wextra -std=c11 -pedantic
CFLAGS += -g
CFLAGS += -I./include
LDFLAGS += -L./lib
LDLIBS += -lupoalglib -lm


.PHONY: all clean

all: test/esercizio8 test/esercizio9 test/esercizio10 test/esercizio11 test/esercizio12

test/esercizio8: test/esercizio8.o exam.o

test/esercizio9: test/esercizio9.o exam.o

test/esercizio10: test/esercizio10.o exam.o

test/esercizio11: test/esercizio11.o exam.o

test/esercizio12: test/esercizio12.o exam.o

clean:
	$(RM) test/esercizio8
	$(RM) test/esercizio9
	$(RM) test/esercizio10
	$(RM) test/esercizio11
	$(RM) test/esercizio12
	$(RM) *.o test/*.o
