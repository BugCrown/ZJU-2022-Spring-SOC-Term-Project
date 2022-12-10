/*
 * Name        : ck807_helloworld.c
 * Author      :
 * Version     :
 * Copyright   : Your copyright notice
 * Description : Simple function in C, Ansi-style
 */
#include"xil_printf.h"
#include"xil_assert.h"
#include"xil_types.h"
#include"lcd_text.h"
#include"lcd_gui.h"
#include "lcd_hz_gui.h"
#include"logo.h"
#include"ebook.h"


#define C_RED 0xF800F800
#define C_YELLOW 0xFFE0FFE0
#define C_BLUE 0x001F001F
#define C_MAGENATA 0xF81FF81F
#define C_GREEN 0x07E007E0
#define C_CYAN 0xB4DFB4DF
#define C_BLACK 0x00000000
#define C_BURLY 0xFEF5FEF5
#define C_WHITE 0xFFFFFFFF

#define IMAGE_X 854
#define IMAGE_Y 480

#define CPU_CLK 100000000
#define RX_FIFO 0
#define TX_FIFO 1
#define STAT_REG 2
#define CTRL_REG 3

#define EBOOK 0
#define EDITOR 1

unsigned int *UART_BASE_ADDR=(unsigned int *)0x40600000;
unsigned int *GPIO_BASE_ADDR=(unsigned int *)0x40000000;
int flag;

