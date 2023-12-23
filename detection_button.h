/*
 * detection_button.h
 *
 *  Created on: 17 novembre 2022
 *      Author: Nirgal
 */

#ifndef detection_button_h
#define detection_button_h


typedef enum
			{
			BUTTON_ID_NONE =0,
			BUTTON_ID_LEFT,
			BUTTON_ID_RIGHT,
			BUTTON_ID_UP,
			BUTTON_ID_DOWN,
			BUTTON_ID_RESET,
			BUTTON_ID_NB
			// Le nombre de boutons dans la liste...
			}button_id_e;

button_id_e button_press_event(void);

#endif /* detection_button.h*/
