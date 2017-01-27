OPENSSL_INCLUDE = -I/Users/julien/Documents/M2Mi/openssl/include/
OPENSSL_LIB = -L/Users/julien/Documents/M2Mi/openssl/lib/


CFLAGS=-Wall -g $(OPENSSL_INCLUDE)
LDFLAGS=$(OPENSSL_LIB) -lcrypto

SOURCES=$(wildcard src/main/c/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TARGET=bin/cmac

all: $(TARGET)

$(TARGET): build $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

build:
	@mkdir -p bin

clean:
	rm -rf bin/https src/main/c/*.o