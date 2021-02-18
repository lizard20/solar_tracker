/** Simple I2C example to read the time from a DS3231 module
* Written by Derek Molloy for the book "Exploring Raspberry Pi" */

#include "ds3231.h"

int 
main()
{
	rtc_t rtc = {.fd = -1};
	rtc_t* ptr = &rtc;

	int ret;

	printf("Starting the DS3231 test application\n");
	ret = open_i2c_rtc ( ptr );
	if (ret < 0)
	{
		perror ("Error openign I2C device\n");
		exit(1);
	}

	ret = connect_rtc ( ptr );
	if (ret < 0)
	{
		exit (1);
	}

	ret = read_rtc ( ptr  );
	if (ret < 0)
	{
		exit (1);
	}

	print_rtc( ptr );

	close(ptr -> fd);
	return 0;
}
