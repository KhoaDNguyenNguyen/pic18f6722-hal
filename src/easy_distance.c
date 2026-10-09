#include "easy_distance.h"
#include "hcsr04.h"

void Easy_Distance_Init(void) {
    HCSR04_Init();
}

uint16_t Easy_Distance_Get(void) {
    return HCSR04_Read();
}
