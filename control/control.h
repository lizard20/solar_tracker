#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// ADC API
#include "../ADC/ads1115.h"

// SPA
#include "../SPA/spa.h"
#include "../SPA/local_data.h"

// RTC
#include "../RTC/ds3231.h"

#define RTC

// Delay in seconds
#define SECS 1

// system states
enum STATES { START = 1, HOME, AUTO, MANUAL, IDLE};

// system events
enum EVENTS { START_END = 1, HOME_END, AUTO_END, MANUAL_END, IDLE_END };

// data types for states, events and control
typedef enum STATES state_t;
typedef enum EVENTS event_t;
typedef struct Control ctrl_t;


// Control struct for data, states, events and commands
struct Control
{
	// States and events
	state_t state;
	event_t event;
	// open device variable
	int fd;
	// tiem varibles
	time_t t; 
	struct tm tm;
	
	// elevation angle
	float elev_angle;	
	float az_angle;
	
	// ADC inputs
	int16_t tl; // top left ldr
	int16_t tr; // top right ldr
	int16_t bl; // bottom left ldr
	int16_t br; // bottom right ldr

	char buf[BUFFER_SIZE];
};

#endif


