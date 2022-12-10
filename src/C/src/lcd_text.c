#include "lcd_text.h"
#include "lcd_gui.h"
#define RX_FIFO 0
#define TX_FIFO 1
#define STAT_REG 2
#define CTRL_REG 3

#define IMAGE_X 854
#define IMAGE_Y 480

#define C_WHITE 0xFFFFFFFF
//Get string from serial port
void Scanf_Uart(char *str)
{
    unsigned int *UART_BASE_ADDR=(unsigned int *)0x40600000;
    int i=0,j;
	while(UART_BASE_ADDR[STAT_REG] == 1)
	{
		for(j=0;j<1000;j++);
			str[i]=UART_BASE_ADDR[RX_FIFO]&0xff;
		for(j=0;j<1000;j++);
			i++;
	}
}

////Get char from serial port
//void GetChar_Uart(char ch)
//{
//    unsigned int *UART_BASE_ADDR=(unsigned int *)0x40600000;
//    int i;
//    if(UART_BASE_ADDR[STAT_REG] == 1)
//    {
//    	for(i = 0; i< 1000; i++);
//        ch = UART_BASE_ADDR[RX_FIFO]&0xff;
//        for(i = 0; i< 1000; i++);
//    }
//}

//Display char in a specific array
void ShowChar(u16 x, u16 y, u8 ch, u8 size, u16 color)
{
    u16 x_loc, y_loc;
    x_loc = x * size / 2;
    y_loc = y * size;
    if(ch >= ' ' && ch <= '~')
    LCD_ShowChar(x_loc, y_loc, ch, size, 0, color);
}

//Display a cursor between two char
void ShowCursor(u16 x, u16 y, u8 size, u32 color)
{
    u16 x_loc, y_loc;
    x_loc = x * size / 2;
    y_loc = y * size;
    LCD_DrawLine(x_loc, y_loc, x_loc, y_loc + size, color);
//    LCD_DrawLine(x_loc - 1, y_loc, x_loc + 1, y_loc, color);
//    LCD_DrawLine(x_loc - 1, y_loc + size, x_loc + 1, y_loc + size, color);
}
unsigned char lcd_str[32][71][19];
u8 page = 0;



#define X_SIZE 71
#define Y_SIZE 19

#define CM_NUM 10
#define CM_LEFT 11
#define CM_DOWN 12
#define CM_UP 13
#define CM_RIGHT 14
#define CM_HASHTAG 15
#define CM_DOLLAR 16
#define CM_G 17
#define CM_DEL 18
#define CM_BAC 19
#define CM_CUT 20
#define CM_COPY 21
#define CM_PASTE_D 22
#define CM_PASTE_U 23
#define CM_I 24
#define CM_A 25
#define CM_O 26
// #define CM_R 27


#define CM_CLEAR 27
#define CM_PAGE 28


//Decode Command
u8 DecodeVimCommand(char ch)
{
    u8 type;
    if(ch >= '0' && ch <= '9')
        type = CM_NUM;
    else
    {
        switch (ch)
        {
            //Move
            case 'h': type = CM_LEFT;break;
            case 'j': type = CM_DOWN;break;
            case 'k': type = CM_UP;break;
            case 'l': type = CM_RIGHT;break;
            case '#': type = CM_HASHTAG;break;
            case '$': type = CM_DOLLAR;break;
            case 'G': type = CM_G;break;

            //Delete Cut Copy Paste
            case 'x': type = CM_DEL;break;
            case 'X': type = CM_BAC;break;
            case 'd': type = CM_CUT;break;
            case 'y': type = CM_COPY;break;
            case 'p': type = CM_PASTE_D;break;
            case 'P': type = CM_PASTE_U;break;

            //Switch to edit mode
            case 'i': type = CM_I;break;
            case 'a': type = CM_A;break;
            case 'o': type = CM_O;break;
            // case 'r': type = CM_R;break;

            case 'c': type = CM_CLEAR;LCD_Clear(C_WHITE);break;
            case '`': type = CM_PAGE;LCD_Clear(C_WHITE);break;

            default:  type = 0;break;
        }
    }
    return type;

}

//lcd_str initial
//void StrInitial()
//{
//    int x = X_SIZE;
//    int y = Y_SIZE;
//    int i, j;
//    for(i = 0; i < x; i++)
//        for(j = 0; j < y; y++)
//            lcd_str[i][j] = 0;
//}

