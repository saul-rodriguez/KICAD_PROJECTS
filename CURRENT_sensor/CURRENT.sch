EESchema Schematic File Version 2  date Tue 07 Aug 2012 09:51:17 PM CEST
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
LIBS:CURRENT-cache
EELAYER 25  0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "7 aug 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L PIC18F14K22_QFN U2
U 1 1 50202367
P 6050 3850
F 0 "U2" H 6050 3650 60  0000 C CNN
F 1 "PIC18F14K22_QFN" H 6100 3750 60  0000 C CNN
F 2 "qfn-20" H 6100 3850 60  0000 C CNN
	1    6050 3850
	1    0    0    -1  
$EndComp
$Comp
L MCP1702 U3
U 1 1 502023C8
P 7900 2000
F 0 "U3" H 8350 2850 60  0000 C CNN
F 1 "MCP1702" H 8650 2750 60  0000 C CNN
F 2 "sot89" H 8650 2850 60  0000 C CNN
	1    7900 2000
	1    0    0    -1  
$EndComp
$Comp
L RN42 U1
U 1 1 50202469
P 2550 3950
F 0 "U1" H 2550 3850 60  0000 C CNN
F 1 "RN42" H 2550 3950 60  0000 C CNN
F 2 "RN42" H 2550 4050 60  0000 C CNN
	1    2550 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 5020257A
P 1250 5500
F 0 "#PWR3" H 1250 5500 30  0001 C CNN
F 1 "GND" H 1250 5430 30  0001 C CNN
	1    1250 5500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 5020259D
P 6150 2450
F 0 "#PWR6" H 6150 2450 30  0001 C CNN
F 1 "GND" H 6150 2380 30  0001 C CNN
	1    6150 2450
	-1   0    0    1   
$EndComp
$Comp
L LED D1
U 1 1 50202765
P 6050 6350
F 0 "D1" H 6050 6450 50  0000 C CNN
F 1 "LED" H 6050 6250 50  0000 C CNN
F 2 "LED-1206" H 6050 6350 50  0000 C CNN
	1    6050 6350
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 50202786
P 6050 5750
F 0 "R2" V 6130 5750 50  0000 C CNN
F 1 "1K" V 6050 5750 50  0000 C CNN
F 2 "SM0603" V 6150 5750 50  0000 C CNN
	1    6050 5750
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR7
U 1 1 502027FB
P 6400 6550
F 0 "#PWR7" H 6400 6650 30  0001 C CNN
F 1 "VDD" H 6400 6660 30  0000 C CNN
	1    6400 6550
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR20
U 1 1 50202942
P 9850 1250
F 0 "#PWR20" H 9850 1350 30  0001 C CNN
F 1 "VDD" H 9850 1360 30  0000 C CNN
	1    9850 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR16
U 1 1 502029EA
P 8600 2100
F 0 "#PWR16" H 8600 2100 30  0001 C CNN
F 1 "GND" H 8600 2030 30  0001 C CNN
	1    8600 2100
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 50202A96
P 9300 1700
F 0 "C3" H 9350 1800 50  0000 L CNN
F 1 "10u" H 9350 1600 50  0000 L CNN
F 2 "SM1206" H 9350 1700 50  0000 C CNN
	1    9300 1700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR17
U 1 1 50202AA3
P 9300 2100
F 0 "#PWR17" H 9300 2100 30  0001 C CNN
F 1 "GND" H 9300 2030 30  0001 C CNN
	1    9300 2100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR11
U 1 1 50202AE9
P 7750 2100
F 0 "#PWR11" H 7750 2100 30  0001 C CNN
F 1 "GND" H 7750 2030 30  0001 C CNN
	1    7750 2100
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR5
U 1 1 50202B77
P 6050 2600
F 0 "#PWR5" H 6050 2700 30  0001 C CNN
F 1 "VDD" H 6050 2710 30  0000 C CNN
	1    6050 2600
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR1
U 1 1 50202EB6
P 1050 4200
F 0 "#PWR1" H 1050 4300 30  0001 C CNN
F 1 "VDD" H 1050 4310 30  0000 C CNN
	1    1050 4200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5020307C
