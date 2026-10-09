#include "dht11.h"
#include "sensor_pins.h"
#include "config.h"

void DHT11_Init(void) {
    TRIS_DHT11 = 1;
}

static uint8_t DHT11_ReadByte(void) {
    uint8_t data = 0;
    uint16_t timeout;
    
    for (uint8_t i = 0; i < 8; i++) {
        timeout = 10000;
        while (!DHT11_PIN) {
            if (--timeout == 0) return 0;
        }
        
        __delay_us(35);
        
        if (DHT11_PIN) {
            data = (data << 1) | 1;
            timeout = 10000;
            while (DHT11_PIN) {
                if (--timeout == 0) return 0;
            }
        } else {
            data = (data << 1);
        }
    }
    return data;
}

bool DHT11_Read(uint8_t* temp, uint8_t* humi) {
    uint8_t buf[5];
    uint16_t timeout;
    uint8_t gie = INTCONbits.GIE;
    
    INTCONbits.GIE = 0;

    TRIS_DHT11 = 0;
    DHT11_LAT = 0;
    __delay_ms(20);
    DHT11_LAT = 1;
    TRIS_DHT11 = 1;
    __delay_us(40);

    timeout = 10000;
    while (DHT11_PIN) if (--timeout == 0) { INTCONbits.GIE = gie; return false; }
    timeout = 10000;
    while (!DHT11_PIN) if (--timeout == 0) { INTCONbits.GIE = gie; return false; }
    timeout = 10000;
    while (DHT11_PIN) if (--timeout == 0) { INTCONbits.GIE = gie; return false; }

    for (uint8_t i = 0; i < 5; i++) {
        buf[i] = DHT11_ReadByte();
    }

    INTCONbits.GIE = gie;

    if ((uint8_t)(buf[0] + buf[1] + buf[2] + buf[3]) == buf[4]) {
        *humi = buf[0];
        *temp = buf[2];
        return true;
    }
    
    return false;
}
