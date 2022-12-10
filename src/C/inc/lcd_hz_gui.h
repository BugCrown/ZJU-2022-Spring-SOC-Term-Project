#ifndef LCD_HZ_GUI_H
#define LCD_HZ_GUI_H

#include "xil_assert.h"
#include "xil_printf.h"
#include "xil_types.h"

void LCDShowHZ(u16 x,u16 y,u8 *font,u8 size,u8 mode,u32 color);//Show Chinese character
void ShowHZChar(u16 x, u16 y, u8 *font, u8 size, u16 color);

#endif