P 4200 2350
F 0 "R1" V 4280 2350 50  0000 C CNN
F 1 "1K" V 4200 2350 50  0000 C CNN
F 2 "SM0603" V 4300 2350 50  0000 C CNN
	1    4200 2350
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P1
U 1 1 502030AB
P 4550 2800
F 0 "P1" V 4500 2800 40  0000 C CNN
F 1 "CONN_2" V 4600 2800 40  0000 C CNN
F 2 "pin_strip_2" V 4700 2800 40  0000 C CNN
	1    4550 2800
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR4
U 1 1 50203109
P 4200 2000
F 0 "#PWR4" H 4200 2100 30  0001 C CNN
F 1 "VDD" H 4200 2110 30  0000 C CNN
	1    4200 2000
	1    0    0    -1  
$EndComp
Text Notes 4400 2500 0    60   ~ 0
FACTORY\nRESET
$Comp
L GND #PWR9
U 1 1 5020328D
P 7400 1550
F 0 "#PWR9" H 7400 1550 30  0001 C CNN
F 1 "GND" H 7400 1480 30  0001 C CNN
	1    7400 1550
	1    0    0    -1  
$EndComp
$Comp
L CONN_6 P3
U 1 1 5020352D
P 9300 3300
F 0 "P3" V 9250 3300 60  0000 C CNN
F 1 "CONN_6" V 9350 3300 60  0000 C CNN
F 2 "pin_strip_6-90" V 9450 3300 60  0000 C CNN
	1    9300 3300
	1    0    0    -1  
$EndComp
Text Label 8650 3050 0    60   ~ 0
MCLR
Text Label 4600 3650 0    60   ~ 0
MCLR
Text Label 7300 3650 0    60   ~ 0
PGC
$Comp
L VDD #PWR14
U 1 1 50203731
P 8450 3150
F 0 "#PWR14" H 8450 3250 30  0001 C CNN
F 1 "VDD" H 8450 3260 30  0000 C CNN
	1    8450 3150
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR15
U 1 1 5020379B
P 8450 3250
F 0 "#PWR15" H 8450 3250 30  0001 C CNN
F 1 "GND" H 8450 3180 30  0001 C CNN
	1    8450 3250
	0    1    1    0   
$EndComp
Text Label 8650 3450 0    60   ~ 0
PGC
Text Label 6250 2700 1    60   ~ 0
PGD
Text Label 8650 3350 0    60   ~ 0
PGD
NoConn ~ 8950 3550
$Comp
L EQ730L U4
U 1 1 50210495
P 8950 5300
F 0 "U4" H 8950 5400 60  0000 C CNN
F 1 "EQ730L" H 8950 5500 60  0000 C CNN
F 2 "EQ730L" H 8950 5600 60  0000 C CNN
	1    8950 5300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR13
U 1 1 502104DF
P 8000 5150
F 0 "#PWR13" H 8000 5150 30  0001 C CNN
F 1 "GND" H 8000 5080 30  0001 C CNN
	1    8000 5150
	0    1    1    0   
$EndComp
$Comp
L VDD #PWR12
U 1 1 5021054F
P 8000 5050
F 0 "#PWR12" H 8000 5150 30  0001 C CNN
F 1 "VDD" H 8000 5160 30  0000 C CNN
	1    8000 5050
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 50210F5E
P 9750 1700
F 0 "C4" H 9800 1800 50  0000 L CNN
F 1 "0.1u" H 9800 1600 50  0000 L CNN
F 2 "SM0603" H 9800 1700 50  0000 C CNN
	1    9750 1700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR19
U 1 1 50210F9E
P 9750 2100
F 0 "#PWR19" H 9750 2100 30  0001 C CNN
F 1 "GND" H 9750 2030 30  0001 C CNN
	1    9750 2100
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5021114A
P 7750 1700
F 0 "C2" H 7800 1800 50  0000 L CNN
F 1 "1u" H 7800 1600 50  0000 L CNN
F 2 "SM0603_Capa" H 7800 1700 50  0000 C CNN
	1    7750 1700
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 50211153
P 1050 4600
F 0 "C1" H 1100 4700 50  0000 L CNN
F 1 "1u" H 1100 4500 50  0000 L CNN
F 2 "SM0603_Capa" H 1100 4600 50  0000 C CNN
	1    1050 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 5021129B
