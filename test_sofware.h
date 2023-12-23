/*
 * test_sofware.h
 *
 *  Created on: 16 dec. 2023
 *      Author: vebermat
 */

#ifndef Test_SERVO_H_
#define Test_SERVO_H_

#include <stdint.h>
#include "macro_types.h"
#include "servo.h"
#include "config.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "detection_button.h"
#include "detection_capteur.h"


void Test_Position_Servomoteurs_Reset(void);
void Test_Position_Servomoteurs_saut_posif(void);
void Test_Position_Servomoteurs_saut_negatif(void);
void Test_Position_Max_Bordures_Servomoteurs(void);
void Test_Position_Min_Bordures_Servomoteurs(void);

#endif /* Test_SERVO_H_ */
