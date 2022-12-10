#include <GBK24.h>
#include "xil_assert.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "lcd_hz_gui.h"

void LCDShowHZ(u16 x,u16 y,u8 *font,u8 size,u8 mode,u32 color)
{
    unsigned char qh,ql;
    unsigned long foffset;
    u8 temp,t,t1;
	u16 x0=x;
	u16 y0=y;
	u8 dzk[72];   
	u8 csize=(size/8+((size%8)?1:0))*(size);	 
	if(size!=24)return;

	qh=*font;
	ql=*(++font);
    if(qh<0x81||ql<0x40||ql==0xff||qh==0xff)
	{   		    
	    return;
	}          
	if(ql<0x7f)ql-=0x40;
	else ql-=0x41;
	qh-=0x81;   
//    foffset=((unsigned long)190*qh+ql)*csize;
	foffset=(unsigned long)190*qh+ql;
	for(t=0;t<csize;t++)
	{   												   
		temp=GBK24[foffset][t];
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_DrawPoint(x,y,color);
			else if(mode==0)LCD_DrawPoint(x,y,0xFFFFFFFF);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}
	}  
}
void ShowAllChar(u16 x, u16 y, u8 *font, u8 size, u16 color)
{
    u16 x_loc, y_loc;
    x_loc = x * size;
    y_loc = y * size;
	if(*font >= 0x81)
    	LCDShowHZ(x_loc, y_loc, font, size, 0, color);
	else if(font >= ' ' && font <= '~')
		LCD_ShowChar(x_loc, y_loc, font, size, 0, color);
}

