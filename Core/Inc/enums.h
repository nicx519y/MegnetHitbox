/*
 * enums.h
 *
 *  Created on: Aug 6, 2024
 *      Author: nicx5
 */

#ifndef INC_ENUMS_H_
#define INC_ENUMS_H_


enum InputMode
{
    INPUT_MODE_XINPUT 		= 0,
    INPUT_MODE_SWITCH 		= 1,
    INPUT_MODE_PS3 			= 2,
    INPUT_MODE_KEYBOARD 	= 3,
    INPUT_MODE_PS4 			= 4,
    INPUT_MODE_XBONE 		= 5,
    INPUT_MODE_MDMINI 		= 6,
    INPUT_MODE_NEOGEO 		= 7,
    INPUT_MODE_PCEMINI 		= 8,
    INPUT_MODE_EGRET 		= 9,
    INPUT_MODE_ASTRO 		= 10,
    INPUT_MODE_PSCLASSIC 	= 11,
    INPUT_MODE_XBOXORIGINAL = 12,
    INPUT_MODE_PS5 			= 13,
    INPUT_MODE_GENERIC 		= 14,
    INPUT_MODE_CONFIG 		= 255
};

enum InputModeAuthType
{
    INPUT_MODE_AUTH_TYPE_NONE 	= 0,
    INPUT_MODE_AUTH_TYPE_KEYS 	= 1,
    INPUT_MODE_AUTH_TYPE_USB 	= 2,
    INPUT_MODE_AUTH_TYPE_I2C 	= 3
};

enum SOCDMode
{
    SOCD_MODE_UP_PRIORITY 			= 0,	// U+D=U, L+R=N
    SOCD_MODE_NEUTRAL 				= 1,	// U+D=N, L+R=N
    SOCD_MODE_SECOND_INPUT_PRIORITY = 2,	// U>D=D, L>R=R (Last Input Priority, aka Last Win)
    SOCD_MODE_FIRST_INPUT_PRIORITY 	= 3, 	// U>D=U, L>R=L (First Input Priority, aka First Win)
    SOCD_MODE_BYPASS 				= 4		// U+D=UD, L+R=LR (No cleaning applied)
};

enum PS4ControllerType
{
    PS4_CONTROLLER 	= 0,
    PS4_ARCADESTICK = 7
};



#endif /* INC_ENUMS_H_ */
