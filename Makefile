OBJS=shape.c.o screen.c.o
LINKFLAGS=-lm

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -g -Wall

3d: $(OBJS)
	$(CC) $(LINKFLAGS) $(LIBS) $(OBJS) -o 3d -g

clean: 
	-rm $(OBJS) 3d
