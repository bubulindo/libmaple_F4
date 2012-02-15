#include "rcc.h"
#include "bitband.h"

#ifdef __cplusplus
extern "C" {
#endif



typedef struct rng_reg_map {
	__io uint32 CR;		///< Control Register //
	__io uint32 SR;		///< status register//
	__io uint32 DR;		///< Data Register//
} rng_reg_map;

#define RNG_BASE        ((struct rng_reg_map*)0x50060800)

/// rtc device type //
typedef struct rng_dev {
	rng_reg_map *regs;			///< Register map //
	voidFuncPtr handler;     ///< User IRQ handlers //
} rng_dev;

extern rng_dev *RNG;


#define RNG_CR_IE_BIT		3
#define RNG_CR_RNGEN_BIT	2


#define RNG_SR_SEIS_BIT		6
#define RNG_SR_CEIS_BIT		5
#define RNG_SR_SECS_BIT		2
#define RNG_SR_CECS_BIT		1
#define RNG_SR_DRDY_BIT		0


void rng_init();
void rng_enable();
uint32 rng_get_number();


#ifdef __cplusplus
}
#endif


