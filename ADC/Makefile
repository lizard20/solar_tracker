
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -pedantic -fmax-errors=10
LIBS := -lm

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
HDRS := $(wildcard *.h)
BIN := test_ads1115

all: $(BIN)

$(BIN): $(OBJS)
	@echo "Compiling ..." 
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

%.o: %.c %.h
	@echo "Compiling ..." 
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

run:
	./${BIN}

git:
	@echo "github updating ..."
	git add .
	git commit -m "$m"
	git push

clean:
	@echo "Cleaning ..." 
	$(RM) -r ${BIN} ${OBJS}


:PHONY: all run



