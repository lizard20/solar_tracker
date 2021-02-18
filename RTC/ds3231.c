#include "ds3231.h"

int
open_i2c_rtc ( rtc_t* ptr )
{
	if (( ptr -> fd = open("/dev/i2c-1", O_RDWR)) < 0) 
	{
		printf("Error: Couldn't open device! %d\n", ptr -> fd);
		return 1;
	}
	return 0;
}

int
connect_rtc ( rtc_t* ptr )
{
	if ( ioctl ( ptr -> fd, I2C_SLAVE, RTC_ADDRESS ) < 0)
	{
		perror("Failed to connect to the sensor\n");
		return 1;
	}
	return 0;
}


int 
read_rtc  ( rtc_t* ptr )
{
	char  writeBuffer[1] = {0x00};
	if(write( ptr -> fd, writeBuffer, 1)!=1)
	{
		perror("Failed to reset the read address\n");
		return 1;
   }

//   char buf[BUFFER_SIZE];
   if(read ( ptr -> fd, ptr -> buf, BUFFER_SIZE)!=BUFFER_SIZE){
	   perror("Failed to read in the buffer\n");
	   return 1;
  }
   return 0;
}

void
print_rtc ( rtc_t* ptr  )
{
	printf("The RTC time is %02d:%02d:%02d\n", BCD2DEC( ptr -> buf[2]),
			BCD2DEC(ptr -> buf[1]), BCD2DEC(ptr -> buf[0]));
	printf("month  %02d\n", BCD2DEC( ptr -> buf[5]));
	printf("day  %02d\n", BCD2DEC(ptr -> buf[4]));
	printf("year  %02d\n", 2000 +  BCD2DEC( ptr -> buf[6]));

	float temperature = ptr -> buf[0x11] + ((ptr -> buf[0x12]>>6)*0.25);
	printf("The temperature is %.2f°C\n", temperature);
}
//

