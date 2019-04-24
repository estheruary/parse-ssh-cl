CC=gcc
CFLAGS=-I.
DEPS = utils.h
OBJ = utils.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

parse-ssh-cl: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core *~
