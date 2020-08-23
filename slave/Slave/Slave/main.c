/*
 * Slave.c
 *
 * Created: 8/17/2020 11:33:44 PM
 * Author : 20112
 */ 

#include "SPI.h"
#define F_CPU 16000000
#include <util/delay.h>
int main(void)
{
	uint8 data_1 =0;
	uint8 data_2 =0;
	DIO_SetPinDir(DIO_PORTC,DIO_PIN0,DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTC,DIO_PIN1,DIO_PIN_OUTPUT);
	SPI_Slave_Init();
	SPI_Start();
	_delay_ms(1000);
	while (1)
	{
		data_1 = SPI_Recieve_Byte();
		_delay_ms(1000);
		while (data_1 == '1')
		{
			SPI_Send_Byte(1);
			_delay_ms(1000);
		    data_2=SPI_Recieve_Byte();
			_delay_ms(1000);
			if (data_2 =='O')
			{
				
				DIO_WritePin(DIO_PORTC,DIO_PIN0,DIO_PIN_HIGH);
			}
		   else if(data_2 =='C')
			{
				DIO_WritePin(DIO_PORTC,DIO_PIN0,DIO_PIN_LOW);
			}
		}
			
		while (data_1 == '2')
		{
			SPI_Send_Byte(1);
			_delay_ms(1000);
			data_2=SPI_Recieve_Byte();
			_delay_ms(1000);
			if (data_2 =='O')
			{
				
				DIO_WritePin(DIO_PORTC,DIO_PIN1,DIO_PIN_HIGH);
			}
			else if(data_2 =='C')
			{
				DIO_WritePin(DIO_PORTC,DIO_PIN1,DIO_PIN_LOW);
			}
		}
			
		
	}
}
