/*
** FSM - Finite State Machine for 
** Solar Tracker Control 
**
** */

#include "control.h"
#include "prototypes.h"

// START  STATE
int
start_state ( ctrl_t* ptr )
{
	printf ("start\n");
	ptr -> event = START_END;
	return 0;
} // end of start state

// HOME STATE
int
home_state ( ctrl_t* ptr )
{
	printf ("home\n");
	ptr -> event = HOME_END;
	return 0;
}

// AUTO STATE
int 
auto_state ( ctrl_t* ptr )
{
	if ( read_ldr (ptr) > 0)
	{
		exit (EXIT_FAILURE );
	}

	if ( get_angles ( ptr ) > 0)
	{
		exit (EXIT_FAILURE );
	}
//
	printf ("auto\n");
	ptr -> event = AUTO_END;
	
	return 0;
}

// MANUAL STATE
int
manual_state ( ctrl_t* ptr )
{	
	printf ("manual\n");
	ptr -> event = MANUAL_END;
	
	return 0;
}

// IDLE STATE
int 
idle_state  ( ctrl_t* ptr )
{
	printf ("idle\n");
	ptr -> event = IDLE_END;
	return 0;
}
// END STATES

int
get_angles (ctrl_t* ptr )
{
	int result;	
	spa_data spa;

	rtc_t rtc;
	rtc_t* ptr_rtc = &rtc;

	if (open_i2c_rtc ( ptr_rtc) > 0 )
	{
		printf("Failed opening ds3231 (RTC) device!\n");
		return 1;
	}
//	
	if (connect_rtc (ptr_rtc  ) > 0 )
	{
		printf("Failed to connect to ds3231 (RTC) device on address!\n");
		return 1;
	}

	if ( read_rtc (ptr_rtc  ) > 0 )
	{
		printf("Failed to read from  ds3231 (RTC) device on address!\n");
		return 1;
	}
	print_rtc (ptr_rtc );
//	// close rtc driver
	close (ptr_rtc -> fd);

#ifndef RTC 
	ptr -> t = time(NULL);
	ptr -> tm = *(localtime(&(ptr -> t)));

	spa.year		= (ptr -> tm).tm_year + YEAR_OFFSET;
	spa.month		= (ptr -> tm).tm_mon + MONTH_OFFSET;
	spa.day			= (ptr -> tm).tm_mday;
	spa.hour		= (ptr -> tm).tm_hour;
	spa.minute		= (ptr -> tm).tm_min;
	spa.second		= (ptr -> tm).tm_sec;
#endif

#ifdef RTC
	spa.year		= BCD2DEC(ptr_rtc -> buf[6]) + 2000;
	spa.month      	= BCD2DEC(ptr_rtc -> buf[5]);
	spa.day        	= BCD2DEC(ptr_rtc -> buf[4]);
	spa.hour        = BCD2DEC(ptr_rtc -> buf[2]);
	spa.minute      = BCD2DEC(ptr_rtc -> buf[1]);
	spa.second      = BCD2DEC(ptr_rtc -> buf[0]);
#endif
//
	spa.timezone      = TIMEZONE;
	spa.delta_ut1     = 0;
	spa.delta_t       = 67;
	spa.longitude     = LONGITUD;
	spa.latitude      = LATITUD;
	spa.elevation     = ELEVATION;
	spa.pressure      = PRESSURE;
	spa.temperature   = 11;
	spa.slope         = 30;
	spa.azm_rotation  = -10;
	spa.atmos_refract = 0.5667;
	spa.function      = SPA_ALL;
	
	result = spa_calculate (&spa);
	print_spa (&spa, result );
	ptr -> az_angle = spa.azimuth;
	ptr -> elev_angle = 90.0 - spa.zenith;
	printf ("azimuth angle: %f\n", ptr -> az_angle );
	printf ("elevation angle: %f\n", ptr -> elev_angle);

	return 0;
}

void
print_spa (spa_data* spa, int result )
{
	float min, sec;
	char* months[13] = {"NULL", "Jan", "Feb", "Mar","Apr","May","Jun", "Jul", "Aug", "Sep", "Oct","Nov", "Dec"};


	if (result == 0)
	{
		printf ("********** El Alto neighborhood pointing ***************\n");	
		printf ("Date:          %02d-%s-%d\n", spa -> day, months[spa -> month], spa -> year );
		printf ("Current Time:  %dh %dm %ds\n", spa-> hour, spa -> minute, (int)spa->second);
	    min = 60.0*(spa->sunrise - (int)(spa->sunrise));
        sec = 60.0*(min - (int)min);
        printf("Sunrise:       %02d:%02d:%02d Local Time\n", (int)(spa->sunrise), (int)min, (int)sec);
        min = 60.0*(spa->sunset - (int)(spa->sunset));
        sec = 60.0*(min - (int)min);
        printf("Sunset:        %02d:%02d:%02d Local Time\n", (int)(spa->sunset), (int)min, (int)sec);

		printf ("Elevation avg: %.6f\n", spa->elevation);
		printf ("Latitud:       %.6f\n", spa->latitude );
		printf ("Longitud:      %.6f\n", spa->longitude );
		printf ("Elevation:     %.6f degrees \n", 90.0 - spa->zenith );
		printf("Azimuth:       %.6f degrees\n",spa->azimuth);
		printf ("*************************************************\n");	
	} 
	else
	{
		printf("SPA Error Code: %d\n", result);
	}
}

int
read_ldr ( ctrl_t* ptr  )
{
	adc_t adc = {.fd = -1, .ain[0] = AIN0, .ain[1] = AIN1, .ain[2] = AIN2, .ain[3] = AIN3,
				.int_val[0] = 0, .int_val[1]= 0, .int_val[2] = 0, .int_val[3]=0 };

	adc_t* ptr_adc = &adc;
	//int16_t val;

	if ( open_i2c_ads ( ptr_adc) > 0)
	{
		printf("Error: Couldn't open device! %d\n", ptr_adc-> fd);
		exit(EXIT_FAILURE);
	}
//	
	if ( connect_ads ( ptr_adc ) > 0 )
	{
		printf("Error: Couldn't find ads1115 (ADC) device on address!\n");
		exit(EXIT_FAILURE);
	}
////	
	config_ads ( ptr_adc );
//	
//	// Read analog inputs
	if ( read_ads (ptr_adc ) > 0) 
	{
		printf("Error: Error reading ads1115 (ADC) device!\n");
		exit (EXIT_FAILURE);
	}

	print_ads ( ptr_adc );
//	val = ptr_adc -> int_val[0];
//	if ( val  < 0 )
//	{
//		val  = 0;
//	}
	//printf ( "ain 0x%02x DEC %d \n", ptr -> tl, ptr -> tl );
//	printf ( "ain 0x%02x DEC %d \n",val ,val );
//	ptr -> ain = AIN1;
//	ptr -> tr = read_ads (ptr_adc ); // input 1 top-right
//	ptr -> ain = AIN2;
//	ptr -> bl = read_ads (ptr_adc ); // input 2 bottom-left
//	ptr -> ain = AIN3;
//	ptr -> br = read_ads (ptr_adc ); // input 3 bottom-right
//	printf ("tl: %d tr: %d bl: %d br: %d\n", ptr->tl, ptr -> tr, ptr ->bl, ptr -> br );
////
	close(ptr_adc -> fd );
	return 0;
}

