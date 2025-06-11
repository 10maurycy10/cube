OBJS=shape.c.o screen.c.o main.c.o
HEADERS=shape.h functions.h screen.h
LINKFLAGS=-lm

%.c.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -g -Wall

3d: $(OBJS)
	$(CC) $(LIBS) $(OBJS) -o 3d -g $(LINKFLAGS)

clean: 
	-rm $(OBJS) 3d
