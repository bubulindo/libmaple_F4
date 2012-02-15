#include "rng.h"

static rng_dev rng = {
    .regs         = RNG_BASE,
    .handler     = NULL,
};

rng_dev *RNG = &rng;


void rng_init() {

rcc_clk_enable(RCC_RNG);
//bb_peri_set_bit(&RCC_BASE->AHB2ENR, 6, 1);
}

void rng_enable(){

RNG->regs->CR |= 0x4; //If I read this right, there is no bitbanding in this region. 
//uhh la la
};

void rng_disable() {


}

void stm32_srand() {
}

uint32 stm32_rand() {
return rng_get_number();
}


uint32 rng_get_number(){
//check for errors
uint8 errors = ((RNG->regs->SR >> 5) & 0x3);
if (errors != 0) 
	return 1;
else {
	if ( (RNG->regs->SR & 0x1) > 0 )//   bb_peri_get_bit(&RNG->regs->SR, RNG_SR_DRDY_BIT) == 1)
		return (RNG->regs->DR);
	else
		return 0;
	}
};




void __irq_HASH_RNG_IRQHandler(void) {

//check if this was HASH or RNG irq

}
