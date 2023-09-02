TARGET = p
CC = gcc
BUILD_PATH = ./

TARGET_PATH = $(BUILD_PATH)$(TARGET)

$(shell mkdir -p $(BUILD_PATH))


$(TARGET):main.c
	$(CC) -o $(TARGET_PATH) $^

.PHONY:clean

clean:
	-rm $(TARGET_PATH)

