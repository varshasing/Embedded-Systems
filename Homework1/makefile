# compiler and flags
CC = gcc
CFLAGS = -Wall -Werror

TARGET = BitApp
SRCS = main.c bits.c
OBJS = $(SRCS:.c=.o)
DEP = bits.h

# default rule
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

# clean rule
clean:
	rm -f $(OBJS) $(TARGET)