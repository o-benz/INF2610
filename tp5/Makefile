TP_NAME=GuerreDesChiffres

C_FILES=$(wildcard *.c)

C_FLAGS=-O2 -std=gnu17 -pthread
C_FLAGS+=-Wall -Wno-unused-result -Wno-unused-variable
C_FLAGS+=-Werror

.PHONY: all clean

all: $(TP_NAME)

$(TP_NAME): $(C_FILES)
	gcc $(C_FLAGS) -o $@ $^

clean:
	rm -f $(TP_NAME)
