TARGET = sd
CC = gcc
SOURCES = main.c func.c
OBJECTS = $(SOURCES:.c=.o)
CFLAGS = -Wall -Wextra -c
.PHONY: clean all test
all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
%.o: %.c
	$(CC) $< $(CFLAGS) -o $@
clean:
	rm $(TARGET) $(OBJECTS)
test: $(TARGET)
	cat test.txt
	./$(TARGET) test.txt 's/$$/DOBAVLENSUF/'
	cat test.txt
	./$(TARGET) test.txt 's/^/DABAVLENPREF/'
	cat test.txt
	./$(TARGET) test.txt '/ETONADOUDALIT/d'
	cat test.txt
	./$(TARGET) test.txt 's/ETONADOZAMENIT/ZAMENENO/'
	cat test.txt
