/**
  ******************************************************************************
  * @file    detection_button.c
  * @author  Mathis VEBER
  * @author  Martin FLEURY
  * @date    2022
  * @brief   fonction detection etat bouton
  * version  2.0
  ******************************************************************************
*/


#include <detection_button.h>

#include "stm32f1_gpio.h"
#include "macro_types.h"



/**
 *
  * @fn button_id_e button_press_event()
  * @brief  Permets de detecter un appui sur un bouton
  * @details L'appui se caracterise par un changement d'etat representer par un tableau avec les 5 boutons poussoirs
  * @return button_id_e retourne le bouton appuye ou BUTTON_ID_NONE si aucun bouton n'est appuye


*/
button_id_e button_press_event(void)
		{

			static bool_e previous_state[BUTTON_ID_NB]={FALSE};

			button_id_e ret=BUTTON_ID_NONE;
			button_id_e button_id;

			bool_e current_state;


			for(button_id = BUTTON_ID_LEFT; button_id<BUTTON_ID_NB; button_id++)
			{

			switch(button_id)

			{
			case BUTTON_ID_LEFT:
			 current_state = !HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6);
			break;

			case BUTTON_ID_RIGHT:
			current_state=!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5);
			break;

			case BUTTON_ID_UP:
			current_state=!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7);
			break;

			case BUTTON_ID_DOWN:
			current_state=!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);
			break;

			case BUTTON_ID_RESET:
				current_state=!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
				break;

			default:
			current_state=0;
			break;
			}

			if(current_state&&!previous_state[button_id])
			{

			ret=button_id;
			previous_state[button_id]=current_state;

			return ret;
			}

			if(!current_state&&previous_state[button_id])
						{
						previous_state[button_id]=FALSE;

			}
			}

			return ret;

			}
