//this is code to set up the systick timer

#ifndef TIME_H
#define TIME_H

#include <stdint.h>

#include "../boot/nvic.h"
#include "../imxrt_regmap.h"
#include "../utils/memory.h"

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus extern "C"

#define CORE_FREQ 151200000 //post PLL value, there should be a better way to get the actual core clock wihtout doing the math beforehand

extern volatile uint32_t systick_millis;

//Configure systick
ITCM void configureSystick(void);

//delay a given abount of microseconds
ITCM void delay(uint32_t milliseconds);

#ifdef __cplusplus
}
#endif

#endif	// TIME_H
