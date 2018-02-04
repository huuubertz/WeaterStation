#include "MKL46Z4.h"
#include "UART.h"
#include "slcd.h"
#include "bme280.h"
#include "i2c.h"

char text[]="ERROR";
char temp1[]="temperatura: ";
char temp[]=" oC";
char press1[]="cisnienie: ";
char press[]=" hPa";
char hum[]="wilgotnosc: ";
int number, c;
char znak[]={'\n','\r'};
char menu1[]="%%%% Witaj w pogodynce %%%%";
char menu[]="     Wpisz t, p lub h:";


int main(void){

	int temperature = 0;
	int pressure = 0;
	int humidity = 0;
	

UARTinitialize();
slcdInitialize();
initialize_i2c0();
initialize_bme280();
	
	for (c=0; c<27; c++) {	UART2_Transmit_Poll(menu1[c]);	}
	UART2_Transmit_Poll(znak[0]);
	UART2_Transmit_Poll(znak[1]);
	for (c=0; c<22; c++) {	UART2_Transmit_Poll(menu[c]);	}	
	UART2_Transmit_Poll(znak[0]);
	UART2_Transmit_Poll(znak[1]);
	UART2_Transmit_Poll(znak[0]);

while (1) {
	

number = UART2_Receive_Poll();


	temperature = get_bme280_temperature();
	pressure = get_bme280_pressure();
	humidity = get_bme280_humadity();


	
		
		switch(number){
			case 't':
			for (c=0; c<13; c++) {	UART2_Transmit_Poll(temp1[c]);	}
			dane(temperature);
			slcdDisplay(temperature,1);
			for (c=0; c<3; c++) {	UART2_Transmit_Poll(temp[c]);	}
			UART2_Transmit_Poll(znak[0]);
			UART2_Transmit_Poll(znak[1]);
			break;
			case 'p':
			for (c=0; c<11; c++) {	UART2_Transmit_Poll(press1[c]);	}
			dane(pressure);
			slcdDisplay(pressure,1);
			for (c=0; c<4; c++) {	UART2_Transmit_Poll(press[c]);	}
			UART2_Transmit_Poll(znak[0]);
			UART2_Transmit_Poll(znak[1]);
			break;
			case 'h':
			for (c=0; c<12; c++) {	UART2_Transmit_Poll(hum[c]);	}
			dane(humidity);
			slcdDisplay(humidity,1);
			UART2_Transmit_Poll('%');
			UART2_Transmit_Poll(znak[0]);
			UART2_Transmit_Poll(znak[1]);
			break;
			default:
			for (c=0; c<5; c++) {	UART2_Transmit_Poll(text[c]);	}
			UART2_Transmit_Poll(znak[0]);
			UART2_Transmit_Poll(znak[1]);
			slcdDisplay(1,1);
			break;
		
	}
	
	
	

	
	
}
}
