/*
 * Implementation
 * Sean Bapty
 * contains functions to set ADC memory based on IR input
 * works for each IR sensor
 */
//-----------------------------------------------------------------
// Name:	Coulston
// File:	lab7.c
// Date:	Fall 2014
// Purp:	Collect analog samples from P1.3 and P1.4
//-----------------------------------------------------------------
#include "lab7.h"

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
