/**
  ******************************************************************************
  * @file    detection_capteur.c
  * @author  Mathis VEBER
  * @author  Martin FLEURT
  * @date    2022
  * @brief   fonction detection etat capteur
  * version  2.0
  ******************************************************************************
*/


#include <detection_capteur.h>

#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"

/**
 *
  * @fn   writebbisLED(bool_e)
  * @brief  Permets de modifier l'etat de la LED de la bluePill
  * @param  b Si TRUE la LED s'allume sinon si FALSE la led s'éteint

*/

void writeLEDbbis(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

/**
 *
  * @fn   writerubanLED(bool_e c)
  * @brief  Permets de modifier l'etat d'un ruban de LED
  * @param  b Si TRUE les LED s'allume sinon si FALSE les LED s'éteint

*/
void writerubanLED(bool_e c)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0, c);

}

/**
 *
  * @fn   writeruban2LED(bool_e d)
  * @brief  Permets de modifier l'etat d'un ruban de LED
  * @param  b Si TRUE les LED s'allume sinon si FALSE les LED s'éteint

*/
void writeruban2LED(bool_e d)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1, d);

}




/**
 *
  * @fn   capteur_detect_event()
  * @brief  Permets de detecter une zone capte par un capteur IR et d'allumer le ruban de LED associe à cette zone
  * @details La detection d'un capteur se caracterise par un bouton etat 0 ou 1

*/
void capteur_detect_event(void)
		{

			 if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)){ //Mesure l'etat du capteur IR

				 writerubanLED(TRUE);//Allume le deuxième ruban de LED
				 writeLEDbbis(FALSE);//Allume la LED NUCLEO


			 }


			 if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)){ //Mesure l'etat du capteur IR

				 writeruban2LED(TRUE);//Allume le deuxième ruban de LED
				 writeLEDbbis(FALSE);//Allume la LED NUCLEO
			 }




}

