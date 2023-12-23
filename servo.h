/*
 * servo.h
 *
 *  Created on: 19 sept. 2022
 *      Author: gomezher
 */

#ifndef BSP_SERVO_H_
#define BSP_SERVO_H_

#include <stdint.h>
#include "macro_types.h"

void SERVO_process_test(void);
void SERVO_init(void);
void SERVO_set_position_axe_x(uint16_t position, uint16_t pas, bool_e saut);
void SERVO_set_position_axe_y(uint16_t position, uint16_t pas, bool_e saut);
void SERVO_reset(void);
uint16_t SERVO_get_position_axe_x(void);
uint16_t SERVO_get_position_axe_y(void);


#endif /* BSP_SERVO_H_ */
