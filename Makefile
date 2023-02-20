OUTPUT=project_1
CFLAGS=-g -Wall -Werror -fsanitize=address -std=c99 \
       -Wno-unused-variable
LFLAGS=-lm
OBJ = memgrind.o mymalloc.o
PROGRAM = memgrind

all: $(OBJ)
	gcc $(CFLAGS) -o $(PROGRAM) $(OBJ) $(LFLAGS)

%: %.c
	gcc $(CFLAGS) -o $@ $< $(LFLAGS)

clean:
	rm -f *.o $(PROGRAM)
