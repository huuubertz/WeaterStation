
#include "UART.h"

#define BUS_CLOCK 24000000
#define baud_rate 9600
#define UART2_IRQn 14


void UARTinitialize(){
	
	uint32_t divisor;
	
	// enable clock to UART2 and Port E
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	// connect UART to pins for PTE16, PTE17
	PORTE->PCR[17] |= PORT_PCR_MUX(3);    //RX
	PORTE->PCR[16] |= PORT_PCR_MUX(3);		//TX
	
	UART2->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);			//zablokowac nadajnik i odbiornik przed konfiguracja
	
	
	// Set baud rate to 4800 baud
	divisor = BUS_CLOCK/(baud_rate*16);
	UART2->BDH = UART_BDH_SBR(divisor>>8);
	UART2->BDL = UART_BDL_SBR(divisor);

						//       BR= BusClock/16*SBR				SBR=BusClock/16*BR				SBR=24MHz/16*9600=156.25			1001 1100 = 156   

	//No parity, 8 bits, two stop bits, other settings;
	UART2->C1 = UART2->S2 = UART2->C3 = 0;
	
	
	
	//UART2->BDH &= ~UART_BDH_SBNS_MASK;				//Stop Bit Number Select			0 - One stop bit
	//UART2->C1 &= ~(UART_C1_M_MASK | UART_C1_PE_MASK);				//M:  8-Bit Mode Select
																														//PE: Parity Disable
	

	
	UART2->C2 = UART_C2_TE_MASK | UART_C2_RE_MASK;			//wlaczyc nadajnik i odbiornik
	
	
}


void UART2_Transmit_Poll(uint8_t data) {
// wait until transmit data register is empty
while (!(UART2->S1 & UART_S1_TDRE_MASK));
UART2->D = data;
}


uint8_t UART2_Receive_Poll(void) {
// wait until receive data register is full
while (!(UART2->S1 & UART_S1_RDRF_MASK));
return UART2->D;
}


int dane(int value){	
	int tab[4];
	int i = 0;

	for(i = 3; i>=0; i--){
		tab[i] = value % 10;
		tab[i]+=48;		//zeby bylo ascii
		value /= 10;	
	}
	
	for(i=0; i < 4; i++){		
		UART2_Transmit_Poll(tab[i]);
	}
	
}