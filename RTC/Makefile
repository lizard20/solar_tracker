
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -pedantic -fmax-errors=10
LIBS := -lm

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
HDRS := $(wildcard *.h)
BIN := test_RTC

all: $(BIN)

$(BIN): $(OBJS)
	@echo "Compiling ..." 
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

%.o: %.c
	@echo "Compiling ..." 
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

run: ${BIN}
	./${BIN}

git:
	@echo "github updating ..."
	git add .
	git commit -m "$m"
	git push

clean:
	@echo "Cleaning ..." 
	$(RM) -r ${BIN} ${OBJS}


:PHONY: all run clean



