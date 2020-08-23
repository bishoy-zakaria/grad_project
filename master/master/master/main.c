/*
 * master.c
 *
 * Created: 8/16/2020 7:41:05 PM
 * Author : 20112
 */ 

#include "LCD.h"
#include "UART.h"
#include "PASSWORD.h"
#include "SPI.h"
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	uint8 Temp=0;
	uint8 val=0;
	uint8 data_UART=0;
	uint8 data_SPI=0;
	LCD_Init();
	UART_Init();
	UART_Start();
	
	/* ************************ SLAVES ********************** */
	
	/*DIO_SetPinDir(DIO_PORTA,DIO_PIN0,DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTA,DIO_PIN1,DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTA,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTA,DIO_PIN3,DIO_PIN_OUTPUT);
	
	DIO_WritePin(DIO_PORTA,DIO_PIN0,DIO_PIN_HIGH );
	DIO_WritePin(DIO_PORTA,DIO_PIN1,DIO_PIN_HIGH );
	DIO_WritePin(DIO_PORTA,DIO_PIN2,DIO_PIN_HIGH );
	DIO_WritePin(DIO_PORTA,DIO_PIN3,DIO_PIN_HIGH );*/
	
	/* *********************** PASSWORD *********************** */
	
	TX_String("THE PASSWORD");
	Temp = RX_Byte();
	val=pass_check(Temp);
	
	if(val==1)
	{
		
		TX_String("Welcome Sir");
		LCD_WriteString("Welcome Sir");
		
	}
    while (val==1) 
    {
		
		    DIO_WritePin(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW ); //SS
		    SPI_Master_Init();
		    SPI_Start();
		    _delay_ms(1000);
			
			LCD_Clear();
			LCD_WriteString("LED1_Press:1");
			LCD_GoTo(1,0);
			LCD_WriteString("LED2_Press:2");
			data_UART = RX_Byte();
			SPI_Send_Byte(data_UART);
			_delay_ms(1000);
		    
				data_SPI=SPI_Recieve_Byte();
			    _delay_ms(1000);
				LCD_Clear();
		        LCD_WriteChar(data_UART);
				if(data_SPI==1)    //ACK
				{
					LCD_Clear();
					LCD_WriteString("LED_Open:0");
					LCD_GoTo(1,0);
					LCD_WriteString("LED_Close:C");
					TX_String("LED_Open:O , LED_Close:C");
					while(1)
					{
					data_UART = RX_Byte();
					_delay_ms(250);
					SPI_Send_Byte(data_UART);
					_delay_ms(1000);
					}
					
					
				}
				else 
				{
					LCD_Clear();
					LCD_WriteString("ERROR");
				}
			    
		    
	    }
	}



