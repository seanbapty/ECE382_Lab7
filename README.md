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
