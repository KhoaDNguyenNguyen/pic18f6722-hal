#ifndef HARDWARE_H
#define HARDWARE_H

#ifdef TARGET_SIMULATION
#include "hardware_sim.h"
#else
#include "hardware_board.h"
#endif

#endif
