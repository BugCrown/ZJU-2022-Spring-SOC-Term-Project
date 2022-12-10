#include "xil_assert.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "lcd_init.h"
#include "font.h"
#include "lcd_gui.h"

#define IMAGE_X 854
#define IMAGE_Y 480


//Draw a point at a specific position
//Position: x, y
//Color: color
void LCD_DrawPoint(u16 x,u16 y,u32 color)
{
	int i;
	x = x % IMAGE_X;
	y = y % IMAGE_Y;
	u32 *p = (u32*)VIDEO_BASE_ADDR;
    *(p + y * 854 + x) = color;
}

//Show a Char at a specific position
//The Character's Leftmost point and Top point: x, y
//Color: color
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode,u32 color)
{  							  
  u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);
 	num=num-' ';//The font is start with ' '
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	//Use 1206 font
		else if(size==16)temp=asc2_1608[num][t];	//Use 1608 font
		else if(size==24)temp=asc2_2412[num][t];	//Use 2412 font
		else if(size==32)temp=asc2_3216[num][t];	//Use 3216 font
		else if(size==54)temp=asc2_5427[num][t];	//Use 5427 font
		else return;								//Undefined font
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawPoint(x,y,color);
			else if(mode==0)LCD_DrawPoint(x,y,0xFFFFFFFF);
			temp<<=1;
			y++;
			if(y>=IMAGE_Y)return;		//Over the limited area
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=IMAGE_X)return;	//Over the limited area
				break;
			}
		}  	 
	}  	    	   	 	  
}   

//Abandoned Function
//void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size,u32 color)
//{
//	u8 t,temp;
//	u8 enshow=0;
//	for(t=0;t<len;t++)
//	{
//		temp=(num/LCD_Pow(10,len-t-1))%10;
//		if(enshow==0&&t<(len-1))
//		{
//			if(temp==0)
//			{
//				LCD_ShowChar(x+(size/2)*t,y,' ',size,0, color);
//				continue;
//			}else enshow=1;
//
//		}
//	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0, color);
//	}
//}

//Show a String at a specific position
//The String's Leftmost point and Top point: x, y
//The limited area:width, height
//Color: color
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *str,u32 color)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*str<='~')&&(*str>=' '))
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;
        LCD_ShowChar(x,y,*str,size,0,color);
        x+=size/2;
        str++;
    }  
}

//Clear the screen
void LCD_Clear(u32 color)
{
	u32 *p = (u32*)VIDEO_BASE_ADDR;
    int i;
    for(i=0; i<VIDEO_LENGTH; i++)
    {
        *(p++) = color;
    }
}

//Fill an area
//Top left point:(sx, sy)
//Bottom right point:(ex, ey)
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color)
{          
	u16 i,j;
	u16 xlen=0;
	u16 temp;
    xlen=ex-sx+1;	 
    for(i=sy;i<=ey;i++)
    {
        for(j=0;j<xlen;j++)
            LCD_DrawPoint(sx + j, i, color);	//Draw point
    }
}

//Draw a line
//The starting point:x1,y1
//The ending point:x2,y2
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u32 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; 
	else if(delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )
	{  
		LCD_DrawPoint(uRow,uCol,color);
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    

//Draw thick lines
void DrawBline(u16 x0,u16 y0,u16 x1,u16 y1,u8 size,u32 color)
{
	u16 t; 
	int xerr=0, yerr=0, delta_x, delta_y, distance; 
	int incx, incy, uRow, uCol;

	delta_x = x1-x0;
	delta_y = y1-y0; 
	uRow = x0; 
	uCol = y0; 
	if (delta_x > 0) incx = 1;
	else if (delta_x == 0) incx = 0;
	else {
        incx = -1;
        delta_x = -delta_x;
    }
	if (delta_y > 0) incy = 1; 
	else if (delta_y == 0) incy = 0;
	else {
        incy = -1;
        delta_y = -delta_y;
    } 
	if (delta_x > delta_y) distance = delta_x;
	else distance = delta_y; 
	for(t = 0; t <= distance+1; t++) {
		if (size == 0) LCD_DrawPoint(uRow,uCol,color);
		if (size == 1) {
			LCD_DrawPoint(uRow,uCol,color);
			LCD_DrawPoint(uRow+1,uCol,color);
			LCD_DrawPoint(uRow,uCol+1,color);  
			LCD_DrawPoint(uRow+1,uCol+1,color);  
		}
		if(size == 2) {
			LCD_DrawPoint(uRow,uCol,color);  
			LCD_DrawPoint(uRow+1,uCol,color);  
			LCD_DrawPoint(uRow,uCol+1,color);
			LCD_DrawPoint(uRow+1,uCol+1,color);  
			LCD_DrawPoint(uRow-1,uCol+1,color);  
			LCD_DrawPoint(uRow+1,uCol-1,color); 
			LCD_DrawPoint(uRow-1,uCol-1,color);   
			LCD_DrawPoint(uRow-1,uCol,color);  
			LCD_DrawPoint(uRow,uCol-1,color);   
		}
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance) { 
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance) { 
			yerr -= distance; 
			uCol += incy; 
		} 
	} 				 
}

//Draw a circle
//Center Point:(x,y)
//r :radius
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,u32 color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b,color);             //5
 		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-a,y0+b,color);             //1       
 		LCD_DrawPoint(x0-b,y0+a,color);             
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
  	    LCD_DrawPoint(x0-b,y0-a,color);             //7     	         
		a++;
		//Use Bresenham method
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 


