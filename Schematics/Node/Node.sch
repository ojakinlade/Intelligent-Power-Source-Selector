EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "IPSS Node Schematics"
Date "2023-03-22"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 641A331D
P 5700 3550
F 0 "A1" H 6050 2600 50  0000 C CNN
F 1 "Arduino_Nano" H 6100 2500 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 5700 3550 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 5700 3550 50  0001 C CNN
	1    5700 3550
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:L7805 U1
U 1 1 641A4349
P 3950 2950
F 0 "U1" H 3950 3192 50  0000 C CNN
F 1 "L7805" H 3950 3101 50  0000 C CNN
F 2 "" H 3975 2800 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 3950 2900 50  0001 C CNN
	1    3950 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery BT1
U 1 1 641A4FAD
P 2950 3200
F 0 "BT1" H 3058 3246 50  0000 L CNN
F 1 "Battery" H 3058 3155 50  0000 L CNN
F 2 "" V 2950 3260 50  0001 C CNN
F 3 "~" V 2950 3260 50  0001 C CNN
	1    2950 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 641A7025
P 2950 3550
F 0 "#PWR01" H 2950 3300 50  0001 C CNN
F 1 "GND" H 2955 3377 50  0000 C CNN
F 2 "" H 2950 3550 50  0001 C CNN
F 3 "" H 2950 3550 50  0001 C CNN
	1    2950 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 3400 2950 3500
Text GLabel 2950 2850 1    50   Input ~ 0
7.4V
Wire Wire Line
	2950 2850 2950 2950
Wire Wire Line
	3650 2950 3250 2950
Connection ~ 2950 2950
Wire Wire Line
	2950 2950 2950 3000
Text GLabel 4400 2950 2    50   Input ~ 0
5V
Text GLabel 5600 2450 1    50   Input ~ 0
7.4V
Wire Wire Line
	5600 2450 5600 2550
$Comp
L power:GND #PWR03
U 1 1 641A9964
P 5750 4700
F 0 "#PWR03" H 5750 4450 50  0001 C CNN
F 1 "GND" H 5755 4527 50  0000 C CNN
F 2 "" H 5750 4700 50  0001 C CNN
F 3 "" H 5750 4700 50  0001 C CNN
	1    5750 4700
	1    0    0    -1  
$EndComp
NoConn ~ 6200 2950
NoConn ~ 6200 3050
NoConn ~ 6200 3350
NoConn ~ 6200 3550
NoConn ~ 6200 3650
NoConn ~ 6200 3750
NoConn ~ 6200 3850
NoConn ~ 6200 3950
NoConn ~ 6200 4050
NoConn ~ 6200 4150
NoConn ~ 6200 4250
NoConn ~ 5200 4250
NoConn ~ 5200 4150
NoConn ~ 5200 4050
NoConn ~ 5200 3950
NoConn ~ 5200 3350
NoConn ~ 5200 3050
NoConn ~ 5200 2950
NoConn ~ 5800 2550
NoConn ~ 5900 2550
NoConn ~ 5200 3550
NoConn ~ 5200 3650
$Comp
L Connector:Conn_01x05_Male J1
U 1 1 641AB350
P 6900 3200
F 0 "J1" H 7000 3650 50  0000 C CNN
F 1 "HC12" H 7000 3550 50  0000 C CNN
F 2 "" H 6900 3200 50  0001 C CNN
F 3 "~" H 6900 3200 50  0001 C CNN
	1    6900 3200
	1    0    0    -1  
$EndComp
Text GLabel 7250 3000 2    50   Input ~ 0
5V
Wire Wire Line
	7250 3000 7100 3000
Text GLabel 7250 3200 2    50   Input ~ 0
HC12_RX
Text GLabel 7250 3300 2    50   Input ~ 0
HC12_TX
Text GLabel 7250 3400 2    50   Input ~ 0
HC12_SET
Wire Wire Line
	7250 3400 7100 3400
Wire Wire Line
	7250 3300 7100 3300
Wire Wire Line
	7250 3200 7100 3200
Text GLabel 5050 3150 0    50   Input ~ 0
HC12_TX
Wire Wire Line
	5050 3150 5200 3150
