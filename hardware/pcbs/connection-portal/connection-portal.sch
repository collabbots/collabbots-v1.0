EESchema Schematic File Version 4
LIBS:connection-portal-cache
EELAYER 29 0
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
Text Notes 7300 7200 0    50   ~ 0
1
Text Notes 7400 7250 0    50   ~ 0
1
Text Notes 7350 7500 0    50   ~ 0
collabots-connection-portal v1.0
Text Notes 8150 7650 0    50   ~ 0
14 June 2019
Text Notes 10600 7650 0    50   ~ 0
A
$Comp
L Connector:Conn_01x15_Male J6
U 1 1 5D032CDB
P 7150 4250
F 0 "J6" H 7050 4350 50  0000 C CNN
F 1 "Servo-Connector" H 6750 4250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x15_P2.54mm_Horizontal" H 7150 4250 50  0001 C CNN
F 3 "~" H 7150 4250 50  0001 C CNN
	1    7150 4250
	-1   0    0    1   
$EndComp
$Comp
L Connector:Screw_Terminal_01x06 J3
U 1 1 5D053193
P 3850 4450
F 0 "J3" H 3929 4350 50  0000 L CNN
F 1 "Servo PWM" H 3929 4441 50  0000 L CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type011_RT05506HBWC_1x06_P5.00mm_Horizontal" H 3850 4450 50  0001 C CNN
F 3 "~" H 3850 4450 50  0001 C CNN
	1    3850 4450
	-1   0    0    1   
$EndComp
$Comp
L Connector:Screw_Terminal_01x04 J2
U 1 1 5D053BA7
P 3850 3250
F 0 "J2" H 3930 3150 50  0000 L CNN
F 1 "Interrupt-In" H 3930 3241 50  0000 L CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type011_RT05504HBWC_1x04_P5.00mm_Horizontal" H 3850 3250 50  0001 C CNN
F 3 "~" H 3850 3250 50  0001 C CNN
	1    3850 3250
	-1   0    0    1   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5D055DF3
P 3850 3850
F 0 "J1" H 3768 3525 50  0000 C CNN
F 1 "Power" H 3768 3616 50  0000 C CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type011_RT05502HBWC_1x02_P5.00mm_Horizontal" H 3850 3850 50  0001 C CNN
F 3 "~" H 3850 3850 50  0001 C CNN
	1    3850 3850
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D3
U 1 1 5D056914
P 4750 4600
F 0 "D3" V 4789 4483 50  0000 R CNN
F 1 "LED" V 4698 4483 50  0000 R CNN
F 2 "LED_THT:LED_Rectangular_W3.9mm_H1.8mm_FlatTop" H 4750 4600 50  0001 C CNN
F 3 "~" H 4750 4600 50  0001 C CNN
	1    4750 4600
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D1
U 1 1 5D059FEB
P 4200 4800
F 0 "D1" V 4250 4750 50  0000 R CNN
F 1 "LED" V 4150 4750 50  0000 R CNN
F 2 "LED_THT:LED_Rectangular_W3.9mm_H1.8mm_FlatTop" H 4200 4800 50  0001 C CNN
F 3 "~" H 4200 4800 50  0001 C CNN
	1    4200 4800
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D2
U 1 1 5D05A8D0
P 4450 4700
F 0 "D2" V 4500 4600 50  0000 R CNN
F 1 "LED" V 4400 4600 50  0000 R CNN
F 2 "LED_THT:LED_Rectangular_W3.9mm_H1.8mm_FlatTop" H 4450 4700 50  0001 C CNN
F 3 "~" H 4450 4700 50  0001 C CNN
	1    4450 4700
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D4
U 1 1 5D05AE57
P 5050 4500
F 0 "D4" V 5089 4383 50  0000 R CNN
F 1 "LED" V 4998 4383 50  0000 R CNN
F 2 "LED_THT:LED_Rectangular_W3.9mm_H1.8mm_FlatTop" H 5050 4500 50  0001 C CNN
F 3 "~" H 5050 4500 50  0001 C CNN
	1    5050 4500
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D5
U 1 1 5D05B214
P 5350 4400
F 0 "D5" V 5389 4283 50  0000 R CNN
F 1 "LED" V 5298 4283 50  0000 R CNN
F 2 "LED_THT:LED_Rectangular_W3.9mm_H1.8mm_FlatTop" H 5350 4400 50  0001 C CNN
F 3 "~" H 5350 4400 50  0001 C CNN
	1    5350 4400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R4
