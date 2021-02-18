#ifndef __DAC_H__
#define __DAC_H__

#include <stdio.h>
#include <sys/types.h> // open
#include <sys/stat.h>  // open
#include <unistd.h>    // read/write usleep
#include <stdlib.h>    // exit
#include <inttypes.h>  // uint8_t, etc
#include <linux/i2c-dev.h> // I2C bus definitions
#include <sys/fcntl.h> 
#include <sys/ioctl.h>      


#define ADS_ADDRESS  0x48
#define N_INPUTS 4
#define VPS (6.144/32768.0)

// Bits [15:8]
// single shot

#define SSHOT (0x01 << 15)
// 100 ANC0; 101 ANC1; 110 ANC2; 111 ANC3
#define AIN0 (0x04 << 12)
#define AIN1 (0x05 << 12)
#define AIN2 (0x06 << 12)
#define AIN3 (0x07 << 12)

#define PGA (0x00 << 9)

// 0 - contnuos
// 1 - single shot and down
#define MODE (0x01 << 8)

// Bits [7:0]
// Data Rate, 3 bits
#define DRATE (0x04 << 5)

// Comp mode, 1 bit
#define COMP_MODE ( 0x0 << 4)

// Comparatro polatiry, 1 bit
#define COMP_POL (0x00 << 3)

// Latching comparator, 1 bit
#define COMP_LAT (0x0 << 2)

// Comparator queue, 2 bits
#define COMP_Q (0x01) 

// dac_t  data type
typedef struct ADC adc_t;
struct ADC
{
	int fd;
	union 
	{
		uint16_t write16_buff [2];
		uint8_t  write8_buff  [3];
	};
	uint8_t read_buff[2];
//	int16_t int_val;
	float float_val[ N_INPUTS];
//	uint16_t ain;

	uint16_t ain[N_INPUTS]; 	// analog inputs register adresses
	int16_t int_val[N_INPUTS]; 	// integer analog values
};

/***** Prototypes **********/
int open_i2c_ads (adc_t*);
int connect_ads (adc_t*);
void config_ads ( adc_t* );
int read_ads ( adc_t*  );
void print_ads ( adc_t*  );


#endif 
