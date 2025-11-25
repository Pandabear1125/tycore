//this is code to set up the systick timer

#ifndef TIME_H
#define TIME_H 

#include "../imxrt_regmap.h"
#include "../utils/memory.h"
#include "../boot/nvic.h"

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus extern "C"


static volatile uint32_t systick_millis = 0;  // milliseconds counter


//Configure systick
ITCM void configureSystick(void);


//delay a given abount of microseconds
ITCM void delay(int milliseconds);




#ifdef __cplusplus
}
#endif

#endif // TIME_H