/*******************************************************************
 *  Copyright C 2010 by Amlogic, Inc. All Rights Reserved.
 *  File name: TVAFE_ADC.h
 *  Description: IO function, structure,
 enum, used in TVIN AFE sub-module processing
 *******************************************************************/
#ifndef _TVAFE_ADC_H
#define _TVAFE_ADC_H

#include <linux/amlogic/tvin/tvin.h>


#define PERIPHS_PIN_MUX_0			0x202c
#define P_PERIPHS_PIN_MUX_0			CBUS_REG_ADDR(PERIPHS_PIN_MUX_0)
#define PERIPHS_PIN_MUX_1			0x202d
#define P_PERIPHS_PIN_MUX_1			CBUS_REG_ADDR(PERIPHS_PIN_MUX_1)
#define PERIPHS_PIN_MUX_2			0x202e
#define P_PERIPHS_PIN_MUX_2			CBUS_REG_ADDR(PERIPHS_PIN_MUX_2)
#define PERIPHS_PIN_MUX_3			0x202f
#define P_PERIPHS_PIN_MUX_3			CBUS_REG_ADDR(PERIPHS_PIN_MUX_3)
#define PERIPHS_PIN_MUX_4			0x2030
#define P_PERIPHS_PIN_MUX_4			CBUS_REG_ADDR(PERIPHS_PIN_MUX_4)
#define PERIPHS_PIN_MUX_5			0x2031
#define P_PERIPHS_PIN_MUX_5			CBUS_REG_ADDR(PERIPHS_PIN_MUX_5)
#define PERIPHS_PIN_MUX_6			0x2032
#define P_PERIPHS_PIN_MUX_6			CBUS_REG_ADDR(PERIPHS_PIN_MUX_6)
#define PERIPHS_PIN_MUX_7			0x2033
#define P_PERIPHS_PIN_MUX_7			CBUS_REG_ADDR(PERIPHS_PIN_MUX_7)
#define PERIPHS_PIN_MUX_8			0x2034
#define P_PERIPHS_PIN_MUX_8			CBUS_REG_ADDR(PERIPHS_PIN_MUX_8)
#define PERIPHS_PIN_MUX_9			0x2035
#define P_PERIPHS_PIN_MUX_9			CBUS_REG_ADDR(PERIPHS_PIN_MUX_9)
#define PERIPHS_PIN_MUX_10			0x2036
#define P_PERIPHS_PIN_MUX_10		CBUS_REG_ADDR(PERIPHS_PIN_MUX_10)

#if 0
/* #define TVAFE_DEBUG_PIN_ENABLE */
#define TVAFE_ADC_CONFIGURE_INIT     1
#define TVAFE_ADC_CONFIGURE_NORMAL   (1|(1<<POWERDOWNZ_BIT)|(1<<RSTDIGZ_BIT))
/* 7 */
#define TVAFE_ADC_CONFIGURE_RESET_ON (1|(1<<POWERDOWNZ_BIT))
/********************************************************** */
/* *** enum definitions ********************************************* */
/*************************************************************** */
/* auto clock detection state machine */
enum tvafe_vga_auto_clk_state_e {
	VGA_CLK_IDLE,
	VGA_CLK_INIT,
	VGA_CLK_ROUGH_ADJ,
	VGA_CLK_FINE_ADJ,
	VGA_CLK_EXCEPTION,
	VGA_CLK_END,
};

/* auto phase state machine */
enum tvafe_vga_auto_phase_state_e {
	VGA_PHASE_IDLE,
	VGA_PHASE_INIT,
	/* auto phase init */
	VGA_PHASE_SEARCH_WIN,
	VGA_PHASE_ADJ,
	/* write all the phase value, get the best value by the sum value */
	VGA_PHASE_EXCEPTION,
	VGA_PHASE_END,
	VGA_BORDER_DET_INIT,
	VGA_BORDER_DET,
	VGA_VDIN_BORDER_DET,
};
struct tvafe_vga_border_s {
	unsigned int hstart;
	unsigned int hend;
	unsigned int vstart;
	unsigned int vend;
};
struct tvafe_vga_auto_s {
	enum tvafe_vga_auto_clk_state_e   clk_state;
	enum tvafe_vga_auto_phase_state_e phase_state;
	struct tvafe_vga_border_s         border;
	unsigned char                     ap_win_index;
	unsigned char                     ap_winmax_index;
	unsigned char                     ap_pha_index;
	unsigned char                     ap_phamax_index;
	unsigned char                     vs_cnt;
	unsigned char                     adj_cnt;
	signed char                     adj_dir;
	unsigned int                      ap_max_diff;
};
struct tvafe_adc_s {
	/* status of command */
	enum tvafe_cmd_status_e    cmd_status;
	unsigned char                       auto_enable;
	/* adc auto adjust enable */
	struct tvafe_vga_auto_s        vga_auto;

	struct tvafe_vga_parm_s       vga_parm;

	struct tvin_format_s               hw_info;
	unsigned char                       hs_sog_sw_cnt;
	unsigned char                       adc_reset_cnt;
	unsigned int                          skip_frame_cnt;
	enum tvin_sig_fmt_e             current_fmt;
};
#endif
/******************************************************** */
/* ******** GLOBAL FUNCTION CLAIM ******** */
/***************************************************** */
#if 0
extern void tvafe_adc_set_deparam(struct tvin_parm_s *parm,
						struct tvafe_adc_s *adc);
extern void tvafe_adc_set_param(struct tvin_parm_s *parm,
						struct tvafe_adc_s *adc);
/*
extern void tvafe_adc_get_param(struct tvin_parm_s *parm,
						struct tvafe_adc_s *adc);
*/
extern void tvafe_vga_vs_cnt(struct tvafe_adc_s *adc);
extern void tvafe_vga_auto_adjust_handler(struct tvin_parm_s *parm,
						struct tvafe_adc_s *adc);
extern int  tvafe_vga_auto_adjust_enable(struct tvafe_adc_s *adc);
extern void tvafe_vga_auto_adjust_disable(struct tvafe_adc_s *adc);
extern bool tvafe_adc_no_sig(void);
extern bool tvafe_adc_fmt_chg(struct tvin_parm_s *parm,
					struct tvafe_adc_s *adc);
extern enum tvin_sig_fmt_e tvafe_adc_search_mode(
			struct tvin_parm_s *parm, struct tvafe_adc_s *adc);
extern bool tvafe_adc_get_pll_status(void);
extern bool tvafe_adc_check_frame_skip(struct tvafe_adc_s *adc);

extern void tvafe_adc_configure(enum tvin_sig_fmt_e fmt);
extern void tvafe_adc_digital_reset(void);
extern void tvafe_adc_comphase_pr(void);
extern void tvin_vdin_bar_detect(enum tvin_sig_fmt_e fmt,
					struct tvafe_adc_s *adc);
#endif
extern void tvin_vdin_bbar_init(enum tvin_sig_fmt_e fmt);
extern void get_adc_version(const char **ver, const char **last_ver);
#endif /* _TVAFE_ADC_H */

