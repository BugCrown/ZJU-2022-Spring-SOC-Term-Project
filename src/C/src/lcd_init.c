#include "lcd_init.h"

u32 lcd_init()
{
    u32 *video_mem = (u32*)REG_VIDEOMEM_ADDR;
    u32 *video_mem_length = (u32*)REG_VIDEOMEM_LENGTH;
    u32 *lcd_initial = (u32*)REG_LCDINIT_ADDR;
    u32 *lcd_initial_length = (u32*)REG_LCDINIT_LENGTH;
    u32 *lcd_ctrl = (u32*)REG_LCD_CTRL;
    u32 *lcd_status = (u32*)REG_LCD_STATUS;

    u32 *init_parameter = (u32 *)LCD_INIT_BASE_ADDR;
    u32 *p = init_parameter;

    *video_mem = VIDEO_BASE_ADDR;
    *video_mem_length = VIDEO_LENGTH;
    *lcd_initial = LCD_INIT_BASE_ADDR;
    *lcd_initial_length = LCD_INIT_LENGTH;
    *lcd_ctrl = 0;
    u32 i;
    for(i=0; i<640; i++){
    	*(p++) = 0;
    }
    p = init_parameter;
    if(*lcd_status & 1)
    {
    	return 0;
    }
    else{
        *(p++) = 0xff;  // EXTC Command Set enable register
        *(p++) = 0x100ff;
        *(p++) = 0x10098;
        *(p++) = 0x10006;
        *(p++) = 0xba;  // SPI Interface Setting 
        *(p++) = 0x100e0;
        *(p++) = 0xbc;  // GIP 1
        *(p++) = 0x10003;
        *(p++) = 0x1000f;
        *(p++) = 0x10063;
        *(p++) = 0x10069;
        *(p++) = 0x10001;
        *(p++) = 0x10001;
        *(p++) = 0x1001b;
        *(p++) = 0x10011;
        *(p++) = 0x10070;
        *(p++) = 0x10073;
        *(p++) = 0x100ff;
        *(p++) = 0x100ff;
        *(p++) = 0x10008;
        *(p++) = 0x10009;
        *(p++) = 0x10005;
        *(p++) = 0x10000;
        *(p++) = 0x100ee;
        *(p++) = 0x100e2;
        *(p++) = 0x10001;
        *(p++) = 0x10000;
        *(p++) = 0x100c1;
        *(p++) = 0xbd;  //GIP 2
        *(p++) = 0x10001;
        *(p++) = 0x10023;
        *(p++) = 0x10045;
        *(p++) = 0x10067;
        *(p++) = 0x10001;
        *(p++) = 0x10023;
        *(p++) = 0x10045;
        *(p++) = 0x10067;
        *(p++) = 0xbe;  //GIP 3
        *(p++) = 0x10000;
        *(p++) = 0x10022;
        *(p++) = 0x10027;
        *(p++) = 0x1006a;
        *(p++) = 0x100bc;
        *(p++) = 0x100d8;
        *(p++) = 0x10092;
        *(p++) = 0x10022;
        *(p++) = 0x10022;
        *(p++) = 0xc7;  //Vcom
        *(p++) = 0x1001e;
        *(p++) = 0xed;  //EN_volt_reg;
        *(p++) = 0x1007f;
        *(p++) = 0x1000f;
        *(p++) = 0x10000;
        *(p++) = 0xc0; //Power Control 1
        *(p++) = 0x100e3;
        *(p++) = 0x1000b;
        *(p++) = 0x10000;
        *(p++) = 0xfc;
        *(p++) = 0x10008;
        *(p++) = 0xdf; //Engineering Setting
        *(p++) = 0x10000;
        *(p++) = 0x10000;
        *(p++) = 0x10000;
        *(p++) = 0x10000;
        *(p++) = 0x10000;
        *(p++) = 0x10002;
        *(p++) = 0xf3;  //DVDD Voltage Setting
        *(p++) = 0x10074;
        *(p++) = 0xb4;  //Display Inversion Control
        *(p++) = 0x10000;
        *(p++) = 0x10000;
        *(p++) = 0x10000;
        *(p++) = 0xf7;  //Panel Resolution Selection Set
        *(p++) = 0x10081;
        *(p++) = 0xb1;  //Frame Rate
        *(p++) = 0x10000;
        *(p++) = 0x10010;
        *(p++) = 0x10014;
        *(p++) = 0xf1;  //Panel Timing Control
        *(p++) = 0x10029;
        *(p++) = 0x1008a;
        *(p++) = 0x10007;
        *(p++) = 0xf2;  //Panel Timing Control
        *(p++) = 0x10040;
        *(p++) = 0x100d2;
        *(p++) = 0x10050;
        *(p++) = 0x10028;
        *(p++) = 0xc1;  //Power Control 2
        *(p++) = 0x10017;
        *(p++) = 0x10085;
        *(p++) = 0x10085;
        *(p++) = 0x10020;
        *(p++) = 0xe0;  //Positive Gamma Control
        *(p++) = 0x10000;
        *(p++) = 0x1000c;
        *(p++) = 0x10015;
        *(p++) = 0x1000d;
        *(p++) = 0x1000f;
        *(p++) = 0x1000c;
        *(p++) = 0x10007;
        *(p++) = 0x10005;
        *(p++) = 0x10007;
        *(p++) = 0x1000b;
        *(p++) = 0x10010;
        *(p++) = 0x10010;
        *(p++) = 0x1000d;
        *(p++) = 0x10017;
        *(p++) = 0x1000f;
        *(p++) = 0x10000;
        *(p++) = 0xe1;  //Negative Gamma Correction
        *(p++) = 0x10000;
        *(p++) = 0x1000d;
        *(p++) = 0x10015;
        *(p++) = 0x1000e;
        *(p++) = 0x10010;
        *(p++) = 0x1000d;
        *(p++) = 0x10008;
        *(p++) = 0x10006;
        *(p++) = 0x10007;
        *(p++) = 0x1000c;
        *(p++) = 0x10011;
        *(p++) = 0x10011;
        *(p++) = 0x1000e;
        *(p++) = 0x10017;
        *(p++) = 0x1000f;
        *(p++) = 0x10000;
        *(p++) = 0x35;  //Tearing Effect ON
        *(p++) = 0x10000;
        *(p++) = 0x36;
        *(p++) = 0x10060;
        *(p++) = 0x3a;
        *(p++) = 0x10055;
        *(p++) = 0x11;  //Exit Sleep
        *(p++) = 0x29;  //Display On

        *(p++) = 0x2a;  //鐠佸墽鐤嗛崶鍓у闂�锟�854
        *(p++) = 0x10000;
        *(p++) = 0x10000;
        *(p++) = 0x10003; // 0x0355 = 853
        *(p++) = 0x10055;
        *(p++) = 0x2b;  //鐠佸墽鐤嗛崶鍓у鐎癸拷480
        *(p++) = 0x10000;
        *(p++) = 0x10000;
        *(p++) = 0x10001; // 0x01df = 479
        *(p++) = 0x100df;
        *(p++) = 0x2c;  //Memory Write
        
        *lcd_ctrl = 1;  //閸掓繂顫愰崠鏍ф嚒娴犮倧绱濋幒褍鍩楅崳銊ㄧ箻閸忣檼CD閸掓繂顫愰崠鏍Ц閹拷
        for(i=0; i< 500000; i++){
        // 	if(*lcd_status & 2){
        // 	    *lcd_ctrl = 0;
        // 	}
         	if(*lcd_status & 1){
             	return 1;   //鐟欏嫬鐣鹃弮鍫曟？閸愬導CD閸掓繂顫愰崠鏍х暚閹存劧绱濇潻鏂挎礀1
             }
         }
        return -1;  //LCD閸掓繂顫愰崠鏍Т閺冭埖婀�瑰本鍨氶敍宀冪箲閸ワ拷-1
    }
}
