///****************************************************************************
// * The MIT License
// *
// * Copyright (c) 2011 Visible Assets Inc.
// *
// * Permission is hereby granted, free of charge, to any person
// * obtaining a copy of this software and associated documentation
// * files (the "Software"), to deal in the Software without
// * restriction, including without limitation the rights to use, copy,
// * modify, merge, publish, distribute, sublicense, and/or sell copies
// * of the Software, and to permit persons to whom the Software is
// * furnished to do so, subject to the following conditions:
// *//
// * The above copyright notice and this permission notice shall be
// * included in all copies or substantial portions of the Software.
// *
 //* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 //* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 //* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 //* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 //* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 //* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 //* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 //* SOFTWARE.
 //****************************************************************************//

///
// * @file   rtc.h
// * @author Rod Gilchrist <rod@visibleassets.com>
// * @brief  Real Time Clock interface.
// *
 //

#ifndef _RTC_F4_H
#define _RTC_F4_H

#include <libmaple.h>
#include <rcc.h>
#include <nvic.h>
#include <bitband.h>
#include <pwr.h>
#include <exti.h>

#define EXTI_RTC_ALARM_BIT		17						// the extra exti interrupts (16,17,18,19) should be defined in exti.h (BUG)

#define RCC_BDCR_RTCSEL_LSI   (0x2 << 8)


