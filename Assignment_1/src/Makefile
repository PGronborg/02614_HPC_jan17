CC = gcc
OBJECT = main.o matoper.o datatools.o
OPT = -g -O3
WARN = -Wall
CFLAGS = $(OPT) $(WARN)
LIB = -lm -L /usr/lib64/atlas -lcblas
TARGET	= assign1.$(CC)


$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) -o $@ $(OBJECT) $(LIB)

clean: 
	/bin/rm -f *.o core

realclean: clean
	@/bin/rm -f $(TARGET)
