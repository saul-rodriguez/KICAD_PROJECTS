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
LIBS:SAUL
LIBS:raspberry_common
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
L RASPBERRY_RV2 U1
U 1 1 547389F8
P 2900 2300
F 0 "U1" H 2900 2500 60  0000 C CNN
F 1 "RASPBERRY_RV2" H 2950 2350 60  0000 C CNN
F 2 "" H 2800 2000 60  0000 C CNN
F 3 "" H 2800 2000 60  0000 C CNN
	1    2900 2300
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 54738AAF
P 1150 3000
F 0 "D1" H 1150 3100 50  0000 C CNN
F 1 "LED" H 1150 2900 50  0000 C CNN
F 2 "" H 1150 3000 60  0000 C CNN
F 3 "" H 1150 3000 60  0000 C CNN
	1    1150 3000
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 54738B2C
P 1150 2450
F 0 "R1" V 1230 2450 40  0000 C CNN
F 1 "500" V 1157 2451 40  0000 C CNN
F 2 "" V 1080 2450 30  0000 C CNN
F 3 "" H 1150 2450 30  0000 C CNN
	1    1150 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 2200 1150 2200
Wire Wire Line
	1150 2700 1150 2800
$Comp
L GND #PWR1
U 1 1 54738CB9
P 1150 3300
F 0 "#PWR1" H 1150 3300 30  0001 C CNN
F 1 "GND" H 1150 3230 30  0001 C CNN
F 2 "" H 1150 3300 60  0000 C CNN
F 3 "" H 1150 3300 60  0000 C CNN
	1    1150 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 3200 1150 3300
$Comp
L GND #PWR?
U 1 1 54738DCD
P 1650 3050
F 0 "#PWR?" H 1650 3050 30  0001 C CNN
F 1 "GND" H 1650 2980 30  0001 C CNN
F 2 "" H 1650 3050 60  0000 C CNN
F 3 "" H 1650 3050 60  0000 C CNN
	1    1650 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 2900 1650 2900
Wire Wire Line
	1650 2900 1650 3050
$EndSCHEMATC
