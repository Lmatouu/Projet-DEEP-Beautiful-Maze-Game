/**
  ******************************************************************************
  * @file    servo.c
  * @author  Mathis VEBER
  * @author  Martin FLEURY
  * @date    2022
  * @brief   fonction controle servomoteurs
  * version  2.0
  ******************************************************************************
*/

#include "servo.h"
#include "config.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"

#define PERIOD_TIMER 10 //ms
static uint16_t current_positionx;
static uint16_t current_positiony;


//void SERVO_process_test(void)
	//	{
		//	static uint16_t position = 50;
			//static bool_e previous_button = FALSE;
			//bool_e current_button;
		//lecture du bouton bleu
			//current_button = !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
			//if(current_button && !previous_button) //si appui bouton
			//{
				//position = (position > 99)?0:(position+5); //de 0 à 100%, par pas de 5%
				//SERVO_set_position(position);
		//	}
			//previous_button = current_button; //sauvegarde pour le prochain passage
			//HAL_Delay(10); //anti-rebond "de fortune" en cadencant la lecture du bouton
		//}

/**
 *
  * @fn    void SERVO_init()
  * @brief  Initialise les deux servomoteurs avec leurs pulses et les positionnent à leurs positions initiales
  * @details Les positions initiales a ete dermine par des tests pour que le labyrinthe soit le plus droit possible
*/
void SERVO_init(void)
	{
	//initialisation et lancement du timer1 à une période de 10 ms
		TIMER_run_us(TIMER1_ID, PERIOD_TIMER*1000, FALSE); //10000us = 10ms

		//TIMER_run_us(TIMER3_ID, PERIOD_TIMER*1000, FALSE); //10000us = 10ms
	//activation du signal PWM sur le canal 1 du timer 1 (broche PA8)
		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_1, 150, FALSE, FALSE);

		TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_2, 150, FALSE, FALSE);
	//rapport cyclique reglé pour une position servo de 50%
		SERVO_set_position_axe_x(115,0,TRUE);
		current_positionx=115;

		SERVO_set_position_axe_y(115,0,TRUE);
		current_positiony=115;
	}

/**
 *
  * @fn    SERVO_reset()
  * @brief  Permets de reinitialiser la position des servomoteurs
  * @details La position reinitialiser est la postion initiale
*/

void SERVO_reset(void)
{
	SERVO_set_position_axe_x(115,0,TRUE);
			current_positionx=115;

			SERVO_set_position_axe_y(115,0,TRUE);
			current_positiony=115;
}
	//position est exprimée de 0 à 100.

/**
 *
  * @fn SERVO_set_position_axe_x(uint16_t, uint16_t, bool_e)
  * @brief  Permets de positioner la position d'un servomoteur suivant l'axe x
  * @details La position du servomoteur augmente ou diminue avec un pas positif ou négatif
  * @param  position la dernière position du servomoteur
  * @param pas le bond qui doit modifier l'ancienne position du servomoteur
  * @param saut si la position augmente TRUE ou diminue FALSE
*/

void SERVO_set_position_axe_x(uint16_t position , uint16_t pas, bool_e saut)
	{
	uint16_t prochainepostition;

	if(saut){
		 prochainepostition=position+pas; //écretage si l'utilisateur demande plus de 100%

	if(prochainepostition > 135 ){
			prochainepostition = 135;}
	}
	else{
		prochainepostition=position-pas;
		if(prochainepostition < 95){
			 prochainepostition=95;
		}
	}

		TIMER_set_duty(TIMER1_ID,TIM_CHANNEL_1,100+prochainepostition);//TODO : mise à jour du rapport cyclique.
	//duty doit être exprimé ici de 100 à 200 (sur 1000) (pour un rapport cyclique de 10% à 20%, c’est-à-dire une durée de pulse de 1 à 2ms dans la période de 10ms)
	//Donc on additionne 100 à position.
		current_positionx=prochainepostition;
	}

/**
 *
  * @fn SERVO_set_position_axe_y(uint16_t, uint16_t, bool_e)
  * @brief  Permets de positioner la position d'un servomoteur suivant l'axe y
  * @details La position du servomoteur augmente ou diminue avec un pas positif ou négatif
  * @param  position la dernière position du servomoteur
  * @param pas le bond qui doit modifier l'ancienne position du servomoteur
  * @param saut si la position augmente TRUE ou diminue FALSE
*/
void SERVO_set_position_axe_y(uint16_t position , uint16_t pas, bool_e saut)
{
	uint16_t prochainepostition;

	if(saut){
		prochainepostition=position+pas; //écretage si l'utilisateur demande plus de 100%

		if(prochainepostition > 135 ){
			prochainepostition = 135;}
	}
	else{
		prochainepostition=position-pas;
		if(prochainepostition < 95){
			prochainepostition=95;
		}
	}

			TIMER_set_duty(TIMER1_ID,TIM_CHANNEL_2,100+prochainepostition);//TODO : mise à jour du rapport cyclique.	//duty doit être exprimé ici de 100 à 200 (sur 1000) (pour un rapport cyclique de 10% à 20%, c’est-à-dire une durée de pulse de 1 à 2ms dans la période de 10ms)
	//Donc on additionne 100 à position.
		current_positiony=prochainepostition;
	}

/**
 *
  * @fn  uint16_t SERVO_get_position_axe_x()
  * @brief  Permets de donner la position actuelle du servomoteur X
  * @return la position actuelle du sermoteur X

*/
uint16_t SERVO_get_position_axe_x(void)
{
	return current_positionx;
}

/**
 *
  * @fn  uint16_t SERVO_get_position_axe_y()
  * @brief  Permets de donner la positio actuelle du servomoteur Y
  * @return la position actuelle du sermoteur Y

*/
uint16_t SERVO_get_position_axe_y(void)
{
	return current_positiony;
}


