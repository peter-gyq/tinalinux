/*
 * Copyright (C) 2013 Allwinnertech, kevin.z.m <kevin@allwinnertech.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Adjustable factor-based clock implementation
 */
#ifndef __MACH_SUNXI_CLK_SUN8IW9_H
#define __MACH_SUNXI_CLK_SUN8IW9_H

#include <linux/clk-provider.h>
#include <linux/clkdev.h>
#include <linux/io.h>
#include <mach/hardware.h>
#include "clk-factors.h"

/* register list */
#define PLL_CPU0            0x0000
#define PLL_CPU1            0x0004
#define PLL_AUDIO           0x0008
#define PLL_VIDEO           0x0010
#define PLL_VE              0x0018
#define PLL_DDR0            0x0020
#define PLL_PERIPH0         0x0028
#define PLL_PERIPH1         0x002C
//#define PLL_24M           0x0034 //no need in software,change to do it in hardware.
#define PLL_GPU             0x0038
#define MIPI_PLL            0x0040
#define PLL_HSIC            0x0044
#define PLL_DE              0x0048
#define PLL_DDR1            0x004c


#define CPU_CFG             0x0050
#define AHB1_CFG            0x0054
#define APB2_CFG            0x0058
#define BUS_GATE0           0x0060
#define BUS_GATE1           0x0064
#define BUS_GATE2           0x0068
#define BUS_GATE3           0x006c
#define BUS_GATE4           0x0070
#define THS_CFG             0x0074
#define CCI400_CFG          0x0078
#define NAND_CFG            0x0080
#define SD0_CFG             0x0088
#define SD1_CFG             0x008c
#define SD2_CFG             0x0090
#define SD3_CFG             0x0094
#define SS_CFG              0x009c
#define SPI0_CFG            0x00A0
#define SPI1_CFG            0x00A4
#define USB_CFG             0x00CC
#define PLL_CPU_CFG         0x00EC
#define DRAM_CFG            0x00F4
#define PLL_DDR1_CFG        0x00F8
#define MBUS_RST            0x00FC
#define DRAM_GATE           0x0100
#define DE_CFG              0x0104
#define LCD_CH0             0x0118
#define CSI0_CFG            0x0134
#define CSI1_CFG            0x0138
#define VE_CFG              0x013C
#define ADDA_CFG            0x0140
#define AVS_CFG             0x0144
#define MBUS_CFG            0x015C
#define MIPI_DSI            0x0168
#define MIPI_CSI            0x016C
#define GPU_CFG             0x01A0
#define ATS_CFG             0x01B0
#define PLL_LOCK            0x0200
#define CPU_LOCK            0x0204
#define PLL_CPU1PAT         0x027c
#define PLL_CPU0PAT         0x0280
#define PLL_AUDIOPAT        0x0284
#define PLL_VIDEOPAT        0x0288
#define PLL_VEPAT           0x028c
#define PLL_DDR0PAT  		0X0290
#define PLL_GPUPAT          0x029c
#define PLL_MIPIPAT         0x02A0
#define PLL_HSICPAT         0x02A4
#define PLL_DEPAT           0x02A8
#define	PLL_DDR1PAT0		0X02AC
#define	PLL_DDR1PAT1		0X02B0

#define BUS_RST0           0x02C0
#define BUS_RST1           0x02C4
#define BUS_RST2           0x02C8
#define BUS_RST3           0x02D0
#define BUS_RST4           0x02D8

#define SUNXI_CLK_MAX_REG   0X0304
#define LOSC_OUT_GATE       0x01F00060

#define CPUS_CFG            0x00
#define CPUS_APB0           0x0C
#define CPUS_APB0_GATE      0x28
#define KEYPAD_CFG          0x34
#define CPUS_CLK_MAX_REG    0xB0
#define CPUS_APB0_RST       0xB0

#define F_N8X7_M0X4(nv,mv) FACTOR_ALL(nv,8,7,0,0,0,mv,0,4,0,0,0,0,0,0,0,0,0)
#define F_N8X5_K4X2(nv,kv) FACTOR_ALL(nv,8,5,kv,4,2,0,0,0,0,0,0,0,0,0,0,0,0)
#define F_N8X6(nv) FACTOR_ALL(nv,8,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define F_N8X5_K4X2_M0X2(nv,kv,mv) FACTOR_ALL(nv,8,5,kv,4,2,mv,0,2,0,0,0,0,0,0,0,0,0)
#define F_N8X5_K4X2_M0X2_P16x2(nv,kv,mv,pv) \
               FACTOR_ALL(nv,8,5, \
                          kv,4,2, \
                          mv,0,2, \
                          pv,16,2, \
                          0,0,0,0,0,0)
#define F_N8X7_M0X2(nv , mv) FACTOR_ALL(nv,8,7,0,0,0,mv,0,2,0,0,0,0,0,0,0,0,0)
#define F_N8X7_M0X2_P16x2(nv,mv, pv)   FACTOR_ALL(nv,8,7,0,0,0,mv,0,2,pv,16,2,0,0,0,0,0,0)

#define F_N8X5_K4X2_1N16X5_M0X2(nv,kv,pv,mv) FACTOR_ALL(nv,8,5,kv,4,2,mv,0,2,pv,16,5,0,0,0,0,0,0)



#define PLLCPU(n,m,p,freq)  {F_N8X7_M0X2_P16x2(n,m, p),  freq}
#define PLLVIDEO(n,m,freq)  {F_N8X7_M0X4( n, m),  freq}
#define PLLVE(n,m,freq)  {F_N8X7_M0X4( n, m),  freq}
#define PLLDDR0(n,k,m,freq)  {F_N8X5_K4X2_M0X2( n, k, m),  freq}
#define PLLPERIPH(n,k,freq)  {F_N8X5_K4X2( n, k),  freq}
#define PLLGPU(n,m,freq)  {F_N8X7_M0X4( n, m),  freq}
#define PLLHSIC(n,m,freq)  {F_N8X7_M0X4( n, m),  freq}
#define PLLDE(n,m,freq) {F_N8X7_M0X4( n, m),  freq}
#define PLLDDR1(n,m,freq) {F_N8X7_M0X2(n , m),  freq}


#endif
