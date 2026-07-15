CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -g -Iinclude
LDLIBS =

CFLAGS += $(shell pkg-config --cflags libcjson libcurl lowdown)
LDLIBS += $(shell pkg-config --libs libcjson libcurl lowdown)

TARGET = canis

SRCS = main.c $(wildcard core/*.c banner/*.c)
OBJS = $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)