#include <SPI.h>                                                                                            // подключаем библиотеку SPI для работы с шиной SPI
#include "nRF24L01.h"                                                                                       // подключаем файл настроек из библиотеки RF24
#include "RF24.h"                                                                                           // подключаем библиотеку RF24 для работы с модулем nRF24L01+
#include <UTFT.h>                                                                                           // подключаем библиотеку UTFT для работы с TFT дисплеем
UTFT            myGLCD(TFT01_22SP, 7, 8, 4, 5, 6);                                                          // объявляем  объект myGLCD для работы с библиотекой UTFT, указывая тип дисплея и выводы (TFT01_22SP, SDI/MOSI, SCK, CS, RESET, DC/RS);
RF24            radio(9, 10);                                                                               // создаём объект radio для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)
extern uint8_t  SmallFont[];                                                                                // подключаем маленький шрифт
       uint8_t  Loading        = 0;                                                                         // первый проход по не сохраняется
       uint8_t  ChannelScan    = 0;                                                                         // номер сканируемого канала
       uint8_t  ChannelPrint   = 1;                                                                         // номер выводимого канала
       uint8_t  ChannelPowerNow[128];                                                                       // текущая мощность сигналов на каждом канале
       uint8_t  ChannelPowerMax[128];                                                                       // максимальная мощность сигналов на каждом канале
       uint16_t PositionPoints[10];                                                                         // положение точек на дисплее
const  uint16_t ColorBG          = VGA_BLACK;                                                               // цвет фона
const  uint16_t ColorScale       = VGA_BLUE;                                                                // цвет шкалы и векторов графика
const  uint16_t ColorTextLoad    = VGA_WHITE;                                                               // цвет текста отображающего проценты при старте
const  uint16_t ColorGraphNow    = VGA_WHITE;                                                               // цвет графика отображающего текущие значения
const  uint16_t ColorGraphMax    = VGA_RED;                                                                 // цвет графика отображающего максимальные значения
const  uint16_t PositionLeft     = 20;                                                                      // крайнее левое положение графика на дисплее
const  uint16_t PositionWidth    = 2;                                                                       // ширина одного канала на дисплее
const  uint16_t PositionTop      = 10;                                                                      // крайнее верхнее положение графика на дисплее
const  uint16_t PositionBottom   = 230;                                                                     // крайнее нижнее  положение графика на дисплее
const  uint8_t  PositionHeight1  = 3;                                                                       // размер каждой 1  линии каналов на нижней шкале графика
const  uint8_t  PositionHeight5  = 9;                                                                       // размер каждой 5  линии каналов на нижней шкале графика
const  uint8_t  PositionHeight10 = 15;                                                                      // размер каждой 10 линии каналов на нижней шкале графика
const  uint8_t  FactorGraph      = 4;                                                                       // множитель значений графика

void setup(){
//  подготавливаем дисплей и модуль к работе
    myGLCD.InitLCD();                                                                                       // инициируем дисплей
    myGLCD.fillScr(ColorBG);                                                                                // заливаем дисплей цветом фона
    myGLCD.setFont(SmallFont);                                                                              // устанавливаем маленький шрифт
    myGLCD.setBackColor(ColorBG);                                                                           // устанавливаем цвет фона для фона текста
    radio.begin();                                                                                          // инициируем работу модуля nRF24L01+
    radio.setAutoAck(false);                                                                                // отключаем режим подтверждения приёма
    memset(ChannelPowerNow, 0, sizeof(ChannelPowerNow));                                                    // заполняем все элементы массива ChannelPowerNow значением 0
    memset(ChannelPowerMax, 0, sizeof(ChannelPowerMax));                                                    // заполняем все элементы массива ChannelPowerMax значением 0
    PositionPoints[6]=PositionBottom-myGLCD.getFontYsize();                                                 // положение текста с номерами каналов
    PositionPoints[7]=PositionBottom-myGLCD.getFontYsize()*2;                                               // положение текста с числами частот
    PositionPoints[8]=PositionBottom-myGLCD.getFontYsize()*2-PositionHeight10;                              // положение нулевой координаты по оси Y
//  выводим нижнюю шкалу графика для всего диапазона каналов
        myGLCD.setColor(ColorScale);                                                                        // устанавливаем цвет заливки шкалы
    for(uint8_t i=0; i<128; i++){                                                                           // создаём цикл по всему диапазону каналов
        PositionPoints[9]=PositionLeft+i*PositionWidth;                                                     // положение координаты очередного канала по оси X
        myGLCD.drawLine(PositionPoints[9],i?PositionPoints[8]:PositionTop,PositionPoints[9],PositionPoints[8]+(i%10?(i%5?PositionHeight1:PositionHeight5):PositionHeight10));  // выводим вертикальные линии шкалы графика
        if(i%20==0){myGLCD.printNumI(i, PositionPoints[9]-(i==0?(myGLCD.getFontXsize()/2):(i<100?(myGLCD.getFontXsize()):(myGLCD.getFontXsize()*3/2))), PositionPoints[7]);} // выводим текст - номера каналов
        if(i%40==0){myGLCD.printNumI(((int)2400+i), PositionPoints[9]-(i==0?(myGLCD.getFontXsize()/2):(myGLCD.getFontXsize()*2)), PositionPoints[6]);} // выводим текст - частоты каналов
    }   myGLCD.drawLine(PositionLeft,PositionPoints[8],(PositionLeft+128*PositionWidth),PositionPoints[8]); // выводим горизонтальную линию
        myGLCD.print("N",   PositionLeft+129*PositionWidth, PositionPoints[7]);                             // выводим название шкалы - номер  канала
        myGLCD.print("MGz", PositionLeft+129*PositionWidth, PositionPoints[6]);                             // выводим название шкалы - частота канала
}