P 1050 4900
F 0 "#PWR2" H 1050 4900 30  0001 C CNN
F 1 "GND" H 1050 4830 30  0001 C CNN
	1    1050 4900
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P4
U 1 1 50211640
P 10650 1450
F 0 "P4" V 10600 1450 40  0000 C CNN
F 1 "CONN_2" V 10700 1450 40  0000 C CNN
F 2 "pin_strip_2" V 10800 1450 40  0000 C CNN
	1    10650 1450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR21
U 1 1 50211646
P 10250 2100
F 0 "#PWR21" H 10250 2100 30  0001 C CNN
F 1 "GND" H 10250 2030 30  0001 C CNN
	1    10250 2100
	-1   0    0    -1  
$EndComp
Text Label 7400 3850 0    60   ~ 0
CTRL
$Comp
L CONN_3 K1
U 1 1 50211A83
P 6500 1450
F 0 "K1" V 6450 1450 50  0000 C CNN
F 1 "CONN_3" V 6550 1450 40  0000 C CNN
F 2 "pin_strip_3" V 6650 1450 40  0000 C CNN
	1    6500 1450
	-1   0    0    -1  
$EndComp
$Comp
L PBUTTON S1
U 1 1 50211D5E
P 8000 5100
F 0 "S1" H 8600 6250 60  0000 C CNN
F 1 "PBUTTON" H 8750 6000 60  0000 C CNN
F 2 "PCB_PUSH_bottom" H 8750 6100 60  0000 C CNN
	1    8000 5100
	1    0    0    -1  
$EndComp
NoConn ~ 8200 4300
NoConn ~ 9300 4300
$Comp
L GND #PWR18
U 1 1 50211D6B
P 9400 4150
F 0 "#PWR18" H 9400 4150 30  0001 C CNN
F 1 "GND" H 9400 4080 30  0001 C CNN
	1    9400 4150
	1    0    0    -1  
$EndComp
Text Notes 8000 3850 0    60   ~ 0
BUTTON AT\nINT2 
$Comp
L CONN_1 P5
U 1 1 502124BF
P 1950 1650
F 0 "P5" H 2030 1650 40  0000 L CNN
F 1 "CONN_1" H 1950 1705 30  0001 C CNN
F 2 "Mhole" H 1950 1805 30  0000 C CNN
	1    1950 1650
	1    0    0    -1  
$EndComp
NoConn ~ 1800 1650
$Comp
L CONN_1 P2
U 1 1 502124D2
P 1950 1350
F 0 "P2" H 2030 1350 40  0000 L CNN
F 1 "CONN_1" H 1950 1405 30  0001 C CNN
F 2 "Mhole" H 1950 1505 30  0000 C CNN
	1    1950 1350
	1    0    0    -1  
$EndComp
NoConn ~ 1800 1350
$Comp
L CONN_1 P7
U 1 1 502124D9
P 2350 1650
F 0 "P7" H 2430 1650 40  0000 L CNN
F 1 "CONN_1" H 2350 1705 30  0001 C CNN
F 2 "Mhole" H 2350 1805 30  0000 C CNN
	1    2350 1650
	1    0    0    -1  
$EndComp
NoConn ~ 2200 1650
$Comp
L CONN_1 P6
U 1 1 502124E0
P 2350 1350
F 0 "P6" H 2430 1350 40  0000 L CNN
F 1 "CONN_1" H 2350 1405 30  0001 C CNN
F 2 "Mhole" H 2350 1505 30  0000 C CNN
	1    2350 1350
	1    0    0    -1  
$EndComp
NoConn ~ 2200 1350
$Comp
L NFET U5
U 1 1 5021700D
P 6950 2850
F 0 "U5" H 7150 3200 60  0000 C CNN
F 1 "NFET" H 7200 3450 60  0000 C CNN
	1    6950 2850
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 502170B6
P 7000 2950
F 0 "#PWR8" H 7000 2950 30  0001 C CNN
F 1 "GND" H 7000 2880 30  0001 C CNN
	1    7000 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 4100 3800 4100
Wire Wire Line
	3800 4100 3800 4200
Wire Wire Line
	3800 4200 3650 4200
Wire Wire Line
	1250 4400 1550 4400
Wire Wire Line
	1250 3300 1250 5500
