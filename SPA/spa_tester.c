

/////////////////////////////////////////////
//          SPA TESTER for SPA.C           //
//                                         //
//      Solar Position Algorithm (SPA)     //
//                   for                   //
//        Solar Radiation Application      //
//                                         //
//             August 12, 2004             //
//                                         //
//   Filename: SPA_TESTER.C                //
//                                         //
//   Afshin Michael Andreas                //
//   afshin_andreas@nrel.gov (303)384-6383 //
//                                         //
//   Measurement & Instrumentation Team    //
//   Solar Radiation Research Laboratory   //
//   National Renewable Energy Laboratory  //
//   1617 Cole Blvd, Golden, CO 80401      //
/////////////////////////////////////////////

/////////////////////////////////////////////
// This sample program shows how to use    //
//    the SPA.C code.                      //
/////////////////////////////////////////////

#include <stdio.h>
#include <time.h>
#include "spa.h"  //include the SPA header file
#include "local_data.h"  //include the SPA header file

int 
main ()
{
    spa_data spa;  //declare the SPA structure
    int result;
    float min, sec;

	// time and date
	time_t t = time (NULL);
	struct tm tm = *localtime(&t);
	char* months[13] = {"NULL", "Jan", "Feb", "Mar","Apr","May","Jun", "Jul", "Aug", "Sep", "Oct","Nov", "Dec"};
	
    //enter required input values into SPA structure

    spa.year          = tm.tm_year + YEAR_OFFSET;
    spa.month         = tm.tm_mon + MONTH_OFFSET;
    spa.day           = tm.tm_mday;
    spa.hour          = tm.tm_hour;
    spa.minute        = tm.tm_min;
    spa.second        = tm.tm_sec;
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

    //call the SPA calculate function and pass the SPA structure

    result = spa_calculate(&spa);

    if (result == 0)  //check for SPA errors
    {
        //display the results inside the SPA structure

        printf("Julian Day:    %.6f\n",spa.jd);
        printf("L:             %.6e degrees\n",spa.l);
        printf("B:             %.6e degrees\n",spa.b);
        printf("R:             %.6f AU\n",spa.r);
        printf("H:             %.6f degrees\n",spa.h);
        printf("Delta Psi:     %.6e degrees\n",spa.del_psi);
        printf("Delta Epsilon: %.6e degrees\n",spa.del_epsilon);
        printf("Epsilon:       %.6f degrees\n",spa.epsilon);
        printf("Zenith:        %.6f degrees\n",spa.zenith);
        printf("Azimuth:       %.6f degrees\n",spa.azimuth);
        printf("Incidence:     %.6f degrees\n",spa.incidence);

        min = 60.0*(spa.sunrise - (int)(spa.sunrise));
        sec = 60.0*(min - (int)min);
        printf("Sunrise:       %02d:%02d:%02d Local Time\n", (int)(spa.sunrise), (int)min, (int)sec);

        min = 60.0*(spa.sunset - (int)(spa.sunset));
        sec = 60.0*(min - (int)min);
        printf("Sunset:        %02d:%02d:%02d Local Time\n", (int)(spa.sunset), (int)min, (int)sec);
		printf ("********** El Alto neighborhood pointing ***************\n");	
		printf ("Date:          %02d-%s-%d\n", spa.day, months[spa.month], spa.year );
		printf ("Current Time:  %dh %dm %ds\n", spa.hour, spa.minute, (int)spa.second);
		printf ("Elevation avg: %.6f\n", spa.elevation);
		printf ("Latitud:       %.6f\n", spa.latitude );
		printf ("Longitud:      %.6f\n", spa.longitude );
		printf ("Elevation:     %.6f degrees \n", 90.0 - spa.zenith );
        printf("Azimuth:       %.6f degrees\n",spa.azimuth);
		printf ("*************************************************\n");	

    } else printf("SPA Error Code: %d\n", result);

    return 0;
}

/////////////////////////////////////////////
// The output of this program should be:
//
//Julian Day:    2452930.312847
//L:             2.401826e+01 degrees
//B:             -1.011219e-04 degrees
//R:             0.996542 AU
//H:             11.105902 degrees
//Delta Psi:     -3.998404e-03 degrees
//Delta Epsilon: 1.666568e-03 degrees
//Epsilon:       23.440465 degrees
//Zenith:        50.111622 degrees
//Azimuth:       194.340241 degrees
//Incidence:     25.187000 degrees
//Sunrise:       06:12:43 Local Time
//Sunset:        17:20:19 Local Time
//
/////////////////////////////////////////////

