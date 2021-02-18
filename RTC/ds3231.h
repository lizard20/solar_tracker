#ifndef __DS3231_H__
#define __DS3231_H__

//#define OPENI2C 1

#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <stdlib.h>


#define BUFFER_SIZE 19
#define RTC_ADDRESS 0x68

// the time is in the registers in decimal form
#define BCD2DEC(b) ((b/16)*10 + (b%16))

struct RTC
{
	int fd;
	char buf[BUFFER_SIZE];
};

typedef struct RTC rtc_t;
// prototypes
int open_i2c_rtc ( rtc_t* );
int connect_rtc ( rtc_t* );
int read_rtc ( rtc_t* );
void print_rtc( rtc_t* );

#endif 
