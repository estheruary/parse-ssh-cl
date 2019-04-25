CC=gcc
NAME=parse-ssh-cl
CFLAGS=-I.
DEPS = utils.h
OBJ = utils.o main.o
PREFIX = $(HOME)/.local

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core *~


$(NAME).tar.gz: $(NAME)
	tar -czf $(NAME).tar.gz $(NAME)

.PHONY: release

release: $(NAME).tar.gz


$(PREFIX)/bin/$(NAME): $(NAME)
	install -m 0755 $(NAME) "$(PREFIX)/bin/$(NAME)"

.PHONY: install

install: $(PREFIX)/bin/$(NAME)
