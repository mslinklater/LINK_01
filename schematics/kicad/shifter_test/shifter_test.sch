EESchema Schematic File Version 4
EELAYER 30 0
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
L FizzyChicken:SN74F299 U?
U 1 1 606864C4
P 5350 4150
F 0 "U?" H 5350 4825 50  0000 C CNN
F 1 "SN74F299" H 5350 4734 50  0000 C CNN
F 2 "" H 5350 4150 50  0001 C CNN
F 3 "" H 5350 4150 50  0001 C CNN
	1    5350 4150
	1    0    0    -1  
$EndComp
$Comp
L FizzyChicken:SN74F299 U?
U 1 1 60694C13
P 5350 2550
F 0 "U?" H 5350 3225 50  0000 C CNN
F 1 "SN74F299" H 5350 3134 50  0000 C CNN
F 2 "" H 5350 2550 50  0001 C CNN
F 3 "" H 5350 2550 50  0001 C CNN
	1    5350 2550
	1    0    0    -1  
$EndComp
$Comp
L FizzyChicken:SN74F299 U?
U 1 1 6069D545
P 5350 5800
F 0 "U?" H 5350 6475 50  0000 C CNN
F 1 "SN74F299" H 5350 6384 50  0000 C CNN
F 2 "" H 5350 5800 50  0001 C CNN
F 3 "" H 5350 5800 50  0001 C CNN
	1    5350 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 5650 6300 5650
Wire Wire Line
	6300 5650 6300 4600
Wire Wire Line
	6300 4600 5750 4600
Wire Wire Line
	5750 4000 6300 4000
Wire Wire Line
	6300 4000 6300 3000
Wire Wire Line
	6300 3000 5750 3000
Wire Wire Line
	4950 2900 4750 2900
Text Label 4750 2900 0    50   ~ 0
5V
Wire Wire Line
	4950 4500 4750 4500
Text Label 4750 4500 0    50   ~ 0
5V
Wire Wire Line
	4950 6150 4750 6150
Text Label 4750 6150 0    50   ~ 0
5V
Wire Wire Line
	5750 6150 5950 6150
Text Label 5950 6150 0    50   ~ 0
CLK
Wire Wire Line
	5750 4500 5950 4500
Text Label 5950 4500 0    50   ~ 0
CLK
Wire Wire Line
	5750 2900 5950 2900
Text Label 5950 2900 0    50   ~ 0
CLK
Wire Wire Line
	6200 3350 4550 3350
Wire Wire Line
	4550 3350 4550 2800
Wire Wire Line
	4550 2800 4950 2800
Wire Wire Line
	4950 4600 4750 4600
Text Label 4750 4600 0    50   ~ 0
GND
Wire Wire Line
	4950 3000 4750 3000
Text Label 4750 3000 0    50   ~ 0
GND
Wire Wire Line
	4950 6250 4750 6250
Text Label 4750 6250 0    50   ~ 0
GND
Wire Wire Line
	4950 4400 4550 4400
Wire Wire Line
	4550 4400 4550 4900
Wire Wire Line
	4550 4900 6200 4900
Wire Wire Line
	6200 4900 6200 5550
Wire Wire Line
	6200 5550 5750 5550
Wire Wire Line
	6200 3900 5750 3900
Wire Wire Line
	6200 3350 6200 3900
Wire Wire Line
	4950 5450 4750 5450
Text Label 4750 5450 0    50   ~ 0
OE
Wire Wire Line
	4950 5550 4750 5550
Text Label 4750 5550 0    50   ~ 0
OE
Wire Wire Line
	5750 6250 5950 6250
Text Label 5950 6250 0    50   ~ 0
SHIFT_IN
Wire Wire Line
	5750 2300 5950 2300
Text Label 5950 2300 0    50   ~ 0
SHIFT_IN
Wire Wire Line
	5750 2100 5950 2100
Text Label 5950 2100 0    50   ~ 0
5V
Wire Wire Line
	5750 3700 5950 3700
Text Label 5950 3700 0    50   ~ 0
5V
Wire Wire Line
	5750 5350 5950 5350
Text Label 5950 5350 0    50   ~ 0
5V
Wire Wire Line
	4950 3800 4750 3800
Text Label 4750 3800 0    50   ~ 0
OE
Wire Wire Line
	4950 3900 4750 3900
Text Label 4750 3900 0    50   ~ 0
OE
Wire Wire Line
	4950 2200 4750 2200
Text Label 4750 2200 0    50   ~ 0
OE
Wire Wire Line
	4950 2300 4750 2300
Text Label 4750 2300 0    50   ~ 0
OE
Text Label 7300 3150 0    50   ~ 0
INPUTS
Text Label 7300 3300 0    50   ~ 0
OE
Text Label 7300 3400 0    50   ~ 0
SHIFT_IN
Text Label 7300 3500 0    50   ~ 0
CLK
Wire Wire Line
	4950 2100 4750 2100
Text Label 4750 2100 0    50   ~ 0
S0
Wire Wire Line
	5750 2200 5950 2200
Text Label 5950 2200 0    50   ~ 0
S1
Text Label 7300 3600 0    50   ~ 0
S0
Text Label 7300 3700 0    50   ~ 0
S1
Wire Wire Line
	4950 3700 4750 3700
Text Label 4750 3700 0    50   ~ 0
S0
Wire Wire Line
	5750 3800 5950 3800
Text Label 5950 3800 0    50   ~ 0
S1
Wire Wire Line
	4950 5350 4750 5350
Text Label 4750 5350 0    50   ~ 0
S0
Wire Wire Line
	5750 5450 5950 5450
Text Label 5950 5450 0    50   ~ 0
S1
$EndSCHEMATC
