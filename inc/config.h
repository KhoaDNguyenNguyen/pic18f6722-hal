#ifndef CONFIG_H
#define CONFIG_H

#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config OSC = HS
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRT = OFF
#pragma config BOREN = SBORDIS
#pragma config WDT = OFF
#pragma config LVP = OFF

#endif
