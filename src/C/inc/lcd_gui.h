#ifndef __LCD_H
#define __LCD_H
#include "xil_assert.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "lcd_init.h"

void LCD_DrawPoint(u16 x,u16 y,u32 color);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode,u32 color);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size,u32 color);
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *str,u32 color);
void LCD_Clear(u32 color);
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u32 color);
void DrawBline(u16 x0,u16 y0,u16 x1,u16 y1,u8 size,u32 color);
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,u32 color);



#endif