int main() {
	/* TODO */
	//UART Initial
	char s[200];
	char ch;

	unsigned int div = CPU_CLK / 2 / 9600;
	UART_BASE_ADDR[3]=div;

	u32 i,j,k;
	u32 init_done;
	u32 x_loc;
	u32 y_loc;
	u32 *p = (u32*)VIDEO_BASE_ADDR;
	u32 *lcd_ctrl = (u32*)REG_LCD_CTRL;
	u16 x_pos_pos, y_pos_pos;
	u8 mode;


	init_done = lcd_init();	//LCD Initial

	unsigned char old_lcd_str[32][71][19];
	unsigned char demo_str[1349] = "#include <stdio.h>\nint main(void)\n{\n printf(\"Hello World\");\n return 0;\n}\n";
	//Text Initial
	flag = 0;
	// pageflag = 0;
	page = 0;
	ebookpage = 0;


	for (i = 0; i < 32; i ++)
		for (j = 0; j < 71; j++)
			for (k = 0; k < 19; k++)
			{
				lcd_str[i][j][k] = ' ';
				old_lcd_str[i][j][k] = ' ';
			}

	//demo
	i = 0;
	j = 0;
	k = 0;
	while(demo_str[i] != 0)
	{
		if(demo_str[i] == '\n' || i == 70)
		{
			j = 0;
			k++;
		}
		else
		{
			lcd_str[0][j][k] = demo_str[i];
			j++;
		}
		i++;
	}
	for (j = 0; j < 71; j++)
		for (k = 0; k < 19; k++)
		{
			old_lcd_str[0][j][k] = lcd_str[0][j][k];
		}

	//Display the Logo 'ZIM'
	switch(init_done){
		case 0: ;
		case 1:
			LCD_Clear(C_WHITE);
			*lcd_ctrl = *lcd_ctrl | 6;
			break;
		default: *lcd_ctrl = *lcd_ctrl | 64; return -1;

		}
	*lcd_ctrl = *lcd_ctrl & 0;
	DrawLogo();
	*lcd_ctrl = *lcd_ctrl | 6;
	while(1)
	{
		while(1)
		{
			if(GPIO_BASE_ADDR[0] == 2)
			{
				*lcd_ctrl = *lcd_ctrl & 0;
				LCD_Clear(C_WHITE);
				//Display the demo
			    for(j = 9; j < 19; j++)
			    {
			        for(i = 35; i < 71; i++)
			        {
			            ShowChar(i, j, lcd_str[0][i][j], 24, 0x00000000);
			            ShowChar(i, 18-j, lcd_str[0][i][18-j], 24, 0x00000000);
			            ShowChar(70-i, j, lcd_str[0][70-i][j], 24, 0x00000000);
			            ShowChar(70-i, 18-j, lcd_str[0][70-i][18-j], 24, 0x00000000);
			        }
			    }
				*lcd_ctrl = *lcd_ctrl | 4;
				mode = EDITOR;
				break;
			}
			else if (GPIO_BASE_ADDR[0] == 16)
			{
				mode = EBOOK;
				break;
			}
		}

//		*lcd_ctrl = *lcd_ctrl & 0;
		//Editor Mode
		if(mode == EDITOR)
		{
			while(1)
			{
				*lcd_ctrl = *lcd_ctrl & 0;
				for(int i=0;i<200;i++)
					uart_str[i]=0;

				while(UART_BASE_ADDR[STAT_REG] == 0)
				{
					int j;
					for(j=0;j<1000;j++);
				}

				Scanf_Uart(uart_str);

				flag = VimLiteTXT(flag);
				for(j=0;j<100000;j++);
		//		LCD_Clear(C_WHITE);

				for(j = 9; j < 19; j++)
				{
					for(i = 35; i < 71; i++)
					{
						if(old_lcd_str[page][i][j] != lcd_str[page][i][j])
						{
							ShowChar(i, j, lcd_str[page][i][j], 24, C_BLACK);
		// 					old_lcd_str[page][i][j] = lcd_str[page][i][j];
						}
						if(old_lcd_str[page][i][18-j] != lcd_str[page][i][18-j])
						{
							ShowChar(i, 18-j, lcd_str[page][i][18-j], 24, C_BLACK);
		// 					old_lcd_str[page][i][18-j] = lcd_str[page][i][18-j];
						}
						if(old_lcd_str[page][70-i][j] != lcd_str[page][70-i][j])
						{
							ShowChar(70-i, j, lcd_str[page][70-i][j], 24, C_BLACK);
		// 					old_lcd_str[page][70-i][j] = lcd_str[page][70-i][j];
						}
						if(old_lcd_str[page][70-i][18-j] != lcd_str[page][70-i][18-j])
						{
							ShowChar(70-i, 18-j, lcd_str[page][70-i][18-j], 24, C_BLACK);
		// 					old_lcd_str[page][70-i][35-j] = lcd_str[page][70-i][18-j];
						}
					}
				}
				for (i = 0; i < 32; i ++)
					for (j = 0; j < 71; j++)
						for (k = 0; k < 19; k++)
						{
							old_lcd_str[i][j][k] = lcd_str[i][j][k];
						}
				ShowCursor(x_pos_pos, y_pos_pos, 24, C_WHITE);
				ShowCursor(x_pos, y_pos, 24, C_BLACK);
				x_pos_pos = x_pos;
				y_pos_pos = y_pos;
				xil_printf("The Cursor Position is %d %d\n",x_pos,y_pos);
				*lcd_ctrl = *lcd_ctrl | 4;

			}
		}
		//Ebook mode
		else if (mode == EBOOK)
		{
			ebookpage = 0;
			EbookInitial();
			*lcd_ctrl = *lcd_ctrl & 0;
			DisplayEbook();
			*lcd_ctrl = *lcd_ctrl | 4;
			*lcd_ctrl = *lcd_ctrl & 0;
			while(1)
			{
				if(GPIO_BASE_ADDR[0] == 4)
				{
					*lcd_ctrl = *lcd_ctrl & 0;
					ebookpage = (ebookpage == 0) ? 0 : (ebookpage - 1);
					DisplayEbook();
					*lcd_ctrl = *lcd_ctrl | 4;
					*lcd_ctrl = *lcd_ctrl & 0; //very important! It is used to prevent auto screen off
				}
				else if(GPIO_BASE_ADDR[0] == 8)
				{
					*lcd_ctrl = *lcd_ctrl & 0;
					ebookpage = (ebookpage == 3) ? 3 : (ebookpage + 1);
					DisplayEbook();
					*lcd_ctrl = *lcd_ctrl | 4;
					*lcd_ctrl = *lcd_ctrl & 0;
				}
				xil_printf("The page is %d\n", ebookpage);
				for(i = 0; i < 100000; i++);
			}
		}
	}

	return 0;
}

