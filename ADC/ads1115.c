#include "ads1115.h"

int
open_i2c_ads ( adc_t* ptr )
{
	if (( ptr -> fd = open("/dev/i2c-1", O_RDWR)) < 0) 
	{
		printf("Error: Couldn't open device! %d\n", ptr -> fd);
		return 1;
	}
	return 0;
}

int
connect_ads ( adc_t* ptr )
{
	if (ioctl(ptr -> fd, I2C_SLAVE, ADS_ADDRESS) < 0 )
	{
		printf("Error: Couldn't find device on address!\n");
		return 1;
	}
	return 0;
}

void
config_ads ( adc_t* ptr )
{
	ptr -> write8_buff [0] = 1;    // config register is 1
	ptr -> write8_buff [1] = (SSHOT | PGA | MODE) >> 8;
//	ptr -> write8_buff [1] |=  (AIN1 >> 8); // choose the analog input 
	ptr -> write8_buff [2] = DRATE | COMP_MODE | COMP_POL | COMP_LAT | COMP_Q;
//
}

int
read_ads ( adc_t *ptr )
{
	for (int i = 0; i < N_INPUTS; i++)
	{
		ptr -> write8_buff [1] |=  (ptr -> ain[i] >> 8); // choose the analog input 
		if (write(ptr -> fd, ptr -> write8_buff, 3) != 3)
		{
			perror("Write to register 1");
			return 1;
		}

		// wait for conversion complete
		// checking bit 15
		do {
			if (read( ptr -> fd, ptr -> write8_buff, 2) != 2) 
			{
				perror("Read conversion");
				return 1;
			}
		}
		while ((ptr -> write8_buff[0] & 0x80) == 0);
		//
		//
		//
		//  // read conversion register
		//  // write register pointer first
		ptr -> read_buff[0] = 0;   // conversion register is 0
		if (write(ptr -> fd, ptr -> read_buff, 1) != 1)
		{
			perror("Write register select");
			return 1;
		}
		//  
		//  // read 2 bytes
		if (read(ptr -> fd, ptr -> read_buff, 2) != 2) 
		{
			perror("Read conversion");
			return 1;
		}
		ptr -> int_val[i] = (ptr -> read_buff[0]) << 8 | ptr -> read_buff[1];
	}

	return 0;
}

void
print_ads ( adc_t* ptr )
{
	for (int i = 0; i < N_INPUTS; i++ )
	{
		if (ptr -> int_val [i] < 0)
		{
			ptr -> int_val [i] = 0;
		}
		ptr -> float_val [i]  = ptr -> int_val[i] * VPS; // convert to voltage
		printf ("AIN: %i, Values: HEX 0x%02x DEC %d reading %4.3f volts.\n", i,
				ptr -> int_val[i], ptr -> int_val[i], ptr -> float_val[i] );
	}
		printf ("\n");
}
