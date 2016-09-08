EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:spice
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 0 #GND2
U 1 1 543EC424
P 2700 2350
F 0 "#GND2" H 2700 2250 60  0001 C CNN
F 1 "0" H 2700 2280 60  0000 C CNN
F 2 "" H 2700 2350 60  0000 C CNN
F 3 "" H 2700 2350 60  0000 C CNN
	1    2700 2350
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 543EC438
P 2700 2000
F 0 "C1" H 2700 2100 40  0000 L CNN
F 1 "1u" H 2706 1915 40  0000 L CNN
F 2 "" H 2738 1850 30  0000 C CNN
F 3 "" H 2700 2000 60  0000 C CNN
	1    2700 2000
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 543EC493
P 2050 1700
F 0 "R1" V 2130 1700 40  0000 C CNN
F 1 "1000" V 2057 1701 40  0000 C CNN
F 2 "" V 1980 1700 30  0000 C CNN
F 3 "" H 2050 1700 30  0000 C CNN
	1    2050 1700
	0    1    1    0   
$EndComp
$Comp
L VAC V1
U 1 1 543EC4F2
P 1400 2250
F 0 "V1" H 1400 2350 60  0000 C CNN
F 1 "dc 0V ac 1V" H 1400 2150 60  0000 C CNN
F 2 "" H 1400 2250 60  0000 C CNN
F 3 "" H 1400 2250 60  0000 C CNN
	1    1400 2250
	1    0    0    -1  
$EndComp
$Comp
L 0 #GND1
U 1 1 543EC5C5
P 1400 2850
F 0 "#GND1" H 1400 2750 60  0001 C CNN
F 1 "0" H 1400 2780 60  0000 C CNN
F 2 "" H 1400 2850 60  0000 C CNN
F 3 "" H 1400 2850 60  0000 C CNN
	1    1400 2850
	1    0    0    -1  
$EndComp
Text Notes 1750 3050 0    60   ~ 0
+PSPICE \n.control\nac dec 66 1kHz 120kHz \nplot vdb(OUT)\nset units = degrees\nplot vp(OUT)\n.endc
Wire Wire Line
	2300 1700 2900 1700
Wire Wire Line
	2700 1700 2700 1800
Wire Wire Line
	2700 2200 2700 2350
Wire Wire Line
	1400 2650 1400 2850
Connection ~ 2700 1700
Wire Wire Line
	1400 1850 1400 1700
Connection ~ 1400 1700
Text GLabel 1300 1700 0    60   Input ~ 0
IN
Text GLabel 2900 1700 2    60   Input ~ 0
OUT
Wire Wire Line
	1800 1700 1300 1700
$EndSCHEMATC