Text GLabel 5050 3250 0    50   Input ~ 0
HC12_RX
Wire Wire Line
	5050 3250 5200 3250
Text GLabel 5050 3450 0    50   Input ~ 0
HC12_SET
Wire Wire Line
	5050 3450 5200 3450
Text GLabel 5050 3750 0    50   Input ~ 0
PZEM_TX
Wire Wire Line
	5050 3750 5200 3750
Text GLabel 5050 3850 0    50   Input ~ 0
PZEM_RX
Wire Wire Line
	5050 3850 5200 3850
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 641AE9DD
P 7000 3950
F 0 "J2" H 7100 4300 50  0000 C CNN
F 1 "PZEM_004T" H 7100 4200 50  0000 C CNN
F 2 "" H 7000 3950 50  0001 C CNN
F 3 "~" H 7000 3950 50  0001 C CNN
	1    7000 3950
	1    0    0    -1  
$EndComp
Text GLabel 7350 3850 2    50   Input ~ 0
5V
Wire Wire Line
	7350 3850 7200 3850
Text GLabel 7350 3950 2    50   Input ~ 0
PZEM_RX
Wire Wire Line
	7350 3950 7200 3950
Text GLabel 7350 4050 2    50   Input ~ 0
PZEM_TX
Wire Wire Line
	7350 4050 7200 4050
$Comp
L power:GND #PWR04
U 1 1 641B06A8
P 7350 4200
F 0 "#PWR04" H 7350 3950 50  0001 C CNN
F 1 "GND" H 7355 4027 50  0000 C CNN
F 2 "" H 7350 4200 50  0001 C CNN
F 3 "" H 7350 4200 50  0001 C CNN
	1    7350 4200
	1    0    0    -1  
$EndComp
Text Notes 2600 1600 0    138  Italic 28
INTELLIGENT POWER SOURCE SELECTOR NODE SCHEMATICS\n
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 641B5A43
P 3250 2900
F 0 "#FLG0101" H 3250 2975 50  0001 C CNN
F 1 "PWR_FLAG" H 3250 3073 50  0000 C CNN
F 2 "" H 3250 2900 50  0001 C CNN
F 3 "~" H 3250 2900 50  0001 C CNN
	1    3250 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2900 3250 2950
Connection ~ 3250 2950
Wire Wire Line
	3250 2950 2950 2950
Wire Wire Line
	4400 2950 4250 2950
$Comp
L power:GND #PWR0101
U 1 1 641B7D11
P 7900 3150
F 0 "#PWR0101" H 7900 2900 50  0001 C CNN
F 1 "GND" H 7905 2977 50  0000 C CNN
F 2 "" H 7900 3150 50  0001 C CNN
F 3 "" H 7900 3150 50  0001 C CNN
	1    7900 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 3100 7900 3150
Wire Wire Line
	7100 3100 7900 3100
Wire Wire Line
	5800 4550 5800 4700
Wire Wire Line
	5800 4700 5750 4700
Wire Wire Line
	5700 4550 5700 4700
Wire Wire Line
	5700 4700 5750 4700
Connection ~ 5750 4700
Wire Wire Line
	7200 4150 7350 4150
Wire Wire Line
	7350 4150 7350 4200
$Comp
L power:GND #PWR0102
U 1 1 641BB1D2
P 3950 3300
F 0 "#PWR0102" H 3950 3050 50  0001 C CNN
F 1 "GND" H 3955 3127 50  0000 C CNN
F 2 "" H 3950 3300 50  0001 C CNN
F 3 "" H 3950 3300 50  0001 C CNN
	1    3950 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3300 3950 3250
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 641BBC08
P 3100 3500
F 0 "#FLG0102" H 3100 3575 50  0001 C CNN
F 1 "PWR_FLAG" V 3100 3628 50  0000 L CNN
F 2 "" H 3100 3500 50  0001 C CNN
F 3 "~" H 3100 3500 50  0001 C CNN
	1    3100 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	3100 3500 2950 3500
Connection ~ 2950 3500
Wire Wire Line
	2950 3500 2950 3550
$EndSCHEMATC
