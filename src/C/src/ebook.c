#include "xil_assert.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "ebook.h"
#include "text_example.h"
#include "lcd_hz_gui.h"


u8 ebook[4][19][70];
u8 ebookpage = 0;
//Initial Ebook and porcess
void EbookInitial()
{
    int i = 0;
    int j = 0;
    int k =0;
    int address = 0;
    while (1)
    {
        if(text_example_international[address] >= 0x81)
        {
            ebook[i][j][k] = text_example_international[address];
            k++;
            ebook[i][j][k] = text_example_international[address + 1];
            address = address + 2;
        }
        else if (text_example_international[address] >= ' ' && text_example_international[address] <= '~')
        {
            ebook[i][j][k] = 0;
            k++;
            ebook[i][j][k] = text_example_international[address];
            address = address + 1;
        }

        if(k == 69 && j == 18)
        {
        	j = 0;
            k = 0;
            i++;
        }
        else if(k == 69 && j < 18)
        {
        	j++;
        	k = 0;
        }
        else if (k < 69)
        {
        	k++;
        }
        if(i == 4)
        	break;
    }

}
//Show e-book 
//turn:0 last page, 1 next page
void DisplayEbook()
{
    u8 ascch;
    u8 gbkch[2];
    int i = 0;
    int j = 0;
    int k = 0;
    int h;
    LCD_Clear(0xFFFFFFFF);
    while (1)
    {
        if(ebook[ebookpage][j][k] >= 0x81)
        {
            gbkch[0] = ebook[ebookpage][j][k];
            k++;
            gbkch[1] = ebook[ebookpage][j][k];
            ShowAllChar(k/2, j, gbkch, 24, 0x00000000);
        }
        else if(ebook[ebookpage][j][k] == 0)
        {
            k++;
            ascch = ebook[ebookpage][j][k];
            ShowAllChar(k/2, j, ascch, 24, 0x00000000);
        }

        if(k == 69 && j < 18)
		{
			j++;
			k = 0;
//	        for(h = 0; h < 1000000; h++);
		}
        else if(k == 69 && j == 18)
        {
        	break;
        }
        else
        {
        	k++;
        }
//		for(h = 0; h < 10000; h++);
    }
}
