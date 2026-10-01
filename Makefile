CC ?= clang
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic
TARGET = drone-status-struct

.PHONY: all run clean

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
