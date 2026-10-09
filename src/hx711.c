#include "hx711.h"
#include "sensor_pins.h"
#include "config.h"

void HX711_Init(void) {
    TRIS_HX711_DT = 1;
    TRIS_HX711_SCK = 0;
    HX711_SCK_LAT = 0;
}

int32_t HX711_Read(void) {
    int32_t count = 0;
    uint32_t timeout = 100000;
    
    while (HX711_DT_PIN) {
        if (--timeout == 0) {
            return 0;
        }
    }
    
    for (uint8_t i = 0; i < 24; i++) {
        HX711_SCK_LAT = 1;
        count = count << 1;
        HX711_SCK_LAT = 0;
        if (HX711_DT_PIN) {
            count++;
        }
    }
    
    HX711_SCK_LAT = 1;
    count ^= 0x800000;
    HX711_SCK_LAT = 0;
    
    return count;
}

int32_t HX711_ReadAverage(uint8_t times) {
    int32_t sum = 0;
    uint8_t valid_reads = 0;
    
    for (uint8_t i = 0; i < times; i++) {
        int32_t val = HX711_Read();
        if (val != 0) {
            sum += val;
            valid_reads++;
        }
    }
    
    if (valid_reads == 0) {
        return 0;
    }
    return sum / valid_reads;
}
