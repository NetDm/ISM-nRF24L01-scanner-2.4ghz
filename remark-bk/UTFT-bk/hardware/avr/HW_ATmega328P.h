// *** Hardwarespecific functions ***
void UTFT::_hw_special_init()
{
}

void UTFT::LCD_Writ_Bus(char VH,char VL, byte mode)
{   
	switch (mode)
	{
	case 1:
		if (display_serial_mode==SERIAL_4PIN)
		{
		if (VH==1)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		}
		else
		{
		if (VH==1)
			sbi(P_RS, B_RS);
		else
			cbi(P_RS, B_RS);
		}

		if (VL & 0x80)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x40)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x20)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x10)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x08)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x04)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x02)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x01)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		break;
	case 8:
		if (display_model==ILI9341_UNO || display_model==ILI9327_UNO)
		{
			cport(PORTB,      0xFC);    // сбрасываем в 0 младшие 2 бита порта B
			sport(PORTB, VH & 0x03);    // устанавливаем значение младших 2 битов порта B
			cport(PORTD,      0x03);    // сбрасываем в 0 старшие 6 битов порта D
			sport(PORTD, VH & 0xFC);    // устанавливаем значение старших 6 битов порта D
			if(!LCD_Write_1byte_Flag){pulse_low(P_WR, B_WR);}
			cport(PORTB,      0xFC);    // сбрасываем в 0 младшие 2 бита порта B
			sport(PORTB, VL & 0x03);    // устанавливаем значение младших 2 битов порта B
			cport(PORTD,      0x03);    // сбрасываем в 0 старшие 6 битов порта D
			sport(PORTD, VL & 0xFC);    // устанавливаем значение старших 6 битов порта D
			pulse_low(P_WR, B_WR);
		}
		else if (display_model==ILI9341_MEGA)
		{
			digitalWrite(2, bitRead(VH,2));
			digitalWrite(3, bitRead(VH,3));
			digitalWrite(4, bitRead(VH,4));
			digitalWrite(5, bitRead(VH,5));
			digitalWrite(6, bitRead(VH,6));
			digitalWrite(7, bitRead(VH,7));
			digitalWrite(8, bitRead(VH,0));
			digitalWrite(9, bitRead(VH,1));
			if(!LCD_Write_1byte_Flag){pulse_low(P_WR, B_WR);}
			digitalWrite(2, bitRead(VL,2));
			digitalWrite(3, bitRead(VL,3));
			digitalWrite(4, bitRead(VL,4));
			digitalWrite(5, bitRead(VL,5));
			digitalWrite(6, bitRead(VL,6));
			digitalWrite(7, bitRead(VL,7));
			digitalWrite(8, bitRead(VL,0));
			digitalWrite(9, bitRead(VL,1));
			pulse_low(P_WR, B_WR);
		}
		else
		{
			PORTD = VH;
			pulse_low(P_WR, B_WR);
			PORTD = VL;
			pulse_low(P_WR, B_WR);
		}
		
		break;
	case 16:
		PORTD = VH;
		cport(PORTC, 0xFC);
		sport(PORTC, (VL>>6) & 0x03);
		PORTB =  VL & 0x3F;
		pulse_low(P_WR, B_WR);
		break;
	case LATCHED_16:
		PORTD = VH;
		cbi(P_ALE, B_ALE);
		pulse_high(P_ALE, B_ALE);
		cbi(P_CS, B_CS);
		PORTD =  VL;
		pulse_low(P_WR, B_WR);
		sbi(P_CS, B_CS);
		break;
	}
}

void UTFT::_set_direction_registers(byte mode)
{
	if (display_model==ILI9341_UNO || display_model==ILI9327_UNO)
	{
		DDRD |= 0xFC;
		DDRB |= 0x03;
	}
	else if (display_model==ILI9341_MEGA)
	{
		pinMode(2, OUTPUT); 
		pinMode(3, OUTPUT); 
		pinMode(4, OUTPUT); 
		pinMode(5, OUTPUT); 
		pinMode(6, OUTPUT); 
		pinMode(7, OUTPUT); 
		pinMode(8, OUTPUT); 
		pinMode(9, OUTPUT); 
	}
	else
	{
		DDRD = 0xFF;
	}
	if (mode==16)
	{
		DDRB |= 0x3F;
		DDRC |= 0x03;
	}

}

void UTFT::_fast_fill_16(int ch, int cl, long pix)
{
	long blocks;

	PORTD = ch;
	cport(PORTC, 0xFC);
	sport(PORTC, (cl>>6) & 0x03);
	PORTB =  cl & 0x3F;

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
	}
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16)+1; i++)
		{
			pulse_low(P_WR, B_WR);
		}
}

void UTFT::_fast_fill_8(int ch, long pix)
{
	long blocks;
	if (display_model==ILI9341_UNO || display_model==ILI9327_UNO)
	{
		cport(PORTB,      0xFC);    // сбрасываем в 0 младшие 2 бита порта B
		sport(PORTB, ch & 0x03);    // устанавливаем значение младших 2 битов порта B
		cport(PORTD,      0x03);    // сбрасываем в 0 старшие 6 битов порта D
		sport(PORTD, ch & 0xFC);    // устанавливаем значение старших 6 битов порта D
	}
	else if (display_model==ILI9341_MEGA)
	{
		digitalWrite(2, bitRead(ch,2));
		digitalWrite(3, bitRead(ch,3));
		digitalWrite(4, bitRead(ch,4));
		digitalWrite(5, bitRead(ch,5));
		digitalWrite(6, bitRead(ch,6));
		digitalWrite(7, bitRead(ch,7));
		digitalWrite(8, bitRead(ch,0));
		digitalWrite(9, bitRead(ch,1));
	}
	else
	{
		PORTD = ch;
	}
	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
	}
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16)+1; i++)
		{
			pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		}
}