Wire Wire Line
	1250 5400 2800 5400
Wire Wire Line
	2800 5400 2800 5100
Wire Wire Line
	1250 3300 1550 3300
Connection ~ 1250 4400
Connection ~ 1250 5400
Wire Wire Line
	6150 2800 6150 2450
Wire Wire Line
	4200 3500 3650 3500
Wire Wire Line
	6050 5000 6050 5500
Wire Wire Line
	6050 6000 6050 6150
Wire Wire Line
	6050 6550 6400 6550
Wire Wire Line
	3650 4300 4600 4300
Wire Wire Line
	4600 4300 4600 5250
Wire Wire Line
	4600 5250 6150 5250
Wire Wire Line
	6150 5250 6150 5000
Wire Wire Line
	5950 5000 5950 5150
Wire Wire Line
	5950 5150 4700 5150
Wire Wire Line
	4700 5150 4700 4400
Wire Wire Line
	4700 4400 3650 4400
Wire Wire Line
	9200 1350 10300 1350
Wire Wire Line
	8600 1950 8600 2100
Wire Wire Line
	9300 1500 9300 1350
Connection ~ 9300 1350
Wire Wire Line
	9300 1900 9300 2100
Wire Wire Line
	7750 2100 7750 1900
Wire Wire Line
	7750 1350 7750 1500
Wire Wire Line
	6850 1350 7950 1350
Connection ~ 7750 1350
Wire Wire Line
	6050 2600 6050 2800
Wire Wire Line
	6250 5000 6250 5250
Wire Wire Line
	6250 5250 8200 5250
Wire Wire Line
	1050 4300 1550 4300
Wire Wire Line
	4200 2900 4200 3500
Wire Wire Line
	4200 2600 4200 2700
Wire Wire Line
	4200 2000 4200 2100
Wire Wire Line
	8950 3050 8450 3050
Wire Wire Line
	4900 3650 4500 3650
Wire Wire Line
	7250 3650 7600 3650
Wire Wire Line
	8950 3150 8450 3150
Wire Wire Line
	8950 3250 8450 3250
Wire Wire Line
	8950 3450 8450 3450
Wire Wire Line
	8950 3350 8450 3350
Wire Wire Line
	6250 2800 6250 2450
Wire Wire Line
	8200 5150 8000 5150
Wire Wire Line
	8200 5050 8000 5050
Wire Wire Line
	9750 1500 9750 1350
Connection ~ 9750 1350
Wire Wire Line
	9750 1900 9750 2100
Wire Wire Line
	2300 5100 2300 5400
Connection ~ 2300 5400
Wire Wire Line
	1050 4200 1050 4400
Connection ~ 1050 4300
Wire Wire Line
	1050 4800 1050 4900
Wire Wire Line
	10250 1550 10250 2100
Wire Wire Line
	10250 1550 10300 1550
Connection ~ 9850 1350
Wire Wire Line
	9850 1250 9850 1350
Wire Wire Line
	7250 3850 7900 3850
Wire Wire Line
	7400 1550 7400 1450
Wire Wire Line
	7400 1450 6850 1450
Wire Wire Line
	7250 3750 7950 3750
Wire Wire Line
	7950 3750 7950 4100
Wire Wire Line
	7950 4100 8200 4100
Wire Wire Line
	9300 4100 9400 4100
Wire Wire Line
	9400 4100 9400 4150
Wire Wire Line
	6850 1550 7000 1550
Wire Wire Line
	7000 1550 7000 1950
Wire Wire Line
	7000 2850 7000 2950
$Comp
L R R3
U 1 1 50217262
P 7700 2800
F 0 "R3" V 7780 2800 50  0000 C CNN
F 1 "2.5K" V 7700 2800 50  0000 C CNN
F 2 "SM0603" V 7800 2800 50  0000 C CNN
	1    7700 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 50217268
P 7700 3200
F 0 "#PWR10" H 7700 3200 30  0001 C CNN
F 1 "GND" H 7700 3130 30  0001 C CNN
	1    7700 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3050 7700 3200
Wire Wire Line
	7700 2550 7700 2400
Wire Wire Line
	7600 2400 7900 2400
Wire Wire Line
	7900 2400 7900 3850
Connection ~ 7700 2400
$EndSCHEMATC
