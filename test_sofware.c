/**
  ******************************************************************************
  * @file    test_sofware.c
  * @author  Mathis VEBER
  * @author  Martin FLEURY
  * @date    2022
  * @brief   fonction de test sofware du programme
  * version  2.0
  ******************************************************************************
*/

#include "servo.h"
#include "config.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "detection_button.h"
#include "detection_capteur.h"



/**
 *
  * @fn Test_Position_Servomoteurs_Init()
  * @brief  Permets de vérifier la position initiale des servomoteurs
*/

void Test_Position_Servomoteurs_Init(void){
	SERVO_init();
	printf("Les servomoteurs doivent être initialiser en position en x=115 et en y=115",SERVO_get_position_axe_x(),SERVO_get_position_axe_y);
}

/**
 *
  * @fn Test_Position_Servomoteurs_Reset()
  * @brief  Permets de vérifier la position reset des servomoteurs
*/
void Test_Position_Servomoteurs_Reset(void){
	SERVO_reset();
	printf("Les servomoteurs doivent être en position reset en position en x=115 et en y=115",SERVO_get_position_axe_x(),SERVO_get_position_axe_y);
}
/**
 *
  * @fn Test_Position_Servomoteurs_saut_positif()
  * @brief  Permets de vérifier la position des servomoteurs après un saut positif
*/
void Test_Position_Servomoteurs_saut_posif(void){
	SERVO_reset();
	SERVO_set_position_axe_x(SERVO_get_position_axe_x(), 5, true);
	SERVO_set_position_axe_y(SERVO_get_position_axe_y(), 5, true);
	printf("Les servomoteur doivent être en position reset plus un saut positif ainsi les servomoteurs doivent être en position en x=120 et en y=120",SERVO_get_position_axe_x(),SERVO_get_position_axe_y);
}

/**
 *
  * @fn Test_Position_Servomoteurs_saut_negatif()
  * @brief  Permets de vérifier la position des servomoteurs après un saut negatif
*/
void Test_Position_Servomoteurs_saut_negatif(void){
	SERVO_reset();
		SERVO_set_position_axe_x(SERVO_get_position_axe_x(), 5, false);
		SERVO_set_position_axe_y(SERVO_get_position_axe_y(), 5, false);
		printf("Les servomoteurs doit être en position reset plus un saut négatif ainsi les servomoteurs doivent être en position en x=110 et en y=110",SERVO_get_position_axe_x(),SERVO_get_position_axe_y);
}


/**
 *
  * @fn Test_Position_Max_Bordures_Servomoteurs()
  * @brief  Permets de vérifier la position des servomoteurs max après un saut positif
*/
void Test_Position_Max_Bordures_Servomoteurs(void){
	SERVO_set_position_axe_x(130, 0, true);
	SERVO_set_position_axe_y(130,0, true);

	SERVO_set_position_axe_x(130, 5, true);
	SERVO_set_position_axe_y(130, 5, true);
	printf("Les servomoteurs doit être en position max et rester en position max même avec un saut positif soit en position en x=130 et en y=130",SERVO_get_position_axe_x(),SERVO_get_position_axe_y);

}

/**
 *
  * @fn Test_Position_Min_Bordures_Servomoteurs()
  * @brief  Permets de vérifier la position des servomoteurs min après un saut negatif
*/
void Test_Position_Min_Bordures_Servomoteurs(void){
		SERVO_set_position_axe_x(105, 0, false);
		SERVO_set_position_axe_y(105,0, false);

		SERVO_set_position_axe_x(105, 5, false);
		SERVO_set_position_axe_y(105, 5, false);
		printf("Les servomoteurs doit être en position max et rester en position min même avec un saut négatif soit en position en x=105 et en y=105",SERVO_get_position_axe_x(),SERVO_get_position_axe_y);
}



