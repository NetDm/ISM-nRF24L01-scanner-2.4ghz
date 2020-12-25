//#include <SpiStm32ino.h>                                                                                     // подключаем библиотеку SPI для работы с шиной SPI

#include <st7735.h>

#include <nRF24L01.h>                                                                                       // подключаем файл настроек из библиотеки RF24
#include <RF24.h>

#include "Scanner.h"

const void *p_setupScann=(void*)setupScann;
const void *p_loopScann=(void*)loopScann;

#include "usbd_cdc_if.h"


// подключаем библиотеку RF24 для работы с модулем nRF24L01+
																											// подключаем библиотеку UTFT для работы с TFT дисплеем
//UTFT            myGLCD(TFT01_22SP, 7, 8, 4, 5, 6);                                                          // объявляем  объект myGLCD для работы с библиотекой UTFT, указывая тип дисплея и выводы (TFT01_22SP, SDI/MOSI, SCK, CS, RESET, DC/RS);
	//RF24(uint8_t _cepin, uint8_t _cspin);
RF24            radio(29, 25 );                                                                               // создаём объект radio для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)
extern uint8_t  SmallFont[];                                                                                // подключаем маленький шрифт
       uint8_t  Loading        = 0;                                                                         // первый проход по не сохраняется
       uint8_t  ChannelScan    = 1;                                                                         // номер сканируемого канала
       uint8_t  ChannelPrint   = 0;                                                                         // номер выводимого канала
       int32_t  ChannelPowerNow[128];                                                                       // текущая мощность сигналов на каждом канале
       int32_t  ChannelPowerMem[128];                                                                       // текущая мощность сигналов на каждом канале
       int32_t  ChannelPowerMax;//[128];                                                                       // максимальная мощность сигналов на каждом канале
       uint16_t PositionPoints[10];                                                                         // положение точек на дисплее
const  uint16_t ColorBG          = ST7735_BLACK;                                                               // цвет фона
const  uint16_t ColorScale       = ST7735_BLUE;                                                                // цвет шкалы и векторов графика
const  uint16_t ColorTextLoad    = ST7735_WHITE;                                                               // цвет текста отображающего проценты при старте
const  uint16_t ColorGraphNow    = ST7735_WHITE;                                                               // цвет графика отображающего текущие значения
const  uint16_t ColorGraphMax    = ST7735_RED;     // цвет графика отображающего максимальные значения
const  uint16_t PositionLeft     = 0;          // крайнее левое положение графика на дисплее
const  uint16_t PositionWidth    = 1;			// ширина одного канала на дисплее
const  uint16_t PositionTop      = 10;          // крайнее верхнее положение графика на дисплее
const  uint16_t PositionBottom   = 127;         // крайнее нижнее  положение графика на дисплее
const  uint8_t  PositionHeight1  = 3;           // размер каждой 1  линии каналов на нижней шкале графика
const  uint8_t  PositionHeight5  = 9;          	// размер каждой 5  линии каналов на нижней шкале графика
const  uint8_t  PositionHeight10 = 15; 			// размер каждой 10 линии каналов на нижней шкале графика
const  uint8_t  FactorGraph      = 1;           // множитель значений графика

const uint16_t CENTER=128/2;


const int y0=20;
const int H=ST7735_HEIGHT-1-y0;


