

#include "./../include/SFR02main.h"

#if USERLIB_USE_GYRO || defined(__DOXYGEN__)

#define ADDRESS_SFR02  	0x70
#define ULTS_CTRL_REG1  0x00
#define MEASURE_CENTI		0x51
#define REGISTER_POINT	0x02

#define LINE_ARD_D14                PAL_LINE(GPIOB, 9U)
#define LINE_ARD_D15                PAL_LINE(GPIOB, 8U)


/* buffers */
static uint8_t SDA_rx_data[8];
static uint8_t SDA_tx_data[8];
static uint8_t SDA_value[8];


/*
 * I2C1 config.
 */
static const I2CConfig i2cfg1 = {
    OPMODE_I2C,
    100000,
    STD_DUTY_CYCLE,
};


void Sfr02Start(void){
	  msg_t status = MSG_OK;
	//  systime_t tmo = MS2ST(4);
	  short result;	
	  
	  /* configure gyroscope */
	  SDA_tx_data[0] = ULTS_CTRL_REG1;
	  SDA_tx_data[1] = MEASURE_CENTI ;
		SDA_value[0]= REGISTER_POINT;
	  
	  

	  /* sending  */
	  i2cAcquireBus(&I2CD1);
	  status = i2cMasterTransmitTimeout(&I2CD1, ADDRESS_SFR02, SDA_tx_data, 2, NULL, 0, TIME_INFINITE);
	  i2cReleaseBus(&I2CD1);

	  chThdSleepMilliseconds(70);

	  i2cAcquireBus(&I2CD1);
	  status = i2cMasterTransmitTimeout(&I2CD1, ADDRESS_SFR02, SDA_value, 1, NULL, 0, TIME_INFINITE);
	  i2cReleaseBus(&I2CD1);

		i2cAcquireBus(&I2CD1);
		i2cMasterReceiveTimeout(&I2CD1, ADDRESS_SFR02, SDA_rx_data, 2,TIME_INFINITE);
		i2cReleaseBus(&I2CD1);


	  /* receiving  */
/*
	  i2cAcquireBus(&I2CD1);
	  status = i2cMasterTransmitTimeout(&I2CD1, ADDRESS_SFR02, NULL, 0, SDA_rx_data, 2, TIME_INFINITE);
	  i2cReleaseBus(&I2CD1);
*/

	  result = (SDA_rx_data[0]<<8) | SDA_rx_data[1];
		
		chprintf((BaseChannel *)&SD2, "El resultado es= %d\n\r",result);
		//sdPut(&SD2,result);
		chThdSleepMilliseconds(500);
		

	  
		return;

	  //chprintf((BaseChannel *)&SD3, "Dato= " );

}

/*
int main(void) {

  halInit();
  chSysInit();

  i2cStart(&I2CD1, &i2cfg1);

 while(true){

  sfr02Start();

 }
  */


#endif