void loop(){
//  сканируем очередной канал и сохраняем его данные
    radio.setChannel(ChannelScan);                                                                          // устанавливаем очередной канал работы модуля
    radio.startListening();                                                                                 // начинаем прослушивать очередной канал
    delayMicroseconds(50);                                                                                  // ждём 50 мкс
    radio.stopListening();                                                                                  // останавливаем прослушивание
    if(radio.testRPD()){ChannelPowerNow[ChannelScan]++;}                                                    // если сигнал на указанном канале имел мощность > -64 дБм, то увеличиваем значение в массиве ChannelPowerNow для текущего канала (функция не работает на модулях nRF24L01 без знака «+»)
    if (ChannelPowerMax[ChannelScan]<ChannelPowerNow[ChannelScan]){                                         // если мощность отсканированного канала превышает ранее полученное максимальное значение для этого канала, то ...
        ChannelPowerMax[ChannelScan]=ChannelPowerNow[ChannelScan];                                          // сохраняем мощность отсканированного канала как максимальную
    }   ChannelScan++;                                                                                      // увеличиваем номер сканируемого канала
//  выводим полученные данные                                                                               // данные выводятся по одному каналу, через полный цикл сканирования всех каналов
    if(ChannelScan==127){                                                                                   // если был просканирован последний возможный канал, то ...
        ChannelScan=0;                                                                                      // переходим к 0 каналу
        if(Loading<128){                                                                                    // если это первый проход по диапазону каналов после пуска, то
            Loading++;                                                                                      // увеличиваем счетчик каналов
            myGLCD.setColor(ColorTextLoad);                                                                 // устанавливаем цвет текста отображающего проценты при старте
            if(Loading>=128){myGLCD.print("    ",CENTER, PositionTop+10);}                                  // стираем текст
            else{myGLCD.print((String)map(Loading,0,127,0,100)+"%",CENTER,PositionTop+10);}                 // выводим количество процентов загруженной информации о мощности сигналов в каналах
        }else{                                                                                              // если это не первый проход по диапазону каналов, то ...
//          Рассчитываем положение точек графиков на дисплее
            PositionPoints[0]=PositionPoints[8]-ChannelPowerMax[ChannelPrint-1]*4; if(PositionPoints[0]<PositionTop){PositionPoints[0]=PositionTop;} // координата 1 точки по оси Y для графика максимальных значений
            PositionPoints[1]=PositionPoints[8]-ChannelPowerMax[ChannelPrint  ]*4; if(PositionPoints[1]<PositionTop){PositionPoints[1]=PositionTop;} // координата 2 точки по оси Y для графика максимальных значений
            PositionPoints[2]=PositionPoints[8]-ChannelPowerNow[ChannelPrint-1]*4; if(PositionPoints[2]<PositionTop){PositionPoints[2]=PositionTop;} // координата 1 точки по оси Y для графика текущих значений
            PositionPoints[3]=PositionPoints[8]-ChannelPowerNow[ChannelPrint  ]*4; if(PositionPoints[3]<PositionTop){PositionPoints[3]=PositionTop;} // координата 2 точки по оси Y для графика текущих значений
            PositionPoints[4]=(ChannelPrint-1)*PositionWidth+PositionLeft;                                  // координата 1 точки по оси X для обоих графиков
            PositionPoints[5]= ChannelPrint   *PositionWidth+PositionLeft;                                  // координата 2 точки по оси X для обоих графиков
//          Выводим графики на дисплей
            myGLCD.setColor(ColorBG);       myGLCD.fillRect(PositionPoints[4]+1,0,PositionPoints[5],PositionPoints[8]);                              // стираем с дисплея часть предыдущих графиков
            myGLCD.setColor(ColorScale);    myGLCD.drawLine(PositionPoints[4],PositionPoints[8],PositionPoints[5],PositionPoints[8]);                // выводим горизонтальную часть линии шкалы
            myGLCD.setColor(ColorGraphMax); myGLCD.drawLine(PositionPoints[4],PositionPoints[0],PositionPoints[5],PositionPoints[1]);                // выводим график максимальных данных
            myGLCD.setColor(ColorGraphNow); myGLCD.drawLine(PositionPoints[4],PositionPoints[2],PositionPoints[5],PositionPoints[3]);                // выводим график текущих данных
        }   ChannelPowerNow[ChannelPrint-1]=0;                                                              // стираем показания мощности для только что выведенного канала
            ChannelPrint++; if(ChannelPrint==128){ChannelPrint=1;}                                          // увеличиваем номер выводимого канала
    }
}