U 1 1 5D05BA44
P 5050 4850
F 0 "R4" H 5120 4896 50  0000 L CNN
F 1 "500Ω" H 5120 4805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4980 4850 50  0001 C CNN
F 3 "~" H 5050 4850 50  0001 C CNN
	1    5050 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5D05C3A4
P 4750 5000
F 0 "R3" H 4820 5046 50  0000 L CNN
F 1 "500Ω" H 4820 4955 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4680 5000 50  0001 C CNN
F 3 "~" H 4750 5000 50  0001 C CNN
	1    4750 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D05C6D2
P 4450 5050
F 0 "R2" H 4500 5100 50  0000 L CNN
F 1 "500Ω" H 4500 5000 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4380 5050 50  0001 C CNN
F 3 "~" H 4450 5050 50  0001 C CNN
	1    4450 5050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5D05CB50
P 4200 5150
F 0 "R1" H 4250 5200 50  0000 L CNN
F 1 "500Ω" H 4250 5100 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4130 5150 50  0001 C CNN
F 3 "~" H 4200 5150 50  0001 C CNN
	1    4200 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5D05CDC8
P 5350 4750
F 0 "R5" H 5420 4796 50  0000 L CNN
F 1 "500Ω" H 5420 4705 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5280 4750 50  0001 C CNN
F 3 "~" H 5350 4750 50  0001 C CNN
	1    5350 4750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J4
U 1 1 5D071855
P 5450 3750
F 0 "J4" H 5530 3742 50  0000 L CNN
F 1 "Power-Interrupt" H 5530 3651 50  0000 L CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type011_RT05502HBWC_1x02_P5.00mm_Horizontal" H 5450 3750 50  0001 C CNN
F 3 "~" H 5450 3750 50  0001 C CNN
	1    5450 3750
	1    0    0    -1  
$EndComp
Text GLabel 4050 4150 2    50   Input ~ 0
Interrupt-High
Text GLabel 5250 3750 0    50   Input ~ 0
Interrupt-High
$Comp
L power:GND #PWR0101
U 1 1 5D0879E2
P 5250 3850
F 0 "#PWR0101" H 5250 3600 50  0001 C CNN
F 1 "GND" H 5255 3677 50  0000 C CNN
F 2 "" H 5250 3850 50  0001 C CNN
F 3 "" H 5250 3850 50  0001 C CNN
	1    5250 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5D0881D5
P 4050 3850
F 0 "#PWR0102" H 4050 3600 50  0001 C CNN
F 1 "GND" H 4055 3677 50  0000 C CNN
F 2 "" H 4050 3850 50  0001 C CNN
F 3 "" H 4050 3850 50  0001 C CNN
	1    4050 3850
	1    0    0    -1  
$EndComp
Text GLabel 4050 3750 2    50   Input ~ 0
Servo-High
$Comp
L power:GND #PWR0103
U 1 1 5D088C7A
P 5350 5300
F 0 "#PWR0103" H 5350 5050 50  0001 C CNN
F 1 "GND" H 5355 5127 50  0000 C CNN
F 2 "" H 5350 5300 50  0001 C CNN
F 3 "" H 5350 5300 50  0001 C CNN
	1    5350 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 5200 4450 5300
Wire Wire Line
	4450 5300 4750 5300
Wire Wire Line
	4750 5150 4750 5300
Connection ~ 4750 5300
Wire Wire Line
	4750 5300 5050 5300
Wire Wire Line
	5050 5000 5050 5300
Connection ~ 5050 5300
Wire Wire Line
	5050 5300 5350 5300
Wire Wire Line
	5350 4900 5350 5300
Connection ~ 5350 5300
Wire Wire Line
	4050 4550 4450 4550
Wire Wire Line
	4050 4450 4750 4450
Wire Wire Line
	4050 4350 5050 4350
Wire Wire Line
	4050 4250 5350 4250
Wire Wire Line
	4450 4850 4450 4900
Wire Wire Line
	4750 4750 4750 4850
Wire Wire Line
	5050 4650 5050 4700
Wire Wire Line
	5350 4550 5350 4600
$Comp
L Connector:Screw_Terminal_01x04 J5
U 1 1 5D054671
P 5100 3150
F 0 "J5" H 5250 3000 50  0000 C CNN
F 1 "Interrupt-Out" H 5450 3100 50  0000 C CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type011_RT05504HBWC_1x04_P5.00mm_Horizontal" H 5100 3150 50  0001 C CNN
F 3 "~" H 5100 3150 50  0001 C CNN
	1    5100 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 3050 4250 3050
Wire Wire Line
	4050 3150 4250 3150
Wire Wire Line
	4050 3250 4250 3250
