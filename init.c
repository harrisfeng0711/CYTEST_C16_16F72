//==============================================//
//		Include Header File						//
//==============================================//
#include "init.h"

//==============================================//
//			原型宣告							//
//==============================================//
void Init_System(void);
//void Init_Timer0(void);
void Init_Timer1 (void);
void Init_IO(void);
void Init_AD_Module (void);

//==============================================//
//		    INITIALIZE SYSTEM					//
//==============================================//
void Init_System(void)
{
	OPTION = 0b00001111;			// WDT 1:128
	
	Init_AD_Module();
	Init_IO();
	//Init_Timer1();

	PEIE = 1;						//
}

//==============================================//
//		   IO Initial							//
//==============================================//
void Init_IO(void)
{
	TRISA=0b11111111;				// Set PortA Input/Output
	PORTA=0b11111111;				// Initila PortA

	TRISB=0b00010000;				// Set PortB Input/Output
	PORTB=0b11010000;				// Initila PortB

	TRISC=0b11111111;				// Set PortC Input/Output
	PORTC=0b11111111;				// Initila PortC
}


//==============================================//
//		   Timer1 Initial						//
//==============================================//
void Init_Timer1 (void)
{
	T1CON = 0b00000000;				// 
	TMR1L = 0x38;					// 500ms 中斷
	TMR1H = 0xFF;
	TMR1IE = 1;						// Timer1 Interrupt Enable
}


//==============================================//
//		   	AD Initial							//
//==============================================//

void Init_AD_Module (void)
{
	ADCON1 = 0b00000110; 			// Digital
}

