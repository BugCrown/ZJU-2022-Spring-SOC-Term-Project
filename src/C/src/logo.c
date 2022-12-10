#include "logo.h"
#include "lcd_gui.h"
#include "xil_assert.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "lcd_hz_gui.h"
#include "logo_color.h"
void DrawLogo()
{
	char s[10] = "CK807";
	char ID[100] = "Presented by 3190100368 & 3190103299";
	char cpr[100] = "Copy right 2022-2022";
	char Name0[100] = "×£èåÌÎ";
	char Name1[100] = "ĞìÓÀÌÎ";
    int i, j;
	for(i = 0; i < 10; i++)
		ShowChar(i, 0, s[i], 54, 0x00000000);
	for(i = 0; i < 100; i++)
		ShowChar(i, 12, ID[i], 32, 0x00000000);
	for(i = 0; i < 100; i++)
		ShowChar(i+50, 18, cpr[i], 24, 0x00000000);
	for(i = 0; i < 100; i=i+2)
		ShowAllChar(i/2+10, 18, (Name0+i), 24, 0x00000000);
	for(i = 0; i < 100; i=i+2)
		ShowAllChar(i/2+19, 18, (Name1+i), 24, 0x00000000);
    for (i = 0; i < 700; i++)
    {
        for (j = 0; j < 250; j++)
        {
//            LCD_DrawPoint(i, j+200, logo_screen_color_Z[i][j]);
//            LCD_DrawPoint(i+200, j+200, logo_screen_color_I[i][j]);
            LCD_DrawPoint(i+77, j+100, logo_screen_color_ZIM[i][j]);
        }
    }
}