Wire Wire Line
	4050 3350 4250 3350
Wire Wire Line
	4900 3050 4700 3050
Wire Wire Line
	4900 3150 4700 3150
Wire Wire Line
	4900 3250 4700 3250
Wire Wire Line
	4900 3350 4700 3350
Text Label 4150 3050 0    50   ~ 0
I4
Text Label 4150 3150 0    50   ~ 0
I3
Text Label 4150 3250 0    50   ~ 0
I2
Text Label 4150 3350 0    50   ~ 0
I1
Text Label 4750 3050 0    50   ~ 0
I1
Text Label 4750 3150 0    50   ~ 0
I2
Text Label 4750 3250 0    50   ~ 0
I3
Text Label 4750 3350 0    50   ~ 0
I4
Text Label 5150 4250 0    50   ~ 0
SIG5
Text Label 4850 4350 0    50   ~ 0
SIG4
Text Label 4550 4450 0    50   ~ 0
SIG3
Text Label 4250 4550 0    50   ~ 0
SIG2
Wire Wire Line
	4200 5300 4450 5300
Wire Wire Line
	4200 4950 4200 5000
Connection ~ 4450 5300
Wire Wire Line
	4050 4650 4200 4650
Text Label 4050 4650 0    50   ~ 0
SIG1
Text GLabel 6950 4850 0    50   Input ~ 0
Servo-High
Text GLabel 6950 4550 0    50   Input ~ 0
Servo-High
Text GLabel 6950 4250 0    50   Input ~ 0
Servo-High
Text GLabel 6950 3950 0    50   Input ~ 0
Servo-High
Text GLabel 6950 3650 0    50   Input ~ 0
Servo-High
$Comp
L power:GND #PWR0104
U 1 1 5D0BECE7
P 6350 5050
F 0 "#PWR0104" H 6350 4800 50  0001 C CNN
F 1 "GND" H 6355 4877 50  0000 C CNN
F 2 "" H 6350 5050 50  0001 C CNN
F 3 "" H 6350 5050 50  0001 C CNN
	1    6350 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 4950 6350 4950
Wire Wire Line
	6350 4950 6350 5050
Wire Wire Line
	6950 4650 6350 4650
Wire Wire Line
	6350 4650 6350 4950
Connection ~ 6350 4950
Wire Wire Line
	6950 4350 6350 4350
Wire Wire Line
	6350 4350 6350 4650
Connection ~ 6350 4650
Wire Wire Line
	6950 4050 6350 4050
Wire Wire Line
	6350 4050 6350 4350
Connection ~ 6350 4350
Wire Wire Line
	6950 3750 6350 3750
Wire Wire Line
	6350 3750 6350 4050
Connection ~ 6350 4050
Wire Wire Line
	6950 3550 6700 3550
Wire Wire Line
	6950 3850 6700 3850
Wire Wire Line
	6950 4150 6700 4150
Wire Wire Line
	6950 4450 6700 4450
Wire Wire Line
	6950 4750 6700 4750
Text Label 6750 3550 0    50   ~ 0
SIG5
Text Label 6750 3850 0    50   ~ 0
SIG4
Text Label 6750 4150 0    50   ~ 0
SIG3
Text Label 6750 4450 0    50   ~ 0
SIG2
Text Label 6750 4750 0    50   ~ 0
SIG1
$Comp
L Mechanical:MountingHole J7
U 1 1 5D093CBE
P 6050 3000
F 0 "J7" H 6000 3100 50  0000 L CNN
F 1 "Mounting Pin" H 5850 2750 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 6050 3000 50  0001 C CNN
F 3 "~" H 6050 3000 50  0001 C CNN
	1    6050 3000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole J8
U 1 1 5D0960CE
P 6700 3000
F 0 "J8" H 6650 3100 50  0000 L CNN
F 1 "Mounting Pin" H 6500 2750 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 6700 3000 50  0001 C CNN
F 3 "~" H 6700 3000 50  0001 C CNN
	1    6700 3000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole J10
U 1 1 5D0969CB
P 8000 3000
F 0 "J10" H 7950 3100 50  0000 L CNN
F 1 "Mounting Pin" H 7850 2750 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 8000 3000 50  0001 C CNN
F 3 "~" H 8000 3000 50  0001 C CNN
	1    8000 3000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole J9
U 1 1 5D097449
P 7350 3000
F 0 "J9" H 7300 3100 50  0000 L CNN
F 1 "Mounting Pin" H 7150 2750 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 7350 3000 50  0001 C CNN
F 3 "~" H 7350 3000 50  0001 C CNN
	1    7350 3000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
