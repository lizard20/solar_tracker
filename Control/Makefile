#Makefile for control

CC := gcc
default: all
LIBS :=  -lm
FLAGS := -Wall -Wextra -std=c11 -pedantic -fmax-errors=10

all: control 
	@echo "SUCCESSFUL COMPILATION :)"

control: control.o control_fsm.o 
	$(CC) -o control control.o control_fsm.o ../ADC/ads1115.o ../SPA/spa.o ../RTC/ds3231.o -Wall $(LIBS) $(FLAGS)
	@echo "control made"

control.o: control.c control.h prototypes.h
	$(CC) -c control.c -Wall $(LIBS) $(FLAGS)
	@echo "compiling .o made"

control_fsm.o: control_fsm.c control.h prototypes.h ../ADC/ads1115.h ../ADC/ads1115.c ../SPA/spa.c ../SPA/spa.h ../RTC/ds3231.c ../RTC/ds3231.h
	$(CC) -c control_fsm.c -Wall $(LIBS) $(FLAGS)

run:
	./control

clean:
	rm  control *.o 
	@echo "deleting  made"