//Process input string
u8 StrProcess(char *str)
{
    int i = 0;
    while( str[i] != 0 )
    {
        uart_str[i] = str[i];
        i++;
    }
    return i-1;
}

unsigned char uart_str[200];
unsigned char copy_str[71];
u16 x_pos = 0, y_pos = 0;
u16 num = 0;
u8 pageflag;
//Main text process
//flag: 0 Cammand Mode; 1 Edit Mode
u8 VimLiteTXT(u8 flag)
{
    int i = 0;
    u8 type;
    u8 state = flag;
    u8 next_state;
    num = 1;
    int numflag = 0;

    while(uart_str[i] != 0)
    {

        if(state == 0)                      //Command
        {
            type = DecodeVimCommand(uart_str[i]);
            if(type == CM_NUM)              //Number
            {
            	if (numflag == 0)
            	{
            		num = 0;
                	num = num * 10 + uart_str[i] - '0';
                	numflag = 1;
            	}
            	else
            	{
                	num = num * 10 + uart_str[i] - '0';
            	}

                next_state = 0;
            }


            else if (type == CM_LEFT)       //Move cursor left
            {
                int l;
                for(l = 0; l < num; l++)
                {
                    if(x_pos > 0)
                        x_pos--;
                    else
                        break;
                }
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else if (type == CM_DOWN)
            {
                int d;
                for(d = 0; d < num; d++)
                {
                    if(y_pos < 18)
                        y_pos++;
                    else
                        break;
                }
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else if (type == CM_UP)
            {
                int u;
                for(u = 0; u < num; u++)
                {
                    if(y_pos > 0)
                        y_pos--;
                    else
                        break;
                }
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else if (type == CM_RIGHT)
            {
                int r;
                for(r = 0; r < num; r++)
                {
                    if(x_pos < 71)
                        x_pos++;
                    else
                        break;
                }
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else if (type == CM_HASHTAG)
            {
                x_pos = 0;
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else if (type == CM_DOLLAR)
            {
                x_pos = 71;
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else if (type == CM_G)
            {
                y_pos = 18;
                num = 1;
                next_state = 0;
                numflag = 0;
            }


            else if (type == CM_DEL)//Delete Cut Copy Paste
            {
                int del;
                for(del = 0; del < num; del++)
                {
                    if(x_pos < 71)
                        lcd_str[page][x_pos][y_pos] = ' ';
                    else
                        break;
                    x_pos++;
                }
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else if (type == CM_BAC)
            {
                int bac;
                for(bac = 0; bac < num; bac++)
                {
//                    x_pos = ( x_pos == 0 ) ? 0 : x_pos-1;
                    if(x_pos > 0)
                    {
                    	x_pos--;
                        lcd_str[page][x_pos][y_pos] = ' ';
                    }

                    else
                        break;
                }
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else if (type == CM_CUT)
            {
                int dd1;
                int dd2;
                for(dd1 = 0; dd1 < 71; dd1++)
                {
                    copy_str[dd1] = lcd_str[page][dd1][y_pos];
                }
//                for(dd1 = y_pos; dd1 < 18; dd1++)
//                {
//                    for(dd2 = 0; dd2 < 71; dd2++)
//                    lcd_str[page][dd2][dd1] = lcd_str[page][dd2][dd1+1];
//                }
                for(dd1 = 0; dd1 < 71; dd1++)
                    lcd_str[page][dd1][y_pos] = ' ';
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else if (type == CM_COPY)
            {
                int yy;
                for(yy = 0; yy < 71; yy++)
                {
                    copy_str[yy] = lcd_str[page][yy][y_pos];
                }
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else if (type == CM_PASTE_D)
            {
            	if(y_pos != 18)
            	{
					int pd1,pd2;
					for (pd1 = 18; pd1 > y_pos; pd1--)
					{
						for(pd2 = 0; pd2 < 71; pd2++)
							lcd_str[page][pd2][pd1] = lcd_str[page][pd2][pd1-1];
					}
					y_pos++;
					for(pd1 = 0; pd1 < 71; pd1++)
						lcd_str[page][pd1][y_pos] = copy_str[pd1];
            	}
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else if (type == CM_PASTE_U)
            {
                int pu1,pu2;
                if(y_pos != 0)
                {
					for (pu1 = 0; pu1 < y_pos; pu1++)
					{
						for(pu2 = 0; pu2 < 71; pu2++)
							lcd_str[page][pu2][pu1] = lcd_str[page][pu2][pu1+1];
					}

					y_pos--;
					for(pu1 = 0; pu1 < 71; pu1++)
						lcd_str[page][pu1][y_pos] = copy_str[pu1];
                }
                num = 1;
                next_state = 0;
                numflag = 0;
            }

            //Edit
            else if (type == CM_I)
            {
                num = 1;
                next_state = 1;
                numflag = 0;
            }
            else if (type == CM_A)
            {
                if (x_pos == 71)
                {
                    if(y_pos != 18)
                    {
                        x_pos = 0;
                        y_pos++;
                    }
                }
                else
                x_pos++;
                num = 1;
                next_state = 1;
                numflag = 0;
            }
            else if (type == CM_O)
            {
                if (y_pos < 18)
				{
					y_pos++;
					x_pos = 0;
				}
                num = 1;
                next_state = 1;
                numflag = 0;
            }


            else if (type == CM_CLEAR)	//Clear
            {
        		// LCD_Clear(C_WHITE);
        		int i,j;
        		for(i = 0; i < 71; i++)
        		{
        			for(j = 0; j < 19; j++)
        				lcd_str[page][i][j] = 0;
        		}
                x_pos = 0;
                y_pos = 0;
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else if (type == CM_PAGE) //page
            {
                int i, j;
            	LCD_Clear(C_WHITE);
                page = num;
                for(j = 9; j < 19; j++)
                {
                    for(i = 35; i < 71; i++)
                    {
                        ShowChar(i, j, lcd_str[page][i][j], 24, 0x00000000);
                        ShowChar(i, 18-j, lcd_str[page][i][18-j], 24, 0x00000000);
                        ShowChar(70-i, j, lcd_str[page][70-i][j], 24, 0x00000000);
                        ShowChar(70-i, 18-j, lcd_str[page][70-i][18-j], 24, 0x00000000);                        
                    }
                }
                num = 1;
                next_state = 0;
                numflag = 0;
                x_pos = 0;
                y_pos = 0;
                pageflag = 1;
            }
            else
            {
                num = 1;
                next_state = 0;
                numflag = 0;
            }
        }
        else    //Edit Mode
        {
            if(uart_str[i] >= ' ' && uart_str[i] <= '~')
            {
                if (x_pos == 71)
                {
                    if (y_pos != 18)
                    {
                        x_pos = 0;
                        y_pos++;
                        lcd_str[page][x_pos][y_pos] = uart_str[i];

                        x_pos++;
                    }
                    else
                    break;
                }
                else
                {
                    lcd_str[page][x_pos][y_pos] = uart_str[i];
                    x_pos++;
                }
                num = 1;
                next_state = 1;
                numflag = 0;
            }
            else if (uart_str[i] == 10)// '\n'
            {
                if(y_pos < 18)
                y_pos++;
                num = 1;
                next_state = 1;
                numflag = 0;
            }
            else if (uart_str[i] == 13)// '\r'
            {
                x_pos = 0;
            }
            else if (uart_str[i] == 8)// '\b'
            {
                if(x_pos == 0)
                {
                    if (y_pos > 0)
                    {
                        x_pos = 71;
                        y_pos--;
                        lcd_str[page][70][y_pos] = 0;
                    }
                }
                else
                {
                    x_pos--;
                    lcd_str[page][x_pos][y_pos] = 0;
                }
                num = 1;
                next_state = 1;
                numflag = 0;
            }
            else if (uart_str[i] == 127)// delete
            {
                if(x_pos == 71)
                {
                    if (y_pos < 18)
                    {
                        x_pos = 0;
                        y_pos++;
                        lcd_str[page][0][y_pos] = 0;
                    }
                }
                else
                {
                    x_pos++;
                    lcd_str[page][x_pos][y_pos] = 0;
                }
                num = 1;
                next_state = 1;
                numflag = 0;
            }
            else if(uart_str[i] == 27)// esc
            {
                num = 1;
                next_state = 0;
                numflag = 0;
            }
            else
            {
                num = 1;
                next_state = 1;
                numflag = 0;
            }
        }
        i++;
        state = next_state;
    }
    return state;
}
