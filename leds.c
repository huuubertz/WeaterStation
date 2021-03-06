/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    leds.c
 *      Purpose: Microprocessors Laboratory
 *----------------------------------------------------------------------------
 *      
 *---------------------------------------------------------------------------*/

#include "leds.h"												//Declarations
#include "UART.h"

/*----------------------------------------------------------------------------
  Function that initializes LEDs
 *----------------------------------------------------------------------------*/
void ledsInitialize(void){
	
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK; /* Enable Clock to Port D & E */ 
	PORTD->PCR[5] = PORT_PCR_MUX(1UL);  /* Pin PTD5 is GPIO */
	PORTE->PCR[29] = PORT_PCR_MUX(1UL);  /* Pin PTE29 is GPIO */
	PTD->PDDR |= led_mask[ledGreen];  /* enable PTD5 as Output */
	PTE->PDDR |= led_mask[ledRed];  /* enable PTE29 as Output */
	
	PTD->PSOR = led_mask[ledGreen];  /* switch Green LED off */
	PTE->PSOR = led_mask[ledRed];  /* switch Red LED off */
}
/*----------------------------------------------------------------------------
  Function that blinks (x) times green led with (y) delay in mc
 *----------------------------------------------------------------------------*/
void ledgreenBlink(uint32_t x, uint32_t y){
	uint32_t count;
	
	for(count = 0; count < x; count++){	
		PTD->PCOR = led_mask[ledGreen];
		delay_mc(y);		
		PTD->PSOR = led_mask[ledGreen];
		delay_mc(y);
	}
}
/*----------------------------------------------------------------------------
  Function that blinks (x) times red led with (y) delay in mc
 *----------------------------------------------------------------------------*/
void ledredBlink(uint32_t x, uint32_t y){
	uint32_t count;
	
	for(count = 0; count < x; count++){	
		PTE->PCOR = led_mask[ledRed];
		delay_mc(y);		
		PTE->PSOR = led_mask[ledRed];
		delay_mc(y);	
	}
}
/*----------------------------------------------------------------------------
  Function that turns all LEDs off
 *----------------------------------------------------------------------------*/
void Greenled(void) {
		PTD->PSOR = led_mask[ledGreen];      /* switch Red LED off  */
	  PTE->PCOR = led_mask[ledRed];       /* switch Green LED on  */
}
/*----------------------------------------------------------------------------
  Function that turns all LEDs on
 *----------------------------------------------------------------------------*/
void Redled(void) {
		PTD->PCOR = led_mask[ledGreen];      	/* switch Red LED on  */
	  PTE->PSOR = led_mask[ledRed];     	/* switch Green LED off */
}









	
	int dane(int value){	
	int tab[4];
	int i = 0;

	for(i = 3; i>=0; i--){
		tab[i] = value % 10;
		tab[i]+=48;
		value /= 10;	
	}
	
	for(i=0; i < 4; i++){	
			
		UART2_Transmit_Poll(tab[i]);
	}
	
	
}