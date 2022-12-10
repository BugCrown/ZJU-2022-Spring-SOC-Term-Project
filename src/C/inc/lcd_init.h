/*
 * lcd_init.h
 *
 *  Created on: 2021��7��14��
 *      Author: ����
 */

#ifndef INC_LCD_INIT_H_
#define INC_LCD_INIT_H_

#include "assert.h"
#include "xil_printf.h"
#include "xil_types.h"

#define LCD_BASE_ADDR 0x44A00000
#define REG_VIDEOMEM_ADDR (LCD_BASE_ADDR + 0)
#define REG_VIDEOMEM_LENGTH (LCD_BASE_ADDR + 4)
#define REG_LCDINIT_ADDR (LCD_BASE_ADDR + 8)
#define REG_LCDINIT_LENGTH (LCD_BASE_ADDR + 12)
#define REG_LCD_CTRL (LCD_BASE_ADDR + 16)
#define REG_LCD_STATUS (LCD_BASE_ADDR + 20)

//自定义初始化代码和显示数据的存储地址
//必须处在DDR的地址范围0x80000000~0x87ffffff内
#define VIDEO_BASE_ADDR 0x82000000
#define VIDEO_LENGTH (854*480)
#define LCD_INIT_BASE_ADDR 0x86000000
#define LCD_INIT_LENGTH 145

u32 lcd_init();

#endif /* INC_LCD_INIT_H_ */
