#include "time.h"
#include "../boot/nvic.h"
#include "../imxrt_regmap.h"

// Systick interrupt handler
ITCM void systick_isr(void) {
    ++systick_millis;

    //clear 
}

ITCM void configureSystick(void) {

    //use the external 24MHZ so we dont have to worry about the clock speed
    //hardware divides this down to 100K
    SCS_SYST_CSR->clksource = 0;

    //enable the systick exception
    SCS_SYST_CSR->tickint = 1;

    //add the IRQ to the IVT
    nvic_add_core_isr(15, systick_isr);

    //set the reload value to 99 for a 1ms clock
    SCS_SYST_RVR->reload = 100;

    //enable
    SCS_SYST_CSR->enable = 1;
}