void setupScann(){
//  подготавливаем дисплей и модуль к работе
	ST7735_Init();
	ST7735_FillScreen(/*ST7735_COLOR565(48,48,48)*/ST7735_BLACK);
    radio.begin();                                                                                          // инициируем работу модуля nRF24L01+
    radio.setAutoAck(false);                                                                                // отключаем режим подтверждения приёма
    memset(ChannelPowerNow, 0, sizeof(ChannelPowerNow));                                                    // заполняем все элементы массива ChannelPowerNow значением 0
    memset(ChannelPowerMem, 1, sizeof(ChannelPowerMem));
    ChannelPowerMax=0;

	ST7735_FillRectangle(0,y0-1,128,1,ST7735_COLOR565(192,192,192));

	ST7735_setColor(ST7735_GREEN);

    int i=120;
    do{
		ST7735_FillRectangle(i,y0-2-5,1,4,ST7735_COLOR565(192,192,192));
    }while (i-=10);

	ST7735_print("0",0,0);

	ST7735_print("50",50-Font_7x10.width,0);

	ST7735_print("100",100-Font_7x10.width*1.5,0);

	ST7735_FillRectangle(50 ,y0-2-7,1,7,ST7735_GREEN);
	ST7735_FillRectangle(100,y0-2-7,1,7,ST7735_GREEN);

	radio.setChannel(0);
	radio.startListening();             // начинаем прослушивать очередной канал
	HAL_Delay(150);                                                // ждём 50 мкс
	radio.stopListening();                        // останавливаем прослушивание

	// заполняем все элементы массива ChannelPowerMax значением 0
//    PositionPoints[6]=PositionBottom-Font_7x10.height;                                                 // положение текста с номерами каналов
//    PositionPoints[7]=PositionBottom-Font_7x10.height*2;                                               // положение текста с числами частот
//    PositionPoints[8]=PositionBottom-Font_7x10.height*2-PositionHeight10;                              // положение нулевой координаты по оси Y
////  выводим нижнюю шкалу графика для всего диапазона каналов
//        ST7735_setColor(ColorScale);                                                                        // устанавливаем цвет заливки шкалы
//    for(uint8_t i=0; i<128; i++){                                                                           // создаём цикл по всему диапазону каналов
//        PositionPoints[9]=PositionLeft+i*PositionWidth;                                                     // положение координаты очередного канала по оси X
//        ST7735_drawLine(PositionPoints[9],i?PositionPoints[8]:PositionTop,PositionPoints[9],PositionPoints[8]+(i%10?(i%5?PositionHeight1:PositionHeight5):PositionHeight10));  // выводим вертикальные линии шкалы графика
//        if(i%20==0){ST7735_printNumI(i, PositionPoints[9]-(i==0?(ST7735_getFontXsize()/2):(i<100?(ST7735_getFontXsize()):(ST7735_getFontXsize()*3/2))), PositionPoints[7]);} // выводим текст - номера каналов
//        if(i%40==0){ST7735_printNumI(((int)2400+i), PositionPoints[9]-(i==0?(ST7735_getFontXsize()/2):(ST7735_getFontXsize()*2)), PositionPoints[6]);} // выводим текст - частоты каналов
//    }   ST7735_drawLine(PositionLeft,PositionPoints[8],(PositionLeft+128*PositionWidth),PositionPoints[8]); // выводим горизонтальную линию
//        ST7735_print("N",   PositionLeft+129*PositionWidth, PositionPoints[7]);                             // выводим название шкалы - номер  канала
//        ST7735_print("MGz", PositionLeft+129*PositionWidth, PositionPoints[6]);                             // выводим название шкалы - частота канала
}

void loopScann(){
	char txt[32]={0,};
	int refresh;

//  сканируем очередной канал и сохраняем его данные
	radio.setChannel(ChannelScan); // устанавливаем очередной канал работы модуля
	radio.startListening();             // начинаем прослушивать очередной канал
	delayMicroseconds(50);                                                // ждём 50 мкс
	static int x=0,toggle=0;
	if (++x>7) {x=0;toggle=((toggle==0)?1:0);}
	ST7735_FillRectangle(x+120, 0,1,10, ST7735_BLUE*toggle);
	radio.stopListening();                        // останавливаем прослушивание
	if (radio.testRPD()) {
		ChannelPowerNow[ChannelScan]++;
	} // если сигнал на указанном канале имел мощность > -64 дБм, то увеличиваем значение в массиве ChannelPowerNow для текущего канала (функция не работает на модулях nRF24L01 без знака «+»)
	if (ChannelPowerMax < ChannelPowerNow[ChannelScan]) { // если мощность отсканированного канала превышает ранее полученное максимальное значение для этого канала, то ...
		ChannelPowerMax = ChannelPowerNow[ChannelScan]; // сохраняем мощность отсканированного канала как максимальную
		refresh=1;
	}
	ChannelScan++;                      // увеличиваем номер сканируемого канала

	//  выводим полученные данные                                                                               // данные выводятся по одному каналу, через полный цикл сканирования всех каналов
	if (ChannelScan == 128) { // если был просканирован последний возможный канал, то ...
		ChannelScan = 1;                                 // переходим к 0 каналу

		HAL_GPIO_TogglePin(fromMX(LED_FLASH));

		ChannelPrint=0;
		do{
			if ( (ChannelPowerNow[ChannelPrint]!=ChannelPowerMem[ChannelPrint]) || (refresh!=0) ) {
				ChannelPowerMem[ChannelPrint]=ChannelPowerNow[ChannelPrint];
				int h=(double)(H)*ChannelPowerNow[ChannelPrint]/ChannelPowerMax;
				ST7735_FillRectangle(ChannelPrint,y0		,1,H-(h-1)	,ST7735_BLACK);
				ST7735_FillRectangle(ChannelPrint,y0+H-(h)	,1,(h+1)	,ST7735_YELLOW);
			}
	//			ST7735_DrawPixel(ChannelPrint,ST7735_HEIGHT-1-ChannelPowerMax[ChannelPrint],ST7735_RED);


			}while(128>= (++ChannelPrint));
		refresh=0;
	}
}
