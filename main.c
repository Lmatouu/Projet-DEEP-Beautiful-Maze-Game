/**
  ******************************************************************************
  * @file    main.c
  * @author  Mathis VEBER
  * @author  Martin FLEURY
  * @date    2022
  * @brief   Fonction principale par défaut [main]
  * version  2.0
  ******************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"

#include "detection_button.h"
#include "detection_capteur.h"
#include "servo.h"

/**
 *
  * @fn   writeLED(bool_e)
  * @brief  Permets de modifier l'etat de la LED de la bluePill
  * @param  b Si TRUE la LED s'allume sinon si FALSE la led s'éteint

*/

void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

/**
 *
  * @fn  uint16_t readButton()
  * @brief  Permet de lire l'etat du bouton de la carte nucleo
  * @return l'etat TRUE ou FALSE

*/
bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
}

static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}


/**
 *
  * @fn   int main()
  * @brief  Fonction principale en lecture continue appelant les differentes fonctions
  * @details Permets aussi l'initialisation des elements de la carte

*/
int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la première étape de la fonction main().
 	HAL_Init();

	//Initialisation de l'UART2 à la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reliées jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirigées vers la sonde de débogage, la liaison UART étant ensuite encapsulée sur l'USB vers le PC de développement.
 	//UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le périphérique UART2."
	//SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);


	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);


	//Initialisation des leds du rubans de leds port B0 et B1
	BSP_GPIO_PinCfg(GPIOB, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);
	BSP_GPIO_PinCfg(GPIOB, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms à la liste des fonctions appelées automatiquement chaque ms par la routine d'interruption du périphérique SYSTICK
	Systick_add_callback_function(&process_ms);

	// Initialise les servo-moteurs
	SERVO_init();
	//Initilisaton de l'état éteint de la led verte de la bluepill
	writeLED(TRUE);

	//Initilisaton de l'état éteint des deux rubans de LED
	writerubanLED(FALSE);
	writeruban2LED(FALSE);

	while(1)	//boucle de tâche de fond
	{
		button_id_e etat;
		etat=button_press_event(); // appelle fonction détection bouton
		uint16_t pas=2; // variable permettant de varier le bond entre la prochaine position
		bool_e saut; // variable permettant d'ajuster la sens du bond des servomoteurs (positif/négatif)

		switch(etat){

		case BUTTON_ID_LEFT:
				saut=TRUE;
				SERVO_set_position_axe_x(SERVO_get_position_axe_x(),pas,saut); //Positione le servomoteur à sa nouvelle position
				break;

		case BUTTON_ID_RIGHT:
							saut=FALSE;
							SERVO_set_position_axe_x(SERVO_get_position_axe_x(),pas,saut);//Positione le servomoteur à sa nouvelle position
						    break;


		case BUTTON_ID_UP:
							saut=FALSE;
							SERVO_set_position_axe_y(SERVO_get_position_axe_y(),pas,saut);//Positione le servomoteur à sa nouvelle position
							break;


		case BUTTON_ID_DOWN:
							saut=TRUE;
							SERVO_set_position_axe_y(SERVO_get_position_axe_y(),pas,saut);//Positione le servomoteur à sa nouvelle position
						    break;

		case BUTTON_ID_RESET:
				SERVO_reset();//Positione le servomoteur à sa position initiale
				writerubanLED(FALSE);//Eteint le premier ruban de LED
				writeruban2LED(FALSE);//Eteint le deuxième ruban de LED
				writeLED(TRUE);;//Eteint la LED NUCLEO
				break;

		default:
					break;

		}

		 capteur_detect_event(); // appelle fonction détection capteur






	}


}
