#ifndef __PROTOTYPES_H__
#define __PROTOTYPES_H__
#include "../SPA/spa.h"
/*
** Function: start_state
** Purpose:  It is executed when control is in
** 			 start State. This porcedures configures
** 			 When it finishes succesfully update the event value 
** 			 and pass to the next state, home.
** Input:    Pointer to Control struct - control_t
** Output:   integer: 0 - succes. 1 - error
** Author:   Aldo Nunez
*/
int start_state ( ctrl_t* );

/*
** Function: home_state
** Purpose:  It is executed when control is carrying out
** 			 the procedure to find out Home.
** 			 When it finishes succesfully update the event value
** 			 and pass to the next state, manual.
** Input:    Pointer to Control struct - control_t
** Output:   integer: 0 - finish config. 1 - not finished
** Author:   Aldo Nunez
*/
int home_state ( ctrl_t* );

/*
** Function: auto_state
** Purpose:  It is execute when control is in automatic
** 			 mode,
** 			 When it finishes update the event value
** 			 and pass to the next state,
** Input:    Pointer to Control struct - control_t
** Output:   integer: 0 -manual mode. 1 - end automatic mode
** Author:   Aldo Nunez
*/
int auto_state ( ctrl_t* );

/*
** Function: manual_state
** Purpose:  It is execute when control is in manual
** 			 mode - controlled by Buttons.
** 			 When it finishes update the event value
** 			 and pass to the next state,
** Input:    Pointer to Control struct - control_t
** Output:   integer: 0 -manual mode. 1 - end manual mode
** Author:   Aldo Núñ
*/
int manual_state ( ctrl_t* );

/*
** Function: idle_state
** Purpose:  It is execute when control is in idle
** 			 state - controlled by Buttons.
** 			 When it finishes update the event value
** 			 and pass to the next state,
** Input:    Pointer to Control struct - control_t
** Output:   integer: 0 -manual mode. 1 - end idle state
** Author:   Aldo Núñez
*/
int idle_state ( ctrl_t* );


/*
** Function: print
** Purpose:  Print the state of the system
** Input:    Pointer to Control struct - control_t
** Output:   None
** Author:   Aldo Núñez
*/
void print_spa (spa_data*, int);

int get_angles ( ctrl_t* );
int read_ldr ( ctrl_t* );


#endif
