/* Solar tracker control program.
**
** Auth: Aldo Nunez Tovar
** Date: Feb-2021
** */

#include "control.h"
#include "prototypes.h"

int
main ()
{
	/* init control struct data: 
	states, events and commands */
	ctrl_t  ctrl  = {.state = START, .event = 0, .fd = 0, 
					.elev_angle = 0.0, .tl = 0, .tr = 0, .bl = 0,
					.br = 0};

	// pointer to control struct
	ctrl_t* ptr_ctrl = &ctrl;

	system ( "clear" );
	
	int ret;
	// Start FSM
	while ( true )
	{	
		switch ( ptr_ctrl -> state )
		{
			//  start
			case START:
				ret = start_state ( ptr_ctrl );
				if ( ret )
				{
					perror ( "start Failed!");
					exit(1);
				}

				if (ptr_ctrl -> event == START_END )
				{
					ptr_ctrl -> state = HOME;
				}
				break;
			case HOME:
				ret = home_state ( ptr_ctrl );		
				if ( ret )
				{
					perror ( "home Failed!");
					exit(1);
				}
				if (ptr_ctrl -> event == HOME_END )
				{
					ptr_ctrl -> state = AUTO;
				}
				break;
			case AUTO:
				ret = auto_state ( ptr_ctrl );		
				if ( ret )
				{
					perror ( "auto Failed!");
					exit(1);
				}
				if (ptr_ctrl -> event == AUTO_END )
				{
					ptr_ctrl -> state = MANUAL;
				}
				break;
			case MANUAL:
				ret = manual_state ( ptr_ctrl );		
				if ( ret )
				{
					perror ( "manual Failed!");
					exit(1);
				}
				if (ptr_ctrl -> event ==  MANUAL_END )
				{
					ptr_ctrl -> state = IDLE;
				}
				break;
			case IDLE:	
			ret = idle_state ( ptr_ctrl );		
				if ( ret )
				{
					perror ( "manual Failed!");
					exit(1);
				}
				if (ptr_ctrl -> event ==  IDLE_END )
				{
					ptr_ctrl -> state = HOME;
				}
				break;
			default:
				break;
		} // end switch-case
		sleep ( SECS );
	} // end of while 	
	return 0;

}
