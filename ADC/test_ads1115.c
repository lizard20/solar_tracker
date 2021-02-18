// ads1115b.c read pot on ANC1
// output value in volts exit program.
// uses one-shot mode
// pull up resistors in module caused problems
// used level translator - operated ADS1115 at 5V
// by Lewis Loflin lewis@bvu.net
// www.bristolwatch.com
// http://www.bristolwatch.com/rpi/ads1115.html

#include "ads1115.h"     
// Note PCF8591 defaults to 0x48!

/*
The resolution of the ADC in single ended 
mode we have 15 bit rather than 16 bit resolution, 
the 16th bit being the sign of the differential reading.
*/

int
main()
{
	// init struct
	adc_t adc = {.fd = -1, .ain[0] = AIN0, .ain[1] = AIN1, .ain[2] = AIN2, .ain[3] = AIN3,
				.int_val[0] = 0, .int_val[1]= 0, .int_val[2] = 0, .int_val[3]=0 };
	adc_t* ptr = &adc;
	int ret;

	ret = open_i2c_ads (ptr);
	if (ret > 0 )
	{
		perror ("Fail openign ads1115 device");
		exit(EXIT_FAILURE);
	}

	ret = connect_ads ( ptr );
  // connect to ads1115 as i2c slave
	if (ret > 0 )
	{
		printf("Error: Couldn't find device on address!\n");
		exit(EXIT_FAILURE);
	}
	// Config
	config_ads( ptr );

	// read
	while (1)
	{
		ret = read_ads ( ptr );
		if (ret > 0)
		{
			exit(EXIT_FAILURE);
		}
	
		print_ads ( ptr );
		sleep(2);
	}

	close(ptr -> fd);

  return 0;
}

