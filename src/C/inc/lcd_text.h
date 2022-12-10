#ifndef __TEXT_H
#define __TEXT_H

#include "xil_assert.h"
#include "xil_printf.h"
#include "xil_types.h"


extern unsigned char lcd_str[32][71][19];
extern unsigned char uart_str[200];
extern unsigned char copy_str[71];
extern u16 x_pos, y_pos;
extern u16 num;
extern u8 page;
extern u8 pageflag;
//Get string from serial port
void Scanf_Uart(char *str);
//Get char from serial port
void GetChar_Uart(char ch);
//Display char in a specific array
void ShowChar(u16 x, u16 y, u8 ch, u8 size, u16 color);
//Display a cursor between two char
void ShowCursor(u16 x, u16 y, u8 size, u32 color);
//Decode Command
u8 DecodeVimCommand(char ch);
//lcd_str initial
void StrInitial();
//Process input string
u8 StrProcess(char *str);
//Main text process
u8 VimLiteTXT(u8 flag);
#endif
