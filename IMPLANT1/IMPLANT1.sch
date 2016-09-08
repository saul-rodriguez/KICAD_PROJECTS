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
EELAYER 24 0
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
L INDUCTOR L1
U 1 1 52FA1DC9
P 4100 2900
F 0 "L1" V 4050 2900 40  0000 C CNN
F 1 "INDUCTOR" V 4200 2900 40  0000 C CNN
F 2 "" H 4100 2900 60  0000 C CNN
F 3 "" H 4100 2900 60  0000 C CNN
	1    4100 2900
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 52FA1DEE
P 4650 2750
F 0 "C1" H 4650 2850 40  0000 L CNN
F 1 "C" H 4656 2665 40  0000 L CNN
F 2 "" H 4688 2600 30  0000 C CNN
F 3 "" H 4650 2750 60  0000 C CNN
	1    4650 2750
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 52FA1DFB
P 4650 3300
F 0 "C2" H 4650 3400 40  0000 L CNN
F 1 "C" H 4656 3215 40  0000 L CNN
F 2 "" H 4688 3150 30  0000 C CNN
F 3 "" H 4650 3300 60  0000 C CNN
	1    4650 3300
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 52FA1E01
P 5150 2950
F 0 "C3" H 5150 3050 40  0000 L CNN
F 1 "C" H 5156 2865 40  0000 L CNN
F 2 "" H 5188 2800 30  0000 C CNN
F 3 "" H 5150 2950 60  0000 C CNN
	1    5150 2950
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 52FA1EB0
P 7400 2750
F 0 "D2" H 7400 2850 50  0000 C CNN
F 1 "LED" H 7400 2650 50  0000 C CNN
F 2 "" H 7400 2750 60  0000 C CNN
F 3 "" H 7400 2750 60  0000 C CNN
	1    7400 2750
	0    1    1    0   
$EndComp
$Comp
L LED D3
U 1 1 52FA1EBD
P 7400 3300
F 0 "D3" H 7400 3400 50  0000 C CNN
F 1 "LED" H 7400 3200 50  0000 C CNN
F 2 "" H 7400 3300 60  0000 C CNN
F 3 "" H 7400 3300 60  0000 C CNN
	1    7400 3300
	0    1    1    0   
$EndComp
$Comp
L C C5
U 1 1 52FA1F38
P 8100 3000
F 0 "C5" H 8100 3100 40  0000 L CNN
F 1 "C" H 8106 2915 40  0000 L CNN
F 2 "" H 8138 2850 30  0000 C CNN
F 3 "" H 8100 3000 60  0000 C CNN
	1    8100 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 52FA2013
P 7900 3750
F 0 "#PWR01" H 7900 3750 30  0001 C CNN
F 1 "GND" H 7900 3680 30  0001 C CNN
F 2 "" H 7900 3750 60  0000 C CNN
F 3 "" H 7900 3750 60  0000 C CNN
	1    7900 3750
	1    0    0    -1  
$EndComp
Text Label 8200 2400 0    60   ~ 0
VREC
Text Label 5450 1250 0    60   ~ 0
VREC
Text Label 5450 1350 0    60   ~ 0
GND
$Comp
L CONN_4 P1
U 1 1 52FA224C
P 5000 1400
F 0 "P1" V 4950 1400 50  0000 C CNN
F 1 "CONN_4" V 5050 1400 50  0000 C CNN
F 2 "" H 5000 1400 60  0000 C CNN
F 3 "" H 5000 1400 60  0000 C CNN
	1    5000 1400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4100 2600 4100 2400
Wire Wire Line
	4100 2400 5950 2400
Wire Wire Line
	4100 3200 4100 3650
Wire Wire Line
	4650 3500 4650 3650
Connection ~ 4650 3650
Wire Wire Line
	4650 2400 4650 2550
Connection ~ 4650 2400
Wire Wire Line
	4650 2950 4650 3100
Wire Wire Line
	5150 2750 5150 2400
Connection ~ 5150 2400
Wire Wire Line
	5150 3650 5150 3150
Connection ~ 5150 3650
Wire Wire Line
	7400 2550 7400 2400
Wire Wire Line
	7400 2950 7400 3100
Wire Wire Line
	7400 3650 7400 3500
Connection ~ 7400 3650
Wire Wire Line
	8100 2800 8100 2400
Wire Wire Line
	8100 3650 8100 3200
Connection ~ 4650 3050
Wire Wire Line
	7900 3650 7900 3750
Connection ~ 7900 3650
Wire Wire Line
	8000 2400 8450 2400
Wire Wire Line
	4100 3650 8100 3650
Connection ~ 8100 2400
Wire Wire Line
	4650 3050 5000 3050
Wire Wire Line
	5350 1250 5700 1250
Wire Wire Line
	5350 1350 5700 1350
Wire Wire Line
	5350 1450 5700 1450
Wire Wire Line
	5350 1550 5700 1550
Wire Wire Line
	6650 3550 6650 3650
Connection ~ 6650 3650
Wire Wire Line
	6650 2650 6650 2400
Wire Wire Line
	6050 3100 5750 3100
Text Label 4750 3050 0    60   ~ 0
RX
Text Label 5450 1450 0    60   ~ 0
RX
Text Label 5450 1550 0    60   ~ 0
TX
Text Label 5800 3100 0    60   ~ 0
TX
$Comp
L BAV99W U2
U 1 1 52FA3321
P 7050 1900
F 0 "U2" H 7050 2100 60  0000 C CNN
F 1 "BAV99W" H 7050 2200 60  0000 C CNN
F 2 "" H 7050 1900 60  0000 C CNN
F 3 "" H 7050 1900 60  0000 C CNN
	1    7050 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 2400 5950 1900
Wire Wire Line
	5950 1900 6450 1900
Wire Wire Line
	7650 1900 8000 1900
Wire Wire Line
	8000 1900 8000 2400
Wire Wire Line
	6650 2400 7400 2400
Wire Wire Line
	7050 2350 7050 2400
Connection ~ 7050 2400
$Comp
L NFET_FDV301N U1
U 1 1 52FA35B1
P 6700 3550
F 0 "U1" H 6900 3900 60  0000 C CNN
F 1 "NFET_FDV301N" H 6950 4150 60  0000 C CNN
F 2 "" H 6700 3550 60  0000 C CNN
F 3 "" H 6700 3550 60  0000 C CNN
	1    6700 3550
	1    0    0    -1  
$EndComp
$EndSCHEMATC