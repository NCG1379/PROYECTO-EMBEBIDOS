/*
    PLAY Embedded demos - Copyright (C) 2014-2017 Rocco Marco Guglielmi

    This file is part of PLAY Embedded demos.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 *  Tested under ChibiOS 17.6.x Stable, Project version 3.0.
 *  Please open readme.txt for changelog.
 */

#include "ch.h"
#include "hal.h"
#include "ch_test.h"


#include "./userlib/include/lcd.h"
#include "./userlib/include/SFR02main.h"

//static uint8_t ii;

#define LINE_ARD_D14                PAL_LINE(GPIOB, 9U)
#define LINE_ARD_D15                PAL_LINE(GPIOB, 8U)

#define USART_CR1_9BIT_WORD     (1 << 12)   /* CR1 9 bit word */
#define USART_CR1_PARITY_SET    (1 << 10)   /* CR1 parity bit enable */
#define USART_CR1_EVEN_PARITY   (0 << 9)    /* CR1 even parity */


/*
 * I2C1 config.
 */
static const I2CConfig i2cfg1 = {
    OPMODE_I2C,
    100000,
    STD_DUTY_CYCLE,
};

/*
 * UART config.

 */

static SerialConfig sdcfg1 = {
    9600,                                 /* 9600 baud rate */
    USART_CR1_9BIT_WORD | USART_CR1_PARITY_SET | USART_CR1_EVEN_PARITY,
    USART_CR2_STOP1_BITS | USART_CR2_LINEN,
    0
};

static SerialConfig sdcfg2 = {
    9600,                                 /* 9600 baud rate */
    USART_CR1_9BIT_WORD | USART_CR1_PARITY_SET | USART_CR1_EVEN_PARITY,
    USART_CR2_STOP1_BITS | USART_CR2_LINEN,
    0
};


/*
static THD_WORKING_AREA(waRead, 128);
static THD_FUNCTION(ThReader, arg) {
    (void)arg;

	while (TRUE){

		uint8_t c = sdGet(&SD2);
	    sdPut(&SD2, c);
	}
}
*/


/*
 * Button checker. This thread turn on and off LCD backlight when USER button
 * is pressed. Fade transition is applied when library use PWM.
 */

/*
static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {

  (void)arg;
  chRegSetThreadName("Back_light handler");
  while (true) {
    if(palReadPad(GPIOC, GPIOC_BUTTON)) {
      chThdSleepMilliseconds(50);
      if(!palReadPad(GPIOC, GPIOC_BUTTON))
        LCDD1.backlight ? lcdBacklightOff(&LCDD1) : lcdBacklightOn(&LCDD1);
    }
    chThdSleepMilliseconds(10);
  }
}
*/


/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();
  boardInit();
	//ssdInit();
  sdStart(&SD2, &sdcfg1);
	sdStart(&SD3, &sdcfg2);
  i2cStart(&I2CD1, &i2cfg1);


/*
	palSetPadMode(GPIOA, 2, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetPadMode(GPIOA, 3, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
*/


  palSetPadMode(GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
  palSetPadMode(GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);

	//chThdCreateStatic(waRead, sizeof(waRead), NORMALPRIO, ThReader, NULL);
	//chprintf((BaseChannel *)&SD2, "\n Presione algo,plz\n\r" );
	

   while(true){

		//i2cStart(&I2CD1, &i2cfg1);
  	Sfr02Start();

		

		chThdSleepMilliseconds(500);
		if(!sdGetWouldBlock(&SD3)){
		uint8_t c = sdGet(&SD3);
		chprintf((BaseChannel *)&SD2, "El valor es= %d\n\r",c);
		}else{
		chprintf((BaseChannel *)&SD2, "Tal ves deberias considerar ser taxista :'v \n\r");
	  }
		
   }

/*
  while (true) {
    for(ii = 0; ii < 16; ii++){
      lcdDoDisplayShift(&LCDD1, LCD_LEFT);
      chThdSleepMilliseconds(50);
    }
    chThdSleepMilliseconds(2000);
    for(ii = 0; ii < 16; ii++){
      lcdDoDisplayShift(&LCDD1, LCD_RIGHT);
      chThdSleepMilliseconds(50);
    }
    chThdSleepMilliseconds(2000);
*/
}

//BOOM BOOM BOOOM https://www.youtube.com/watch?v=GsRrswyAEs0 :)
