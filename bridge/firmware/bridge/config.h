/*
 *This file defines configuration options
 *for the firmware which allow for it to be
 *adapted for different versions of the PCB
 *
 */
#ifndef CONFIG_H
#define CONFIG_H


/*Begin configuration*/
#define BAUD_RATE 9600

#define TURF_PIN 2
#define REVERSE_PIN 3
#define FORWARD_PIN 4
#define START_PIN 5
#define SWITCH_DRIVE_ENABLE_PIN 6

#define MAN_AUTO_SELECT_PIN 15
#define MAN_AUTO_SELECT_PIN_ANALOG 1

#define MAN_START_SWITCH_PIN 14
#define MAN_ACCEL_PIN_ANALOG 2
#define MAN_AUX_PIN_ANALOG 3
#define MAN_FORWARD_SWITCH_PIN 0
#define MAN_REVERSE_SWITCH_PIN 1
//#define MAN_TURF_SWITCH_PIN

//#define FORWARD_REVERSE_NORMALLY_CLOSED /*Define only if forward/reverse selct switch is NC*/
/*End configuration*/



/*
 * Do NOT edit file beyond this point,
 * the rest of the file defines useful
 * values based on the configuration
 * provided above
 *
 */

#ifdef FORWARD_REVERSE_NORMALLY_CLOSED
#define FORWARD_REVERSE_OFF_STATE false
#else
#define FORWARD_REVERSE_OFF_STATE true
#endif



#endif
