case ILI9327_UNO:
	LCD_Write_COM(0xE0);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x07);
	LCD_Write_DATA(0x10);
	LCD_Write_DATA(0x09);
	LCD_Write_DATA(0x17);
	LCD_Write_DATA(0x0B);
	LCD_Write_DATA(0x40);
	LCD_Write_DATA(0x8A);
	LCD_Write_DATA(0x4B);
	LCD_Write_DATA(0x0A);
	LCD_Write_DATA(0x0D);
	LCD_Write_DATA(0x0F);
	LCD_Write_DATA(0x15);
	LCD_Write_DATA(0x16);
	LCD_Write_DATA(0x0F);

	LCD_Write_COM(0xE1);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x1A);
	LCD_Write_DATA(0x1B);
	LCD_Write_DATA(0x02);
	LCD_Write_DATA(0x0D);
	LCD_Write_DATA(0x05);
	LCD_Write_DATA(0x30);
	LCD_Write_DATA(0x35);
	LCD_Write_DATA(0x43);
	LCD_Write_DATA(0x02);
	LCD_Write_DATA(0x0A);
	LCD_Write_DATA(0x09);
	LCD_Write_DATA(0x32);
	LCD_Write_DATA(0x36);
	LCD_Write_DATA(0x0F);

	LCD_Write_COM(0xB1); 
	LCD_Write_DATA(0xA0);

	LCD_Write_COM(0xB4);
	LCD_Write_DATA(0x02);

	LCD_Write_COM(0xC0);
	LCD_Write_DATA(0x17);
	LCD_Write_DATA(0x15);

	LCD_Write_COM(0xC1);
	LCD_Write_DATA(0x41);

	LCD_Write_COM(0xC5);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x0A);
	LCD_Write_DATA(0x80);

	LCD_Write_COM(0xB6);
	LCD_Write_DATA(0x02);

	LCD_Write_COM(0x36);
	LCD_Write_DATA(0x48);   

	LCD_Write_COM(0x3a);    
	LCD_Write_DATA(0x55);
	LCD_Write_COM(0xE9);
	LCD_Write_DATA(0x00);  

	LCD_Write_COM(0XF7);
	LCD_Write_DATA(0xA9);
	LCD_Write_DATA(0x51);
	LCD_Write_DATA(0x2C);
	LCD_Write_DATA(0x82);

	LCD_Write_COM(0x11);
	delay(120);
	LCD_Write_COM(0x29);
	break;