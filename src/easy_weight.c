#include "easy_weight.h"
#include "hx711.h"

static int32_t weight_offset = 0;
static float weight_scale = 280.0f;

void Easy_Weight_Init(void) {
    HX711_Init();
}

void Easy_Weight_Tare(void) {
    weight_offset = HX711_ReadAverage(10);
}

void Easy_Weight_SetFactor(float factor) {
    weight_scale = factor;
}

int32_t Easy_Weight_GetGrams(void) {
    int32_t raw = HX711_ReadAverage(5);
    if (raw == 0) {
        return 0;
    }
    int32_t grams = (int32_t)((raw - weight_offset) / weight_scale);
    return (grams < 0) ? 0 : grams;
}
