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
LIBS:spice_ic
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 3350 2550 1350 1050
U 5511CF5A
F0 "inv1" 60
F1 "inv1.sch" 60
F2 "IN" I L 3350 3050 60 
F3 "OUT" O R 4700 3050 60 
F4 "VD" U L 3350 2750 60 
F5 "GD" U L 3350 3500 60 
$EndSheet
$Sheet
S 5350 2550 1350 1050
U 5511D9EB
F0 "inv2" 60
F1 "inv1.sch" 60
F2 "IN" I L 5350 3050 60 
F3 "OUT" O R 6700 3050 60 
F4 "VD" U L 5350 2750 60 
F5 "GD" U L 5350 3500 60 
$EndSheet
Wire Wire Line
	4700 3050 5350 3050
Wire Wire Line
	6700 3050 7600 3050
$Sheet
S 7600 2550 1350 1050
U 5511E210
F0 "inv3" 60
F1 "inv1.sch" 60
F2 "IN" I L 7600 3050 60 
F3 "OUT" O R 8950 3050 60 
F4 "VD" U L 7600 2750 60 
F5 "GD" U L 7600 3500 60 
$EndSheet
Wire Wire Line
	8950 3050 9800 3050
Wire Wire Line
	9800 3050 9800 2100
Wire Wire Line
	9800 2100 2400 2100
Wire Wire Line
	2400 2100 2400 3050
Wire Wire Line
	7600 2750 7300 2750
Wire Wire Line
	7300 2750 7300 1750
Wire Wire Line
	7300 1750 1850 1750
Wire Wire Line
	3000 1750 3000 2750
Wire Wire Line
	3000 2750 3350 2750
Wire Wire Line
	5350 2750 5050 2750
Wire Wire Line
	5050 2750 5050 1750
Connection ~ 5050 1750
Wire Wire Line
	7600 3500 7400 3500
Wire Wire Line
	7400 3500 7400 3900
Wire Wire Line
	7400 3900 3000 3900
Wire Wire Line
	3000 3900 3000 3500
Wire Wire Line
	3000 3500 3350 3500
Wire Wire Line
	5350 3500 5100 3500
Wire Wire Line
	5100 3500 5100 3900
Connection ~ 5100 3900
$Comp
L 0 #GND2
U 1 1 5511E8E8
P 4150 4100
F 0 "#GND2" H 4150 4000 60  0001 C CNN
F 1 "0" H 4150 4030 60  0000 C CNN
F 2 "" H 4150 4100 60  0000 C CNN
F 3 "" H 4150 4100 60  0000 C CNN
	1    4150 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 4100 4150 3900
Connection ~ 4150 3900
$Comp
L vdc V1
U 1 1 5511E9B6
P 1850 2000
F 0 "V1" H 2025 2075 60  0000 C CNN
F 1 "DC 1.8" H 2150 1950 60  0000 C CNN
F 2 "" H 2100 1850 60  0000 C CNN
F 3 "" H 2100 1850 60  0000 C CNN
	1    1850 2000
	1    0    0    -1  
$EndComp
Connection ~ 3000 1750
$Comp
L 0 #GND1
U 1 1 5511EA88
P 1850 2400
F 0 "#GND1" H 1850 2300 60  0001 C CNN
F 1 "0" H 1850 2330 60  0000 C CNN
F 2 "" H 1850 2400 60  0000 C CNN
F 3 "" H 1850 2400 60  0000 C CNN
	1    1850 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 2250 1850 2400
Text Notes 7900 4550 2    60   ~ 0
+PSPICE \n.include ./models/skew_tt.inc\n.include ./models/modelcard3.nmos\n.include ./models/modelcard3.pmos\n
Text Label 9250 3050 2    60   ~ 0
vout
Text GLabel 9800 3050 2    60   Input ~ 0
VOUT
Wire Wire Line
	2400 3050 2550 3050
$Comp
L vsin V2
U 1 1 5511FDB6
P 2800 3050
F 0 "V2" H 2975 3125 60  0000 C CNN
F 1 "AC 1" V 3000 2950 60  0000 C CNN
F 2 "" H 3050 2900 60  0000 C CNN
F 3 "" H 3050 2900 60  0000 C CNN
	1    2800 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 3050 3350 3050
$EndSCHEMATC