#ifdef __cplusplus
extern "C" {
#endif

typedef struct rtc_reg_map {
	__io uint32 TR;		///< Time Shadow Register //
	__io uint32 DR;		///< Date Shadow Register //
	__io uint32 CR;		///< Control Register //
	__io uint32 ISR;		///< Initialization and status register//
	__io uint32 PRER;		///< Prescaler Register//
	__io uint32 WUTR;		///< WakeUp Timer register//
	__io uint32 CALIBR;		///< Calibration Register //
	__io uint32 ALRMAR;		///< Alarm A Register //
	__io uint32 ALRMBR;		///< Alarm B Register //
	__io uint32 SSR;		///< SubSecond Register //
	__io uint32 SHIFTR;		///< Shift Control Register //
	__io uint32 WPR;		///< Write Protection Register //
	__io uint32 TSTR;		///< TimeStamp Time Register //
	__io uint32 TSDR;		///< TimeStamp Date Register //
	__io uint32 TSSSR;		///< TimeStamp Sub Second Register //
	__io uint32 CALR;		///< Calibration Register //
	__io uint32 TAFCR;		///< Tamper and Alternate Func Config Register //
	__io uint32 ALRMASSR;		///< Alarm A Sub Second Register//
	__io uint32 ALRMBSSR;		///< Alarm B Sub Second Register//
	__io uint32 BKPR[20];		///< BackUp Registers//
} rtc_reg_map;
		
/// RTC register map base pointer //
#define RTC_BASE        ((struct rtc_reg_map*)0x40002800)

/// rtc device type //
typedef struct rtc_dev {
	rtc_reg_map *regs;			///< Register map //
	voidFuncPtr handlers[];     ///< User IRQ handlers //
} rtc_dev;

extern rtc_dev *RTC;


//
// * Register bit definitions
 //
 
// Time register  (TR) // 

#define RTC_TR_PM_BIT		22

		
	
// Control register //
	
#define RTC_CRH_OWIE_BIT	2
#define RTC_CRH_ALRIE_BIT	1
#define RTC_CRH_SECIE_BIT	0

#define RTC_CR_COE_BIT		23
#define RTC_CR_OSEL_OUT_DIS	(0x0 << 21)
#define RTC_CR_OSEL_ALR_A	(0x1 << 21)
#define RTC_CR_OSEL_ALR_B	(0x2 << 21)
#define RTC_CR_OSEL_WAKE	(0x3 << 21)
#define RTC_CR_POL_BIT		20
#define RTC_CR_COSEL_BIT	19
#define RTC_CR_BKP_BIT		18
#define RTC_CR_SUB1H_BIT	17
#define RTC_CR_ADD1H_BIT	16
#define RTC_CR_TSIE_BIT		15
#define RTC_CR_WUTIE_BIT	14
#define RTC_CR_ALRBIE_BIT	13
#define RTC_CR_ALRAIE_BIT	12
#define RTC_CR_TSE_BIT		11
#define RTC_CR_WUTE_BIT		10
#define RTC_CR_ALRBE_BIT	9
#define RTC_CR_ALRAE_BIT	8
#define RTC_CR_DCE_BIT		7
#define RTC_CR_FMT_BIT		6
#define RTC_CR_BYPSHAD_BIT	5
#define RTC_CR_REFCKON_BIT	4
#define RTC_CR_TSEDGE_BIT	3
#define RTC_CR_WUCKSEL_RTC16 0
#define RTC_CR_WUCKSEL_RTC8	1
#define RTC_CR_WUCKSEL_RTC4	2
#define RTC_CR_WUCKSEL_RTC2	3



// Initialization and status register //

#define RTC_ISR_RECALPF_BIT	16
#define RTC_ISR_TAMP2F_BIT	14
#define RTC_ISR_TAMP1F_BIT	13
#define RTC_ISR_TSOVF_BIT	12
#define RTC_ISR_TSF_BIT		11
#define RTC_ISR_WUTF_BIT	10
#define RTC_ISR_ALRBF_BIT	9
#define RTC_ISR_ALRAF_BIT	8
#define RTC_ISR_INIT_BIT	7
#define RTC_ISR_INITF_BIT	6
#define RTC_ISR_RSF_BIT		5
#define RTC_ISR_INITS_BIT	4
#define RTC_ISR_SHPF_BIT	3
#define RTC_ISR_WUTWF_BIT	2
#define RTC_ISR_ALRBWF_BIT	1
#define RTC_ISR_ALRAWF_BIT	0


// Prescaler Register RTC_PRER//

#define PREDIV_A_BIT	16
#define PREDIV_S_BIT	0

//  Calibration Register RTC_CALIBR//

#define RTC_CALIBR_DCS_BIT	7

// Alarm A Register //

#define RTC_ALRMAR_MSK4_BIT		31
#define RTC_ALRMAR_WDSEL_BIT	30
#define RTC_ALRMAR_MSK3_BIT		23
#define RTC_ALRMAR_AMPM_BIT		22
#define RTC_ALRMAR_MSK2_BIT		15
#define RTC_ALRMAR_MSK1_BIT		7

// Alarm B Register //

#define RTC_ALRMBR_MSK4_BIT		31
#define RTC_ALRMBR_WDSEL_BIT	30
#define RTC_ALRMBR_MSK3_BIT		23
#define RTC_ALRMBR_AMPM_BIT		22
#define RTC_ALRMBR_MSK2_BIT		15
#define RTC_ALRMBR_MSK1_BIT		7

// Shift Control Register //
#define RTC_SHIFTR_ADD1S_BIT	31

// Time Stamp Time Register //

#define RTC_TSTR_AMPM_BIT		22

// RTC Calibration Register RTC_CALR//

#define RTC_CALR_CALP_BIT		15
#define RTC_CALR_CALW8_BIT		14
#define RTC_CALR_CALW16_BIT		13

// Tamper and Alternate function configuration Register //
#define RTC_TAFCR_ALROUTTYP_BIT 18
#define RTC_TSINSEL_BIT			17
#define RTC_TIAMP1NSEL_BIT		16
#define RTC_TAMPPUDIS_BIT		15
#define RTC_TAMPPRCH1			(0x0 << 13)
#define RTC_TAMPPRCH2			(0x1 << 13)
#define RTC_TAMPPRCH4			(0x2 << 13)
#define RTC_TAMPPRCH8			(0x3 << 13)
#define RTC_TAMPFLT_EDGE		(0x0 << 11)
#define RTC_TAMPFLT_2SAMP		(0x1 << 11)
#define RTC_TAMPFLT_4SAMP		(0x2 << 11)
#define RTC_TAMPFLT_8SAMP		(0x3 << 11)
#define RTC_TAMPTS_BIT			7
#define RTC_TAMPT2TRG_BIT		4
#define RTC_TAMP2E_BIT			3
#define RTC_TAMPIE_BIT			2
#define RTC_TAMP1TRG_BIT		1
#define RTC_TAMP1E_BIT			0




///
 /// @brief RTC interrupt number.
// *
 //

//
typedef enum rtc_interrupt_id {
	RTC_SECONDS_INTERRUPT			= 0,	///< Counter seconds interrupt //
	RTC_ALARM_GLOBAL_INTERRUPT		= 1,	///< RTC alarm global interrupt (i.e. __irq_rtc()) //
	RTC_OVERFLOW_INTERRUPT			= 2,	///< Counter overflow interrupt //
	RTC_ALARM_SPECIFIC_INTERRUPT	= 3		///< RTC alarm specific interrupt (i.e. __irq_rtcalarm(), wake up from halt/sleep) //
	
} rtc_interrupt_id;

//
// * @brief RTC clock source.
// *
 //
typedef enum rtc_clk_src {
	RTCSEL_DEFAULT	= 0,
	RTCSEL_NONE		= 0x10,
	RTCSEL_LSE		= 0x11,
	RTCSEL_LSI		= 0x12,
	RTCSEL_HSE		= 0x13,
} rtc_clk_src;


	
#ifdef __cplusplus
}
#endif

#endif // _RTC_H //