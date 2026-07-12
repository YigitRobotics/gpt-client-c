CC = gcc

CFLAGS = -Wall -Wextra -g -Iinclude

TARGET = gptask

SRCS = gpt.c core/api_key.c core/api_request.c core/log.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lcurl

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean