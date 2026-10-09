#include "easy_dht.h"
#include "dht11.h"

static uint8_t dht_temp = 0;
static uint8_t dht_humi = 0;

void Easy_DHT_Init(void) {
    DHT11_Init();
}

void Easy_DHT_Update(void) {
    uint8_t t = 0, h = 0;
    if (DHT11_Read(&t, &h)) {
        dht_temp = t;
        dht_humi = h;
    }
}

uint8_t Easy_DHT_GetTemp(void) {
    return dht_temp;
}

uint8_t Easy_DHT_GetHumi(void) {
    return dht_humi;
}
