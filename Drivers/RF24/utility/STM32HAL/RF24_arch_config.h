
#ifndef __ARCH_CONFIG_H__
#define __ARCH_CONFIG_H__

  #define RF24_STM32
  
  #include <stdint.h>
  #include <stdio.h>
  #include <time.h>
  #include <string.h>
//  #include <sys/time.h>
  #include <stddef.h>
  
  #include "stm32f1xx_hal.h"
//  #include "spi.h"
//  #define _SPI spi

  // GCC a Arduino Missing
  #define _BV(x) (1<<(x))
  #define pgm_read_word(p) (*(p))
  #define pgm_read_byte(p) (*(p))
  
  //typedef uint16_t prog_uint16_t;
  #define PSTR(x) (x)
  #define printf_P printf
  #define strlen_P strlen
  #define PROGMEM
  #define PRIPSTR "%s"

#define delay HAL_Delay

  #ifdef SERIAL_DEBUG
	#define IF_SERIAL_DEBUG(x) ({x;})
  #else
	#define IF_SERIAL_DEBUG(x)
  #endif

#include <hal_ardu.h>
  
//  #define OUTPUT BCM2835_GPIO_FSEL_OUTP
  
#endif
