ECE382_Lab7
===========
#Objectives
####Required

Use the ADC (analog to digital converter) subsystem to light LEDs based on the presence of a wall. The presence of a wall next to the left sensor should light LED1 on your Launchpad board. The presence of a wall next to the right sensor should light LED2 on your Launchpad board. Demonstrate that the LEDs do not light until they come into close proximity with a wall.

####B functionality

Create a standalone library for your ATD code and release it on Github. This should be separate from your lab code. It should have a thoughtful interface and README, capable of being reused in the robot maze laboratory.

####A functionality

Since each robot's sensors are a little bit different, you need to fully characterize the sensor for your robot. Create a table and graphical plot that shows the ATD values for a variety of distances from a maze wall. This table/graph must be generated for each IR sensor. Use these values to determine how the IR sensors work so you can properly use them to solve the maze.

#Preliminary Design/Prelab
##Hardware Schematic
Prior to thinking about how to implement LED software, it was necessary to think about how to hook up the hardware. From the class notes, any pin containing an A in the pin discription could be used as an input pin for IR signals. Because code was provided for A4 (P1.4) that pin was chosen. Additionally, pins A2 and A3 were selected to control the right and left sensors respectively because no other robot function currently uses these pins. Below is a schematic of the pin connections on the MSP430 to the robot IR ports. 

![alt tag](https://raw.githubusercontent.com/seanbapty/ECE382_Lab7/master/hardware%20schematic%20for%20IR%20sensors.jpg)

However, prior to wiring up these pins it was necessary to check their functionality. IR sensors work by emmiting a varying potential. As the sensor approaches a wall, it emits a higher potential. For these particular sensors, the signal should vary between 1 and 5 V. A multimeter was connected across the IR signal pin to determine if it functioned properly. Below is a 1 to 1 scale of the signal strength emitted by the sensors at varying distances. As is apparent, the sensors emmited the same magnitude signal at varying distances. This will need to be taken into account during software development.

![alt tag](https://raw.githubusercontent.com/seanbapty/ECE382_Lab7/master/IR%20distance%20scale.jpg)

##Software Design
Finally, a rough outline of how the required functionality software should operate was developed.

![alt tag](https://raw.githubusercontent.com/seanbapty/ECE382_Lab7/master/Pseudo%20code--required.jpg)

If there is a lot of quick varyation in the IR signal it may be useful to use the moving average function built in a homework assignment to control the interrupts rather than the instantaneous signal. 

#Code

Most of the work could be accomplished in a single main file. The repeating loop polls the IR sensors and calls the sensor functions if a ADC threshold potential is reached. Once the IR reading drops below the threshold voltage, the LED pin is set to 0.

```
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
```

##B Functionality
For B functionality, the IR functions needed to be assigned to their own library. Below is an independent library of the IR functions.
```
/*
 * Implementation
 * Sean Bapty
 * contains functions to set ADC memory based on IR input
 * works for each IR sensor
 */
#include "lab7.h"

unsigned int centerIR(){
	ADC10CTL0 &= ~ENC;								// clear ADC prior to changing
	ADC10CTL1 = INCH_4;								// center wired to pin 4
	ADC10AE0 |= BIT4;
	ADC10CTL0 |= ENC + ADC10SC;
	return ADC10MEM;								// returns ADC value to be compared to find distance
}

unsigned int leftIR(){
	ADC10CTL0 &= ~ENC;								// clear ADC prior to changing
	ADC10CTL1 = INCH_5;								// center wired to pin 5
	ADC10AE0 |= BIT5;								// originally 3 but pin 3 didn't work
	ADC10CTL0 |= ENC + ADC10SC;
	return ADC10MEM;
}

unsigned int rightIR(){
	ADC10CTL0 &= ~ENC;								// clear ADC prior to changing
	ADC10CTL1 = INCH_2;								// center wired to pin 2
	ADC10AE0 |= BIT2;
	ADC10CTL0 |= ENC + ADC10SC;
	return ADC10MEM;
}
```
#Debugging

The most powerful tool in debugging the IR sensors in a multimeter. In order to determine reasonable values, for the IR ADCs, the multimeter was plugged in and values at different distances were taken (see Prelab). 

The other hardware issue came from false readings of the IR sensor. This means that even when the IR shouldn't pick up a value above the threshold of 0x200 it did and the light wend on. This normally was not an issue as the sampling rate was fast enough that the light flash was not noticeable. This was mitigated by getting adequate blinders for the IR. The problem was not bad enough, but using a moving average function could help smooth out the signal. Furthermore, this could be mitigated by sampling at a slower rate thus decreasing the number of samples and the number of chances of getting a false reading.

#Testing methodology / results

It was not necessary to look at variables or registers when testing this code as its functionality was clearly apparent with the toggling of the light. To test the IR, a piece of paper was slowly moved toward the robor IR sensor directly in front of it, and then slowly moved away directly in front of it. See the Prelab for the scale of distances of when certain sensors where triggered. The result was a light on when a wall was close, and the light went off as the wall moved further away from the wall. This process was repeated for all 3 IR sensors.
#Observations and Conclusions

Although they are drastically different in voltage readings, all 3 IR sensors work. Going forward, it is important to scale the IR values to accomplish the task with the given IR sensor because of these differences. Other than that, there should be no problems using the IR sensors to accomplish a task.
####Documentation

C1C McPeek expalined how to use individual IR functions to return a value that denotes how close an object is.
