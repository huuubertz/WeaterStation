

#ifndef UART_H
#define UART_H

#include "MKL46Z4.h"


void UARTinitialize(void);
void UART2_Transmit_Poll(uint8_t data);
uint8_t UART2_Receive_Poll(void);
int dane (int value);

#endif
