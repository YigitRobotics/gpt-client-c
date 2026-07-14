CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -g \
          -Iinclude \
          -I/opt/homebrew/include

LDFLAGS = -L/opt/homebrew/lib

LDLIBS = -lcjson -lcurl

TARGET = canis

SRCS = main.c $(wildcard core/*.c)
OBJS = $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)