#This is the HCIN720 IA2

##Introduction
This circuit used Proximity sensor to detect distance and then light up corresponding LEDs on Neopixel ring. The data is published to photon cloud for website visualization and then the photon subscribe the data for showing the results on the output circuit.

##Reading Data
Photon reads analog voltage output from Proximity sensor. There is a linear function for 1/distance and voltage.

![][distancefunction]

From the collected samples I computed the equation for computing distance by voltage:
distance=24063/(voltage-294)

##Visualization
I edited the [Progress Meter "Thermometer”](https://codepen.io/afterlight/pen/otHrL) to make a distance meter. This website script will read photon published data and display the meter graph. It’s a new visualization methods compared with IA1.

![][web]

##Output circuit
For data subscribed from photon cloud, the output circuit will light up corresponding LEDs on Neopixel ring. The closer the distance is, the more LEDs will be lighted up.  As the number of lighting LEDs increasing, the color of LEDs will become more red and when distance is close than 10cm, the LEDs will blink red and blue to show a alert.

![][output1]
![][output2]
![][output3]

————
[web]:https://github.com/Zhiyuan1991/HCIN720-IA2/raw/master/images/web.png
[distancefunction]:https://github.com/Zhiyuan1991/HCIN720-IA2/raw/master/images/distance_function.jpg
![][output1]:https://github.com/Zhiyuan1991/HCIN720-IA2/raw/master/images/close.JPG
![][output2]:https://github.com/Zhiyuan1991/HCIN720-IA2/raw/master/images/far.JPG
![][output3]:https://github.com/Zhiyuan1991/HCIN720-IA2/raw/master/images/alert.JPG
