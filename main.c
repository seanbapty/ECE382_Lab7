#include <msp430.h> 

/*
 * main.c
 * Sean Bapty
 * toggles LED 1 when proximity to a wall on the center is less than ~1.5 in.
 * toggles LED 2 when proximity to a wall on the right/left is less than ~1.5 in.
 */
//-----------------------------------------------------------------
// Name:	Coulston
// File:	lab7.c
// Date:	Fall 2014
// Purp:	Collect analog samples from P1.3 and P1.4
//-----------------------------------------------------------------
#include "msp430g2553.h"
#include "lab7.h"

#define RED_LED_ENABLE		P1DIR |= BIT0
#define ORANGE_LED_ENABLE	P1DIR |= BIT6

void initMSP430();

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {

	unsigned short sample[16];									// Just to analyze the values
	unsigned char i = 0;										// index into sample array

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;

	RED_LED_ENABLE;												// Set the red LED as output
	ORANGE_LED_ENABLE;											// Set orange to output

	ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE;
	ADC10CTL1 = ADC10DIV_7;
	ADC10CTL1 |= ADC10SSEL1 | ADC10SSEL0;

	while(1) {
		__delay_cycles(1000);
		centerIR();
		if (ADC10MEM > 0x200)
			P1OUT |= BIT0;
		else
			P1OUT &= ~BIT0;

		__delay_cycles(10000);
		rightIR();
		if (ADC10MEM > 0x200){
			P1OUT |= BIT6;

		}
		else{
			P1OUT &= ~BIT6;

		}

		__delay_cycles(10000);

		leftIR();
		if (ADC10MEM > 0x200)
			P1OUT |= BIT6;
		else
			P1OUT &= ~BIT6;

	} // end main
	return 0;
}
unsigned int centerIR(){
	ADC10CTL0 &= ~ENC;								// clear ADC prior to changing
	ADC10CTL1 = INCH_4;								// center wired to pin 4
	ADC10AE0 |= BIT4;
	ADC10CTL0 |= ENC + ADC10SC;
	return ADC10MEM;
}

unsigned int leftIR(){
	ADC10CTL0 &= ~ENC;								// clear ADC prior to changing
	ADC10CTL1 = INCH_5;								// center wired to pin 4
	ADC10AE0 |= BIT5;
	ADC10CTL0 |= ENC + ADC10SC;
	return ADC10MEM;
}

unsigned int rightIR(){
	ADC10CTL0 &= ~ENC;								// clear ADC prior to changing
	ADC10CTL1 = INCH_2;								// center wired to pin 4
	ADC10AE0 |= BIT2;
	ADC10CTL0 |= ENC + ADC10SC;
	return ADC10MEM;
}
