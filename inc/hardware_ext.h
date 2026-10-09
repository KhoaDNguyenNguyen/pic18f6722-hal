#ifndef SENSOR_PINS_H
#define SENSOR_PINS_H

#include "hardware.h"
#include <xc.h>

#define HCSR04_TRIG_LAT  LATEbits.LATE7
#define HCSR04_ECHO_PIN  PORTEbits.RE6
#define TRIS_HCSR04_TRIG TRISEbits.TRISE7
#define TRIS_HCSR04_ECHO TRISEbits.TRISE6

#define DHT11_LAT        LATGbits.LATG3
#define DHT11_PIN        PORTGbits.RG3
#define TRIS_DHT11       TRISGbits.TRISG3

#define HX711_SCK_LAT    LATDbits.LATD1
#define HX711_DT_PIN     PORTDbits.RD0
#define TRIS_HX711_SCK   TRISDbits.TRISD1
#define TRIS_HX711_DT    TRISDbits.TRISD0

#endif
