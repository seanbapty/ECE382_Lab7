ECE382_Lab7
===========

#Prelab
Prior to thinking about how to implement LED software, it was necessary to think about how to hook up the hardware. From the class notes, any pin containing an A in the pin discription could be used as an input pin for IR signals. Because code was provided for A4 (P1.4) that pin was chosen. Additionally, pins A2 and A3 were selected to control the right and left sensors respectively because no other robot function currently uses these pins. Below is a schematic of the pin connections on the MSP430 to the robot IR ports. 

![alt tag](https://raw.githubusercontent.com/seanbapty/ECE382_Lab7/master/hardware%20schematic%20for%20IR%20sensors.jpg)

However, prior to wiring up these pins it was necessary to check their functionality. IR sensors work by emmiting a varying potential. As the sensor approaches a wall, it emits a higher potential. For these particular sensors, the signal should vary between 1 and 5 V. A multimeter was connected across the IR signal pin to determine if it functioned properly. Below is a 1 to 1 scale of the signal strength emitted by the sensors at varying distances. As is apparent, the sensors emmited the same magnitude signal at varying distances. This will need to be taken into account during software development.

![alt tag](https://raw.githubusercontent.com/seanbapty/ECE382_Lab7/master/IR%20distance%20scale.jpg)

Finally, a rough outline of how the required functionality software should operate was developed.

![alt tag](https://raw.githubusercontent.com/seanbapty/ECE382_Lab7/master/Pseudo%20code--required.jpg)
