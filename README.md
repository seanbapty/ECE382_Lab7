ECE382_Lab7
===========

#Prelab
Prior to thinking about how to implement LED software, it was necessary to think about how to hook up the hardware. From the class notes, any pin containing an A in the pin discription could be used as an input pin for IR signals. Because code was provided for A4 (P1.4) that pin was chosen. Additionally, pins A2 and A3 were selected to control the right and left sensors respectively because no other robot function currently uses these pins. Below is a schematic of the pin connections on the MSP430 to the robot IR ports. 

![alt tag](https://raw.githubusercontent.com/seanbapty/ECE382_Lab7/master/hardware%20schematic%20for%20IR%20sensors.jpg)

