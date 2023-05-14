EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Intelligent Power Source Selector"
Date "2023-04-10"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 7800 1900
Wire Wire Line
	7800 1900 7800 2000
$Comp
L power:GND #PWR?
U 1 1 6462D2E0
P 7800 2000
F 0 "#PWR?" H 7800 1750 50  0001 C CNN
F 1 "GND" H 7805 1827 50  0000 C CNN
F 2 "" H 7800 2000 50  0001 C CNN
F 3 "" H 7800 2000 50  0001 C CNN
	1    7800 2000
	1    0    0    -1  
$EndComp
Text Notes 6950 750  0    118  Italic 24
LEDS
Wire Wire Line
	7800 1100 7800 1500
Wire Wire Line
	7800 1500 7800 1900
Connection ~ 7800 1500
Wire Wire Line
	7550 1500 7800 1500
Wire Wire Line
	7550 1900 7800 1900
Wire Wire Line
	7550 1100 7800 1100
Wire Wire Line
	7100 1100 7250 1100
Wire Wire Line
	7100 1500 7250 1500
Wire Wire Line
	7100 1900 7250 1900
$Comp
L Device:R R3
U 1 1 643787E5
P 7400 1900
F 0 "R3" V 7193 1900 50  0000 C CNN
F 1 "1K" V 7284 1900 50  0000 C CNN
F 2 "" V 7330 1900 50  0001 C CNN
F 3 "~" H 7400 1900 50  0001 C CNN
	1    7400 1900
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 64377F63
P 7400 1500
F 0 "R2" V 7193 1500 50  0000 C CNN
F 1 "1K" V 7284 1500 50  0000 C CNN
F 2 "" V 7330 1500 50  0001 C CNN
F 3 "~" H 7400 1500 50  0001 C CNN
	1    7400 1500
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 6437737D
P 7400 1100
F 0 "R1" V 7193 1100 50  0000 C CNN
F 1 "1K" V 7284 1100 50  0000 C CNN
F 2 "" V 7330 1100 50  0001 C CNN
F 3 "~" H 7400 1100 50  0001 C CNN
	1    7400 1100
	0    1    1    0   
$EndComp
$Comp
L Device:LED D3
U 1 1 64375986
P 6950 1900
F 0 "D3" H 6943 1645 50  0000 C CNN
F 1 "LED" H 6943 1736 50  0000 C CNN
F 2 "" H 6950 1900 50  0001 C CNN
F 3 "~" H 6950 1900 50  0001 C CNN
	1    6950 1900
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D1
U 1 1 6437482B
P 6950 1100
F 0 "D1" H 6943 845 50  0000 C CNN
F 1 "LED" H 6943 936 50  0000 C CNN
F 2 "" H 6950 1100 50  0001 C CNN
F 3 "~" H 6950 1100 50  0001 C CNN
	1    6950 1100
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D2
U 1 1 64373614
P 6950 1500
F 0 "D2" H 6943 1245 50  0000 C CNN
F 1 "LED" H 6943 1336 50  0000 C CNN
F 2 "" H 6950 1500 50  0001 C CNN
F 3 "~" H 6950 1500 50  0001 C CNN
	1    6950 1500
	-1   0    0    1   
$EndComp
Wire Wire Line
	3050 4350 3950 4350
Connection ~ 3050 4350
Wire Wire Line
	3050 4250 3050 4350
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 64370964
P 3050 4250
F 0 "#FLG0102" H 3050 4325 50  0001 C CNN
F 1 "PWR_FLAG" H 3050 4423 50  0000 C CNN
F 2 "" H 3050 4250 50  0001 C CNN
F 3 "~" H 3050 4250 50  0001 C CNN
	1    3050 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 4350 3950 5050
Wire Wire Line
	2300 4350 3050 4350
Wire Wire Line
	2300 4800 2300 4650
$Comp
L power:GND #PWR06
U 1 1 6436BB2B
P 2300 4800
F 0 "#PWR06" H 2300 4550 50  0001 C CNN
F 1 "GND" H 2305 4627 50  0000 C CNN
F 2 "" H 2300 4800 50  0001 C CNN
F 3 "" H 2300 4800 50  0001 C CNN
	1    2300 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT2
U 1 1 6436A930
P 2300 4550
F 0 "BT2" H 2418 4646 50  0000 L CNN
F 1 "3V" H 2418 4555 50  0000 L CNN
F 2 "" V 2300 4610 50  0001 C CNN
F 3 "~" V 2300 4610 50  0001 C CNN
	1    2300 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2650 6100 2650
Text GLabel 6300 2650 2    50   Input ~ 0
CE
Wire Wire Line
	6300 2850 6100 2850
Text GLabel 6300 2850 2    50   Input ~ 0
IO
Wire Wire Line
	6300 2950 6100 2950
Text GLabel 6300 2950 2    50   Input ~ 0
SCLK
Text Notes 2000 6400 0    118  Italic 24
Real-Time Clock Module
NoConn ~ 3850 5050
Wire Wire Line
	4600 5250 4450 5250
Text GLabel 4600 5250 2    50   Input ~ 0
IO
Wire Wire Line
	3200 5350 3450 5350
Text GLabel 3200 5350 0    50   Input ~ 0
CE
Wire Wire Line
	3200 5250 3450 5250
Text GLabel 3200 5250 0    50   Input ~ 0
SCLK
Wire Wire Line
	3950 6000 3950 5850
$Comp
L power:GND #PWR07
U 1 1 6434316E
P 3950 6000
F 0 "#PWR07" H 3950 5750 50  0001 C CNN
F 1 "GND" H 3955 5827 50  0000 C CNN
F 2 "" H 3950 6000 50  0001 C CNN
F 3 "" H 3950 6000 50  0001 C CNN
	1    3950 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 5650 3450 5650
Wire Wire Line
	3250 5800 3250 5650
Wire Wire Line
	2750 5800 3250 5800
Wire Wire Line
	3250 5550 3450 5550
Wire Wire Line
	3250 5500 3250 5550
Wire Wire Line
	2750 5500 3250 5500
$Comp
L Device:Crystal Y1
U 1 1 6433DD58
P 2750 5650
F 0 "Y1" V 2700 5250 50  0000 L CNN
F 1 "32.768KHz" V 2800 5100 50  0000 L CNN
F 2 "" H 2750 5650 50  0001 C CNN
F 3 "~" H 2750 5650 50  0001 C CNN
	1    2750 5650
	0    1    1    0   
$EndComp
$Comp
L Timer_RTC:DS1302+ U6
U 1 1 6433D178
P 3950 5450
F 0 "U6" H 4494 5496 50  0000 L CNN
F 1 "DS1302+" H 4494 5405 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 3950 4950 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DS1302.pdf" H 3950 5250 50  0001 C CNN
	1    3950 5450
	1    0    0    -1  
$EndComp
Text Notes 7200 5300 0    118  Italic 24
HC12 Transceiver
Text Notes 9850 1500 0    118  Italic 24
LCD
Text Notes 5050 5800 0    118  Italic 24
ESP32 MCU
Text Notes 2650 2000 0    118  Italic 24
PWR SUPPLY
Wire Wire Line
	9550 1550 9550 1700
Text GLabel 9550 1550 1    50   Input ~ 0
5V
Wire Wire Line
	3600 3700 3450 3700
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 64370F2B
P 3600 3700
F 0 "#FLG0101" H 3600 3775 50  0001 C CNN
F 1 "PWR_FLAG" V 3600 3828 50  0000 L CNN
F 2 "" H 3600 3700 50  0001 C CNN
F 3 "~" H 3600 3700 50  0001 C CNN
	1    3600 3700
	0    1    1    0   
$EndComp
Connection ~ 10350 3050
Wire Wire Line
	10350 2050 10350 3050
Wire Wire Line
	9650 2050 10350 2050
Connection ~ 9550 4050
Wire Wire Line
	10350 4050 9550 4050
Wire Wire Line
	10350 3050 10350 4050
Wire Wire Line
	9950 3050 10350 3050
Connection ~ 9550 1700
Wire Wire Line
	10250 1700 9550 1700
Wire Wire Line
	10250 3150 10250 1700
Wire Wire Line
	9950 3150 10250 3150
Wire Wire Line
	9550 1700 9550 2050
Wire Wire Line
	8100 1700 9550 1700
Wire Wire Line
	8100 2450 8100 1700
Connection ~ 8100 4050
Wire Wire Line
	7450 3250 7450 4050
Connection ~ 7450 3250
Wire Wire Line
	7450 4050 8100 4050
Wire Wire Line
	8100 4050 8100 3850
Wire Wire Line
	7450 3150 7450 3250
Connection ~ 7450 3150
Wire Wire Line
	7600 3150 7450 3150
Wire Wire Line
	7450 3250 7600 3250
Wire Wire Line
	7450 3050 7450 3150
Wire Wire Line
	7600 3050 7450 3050
Wire Wire Line
	7500 2850 7600 2850
Text GLabel 7500 2850 0    50   Input ~ 0
SDA
Wire Wire Line
	7500 2750 7600 2750
Text GLabel 7500 2750 0    50   Input ~ 0
SCL
NoConn ~ 9150 3050
NoConn ~ 9150 2950
NoConn ~ 9150 2850
NoConn ~ 9150 2750
NoConn ~ 8600 3050
Wire Wire Line
	8850 2450 9150 2450
Wire Wire Line
	8850 2950 8850 2450
Wire Wire Line
	8600 2950 8850 2950
Wire Wire Line
	8750 2350 9150 2350
Wire Wire Line
	8750 2850 8750 2350
Wire Wire Line
	8600 2850 8750 2850
Wire Wire Line
	8650 2250 9150 2250
Wire Wire Line
	8650 2750 8650 2250
Wire Wire Line
	8600 2750 8650 2750
NoConn ~ 7600 3550
Wire Wire Line
	8950 4050 8100 4050
Connection ~ 8950 4050
Wire Wire Line
	8950 4150 8950 4050
$Comp
L power:GND #PWR04
U 1 1 6435BC06
P 8950 4150
F 0 "#PWR04" H 8950 3900 50  0001 C CNN
F 1 "GND" H 8955 3977 50  0000 C CNN
F 2 "" H 8950 4150 50  0001 C CNN
F 3 "" H 8950 4150 50  0001 C CNN
	1    8950 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 4050 8950 4050
Wire Wire Line
	9550 3650 9550 4050
Wire Wire Line
	8600 3450 9150 3450
Wire Wire Line
	8600 3350 9150 3350
Wire Wire Line
	8600 3250 9150 3250
Wire Wire Line
	8600 3150 9150 3150
$Comp
L Interface_Expansion:PCF8574 U4
U 1 1 64353E56
P 8100 3150
F 0 "U4" H 7800 3900 50  0000 C CNN
F 1 "PCF8574" H 7800 3800 50  0000 C CNN
F 2 "" H 8100 3150 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/PCF8574_PCF8574A.pdf" H 8100 3150 50  0001 C CNN
	1    8100 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 2450 2650 2600
$Comp
L power:PWR_FLAG #FLG01
U 1 1 64352AEB
P 2650 2450
F 0 "#FLG01" H 2650 2525 50  0001 C CNN
F 1 "PWR_FLAG" H 2650 2623 50  0000 C CNN
F 2 "" H 2650 2450 50  0001 C CNN
F 3 "~" H 2650 2450 50  0001 C CNN
	1    2650 2450
	1    0    0    -1  
$EndComp
NoConn ~ 6100 4750
NoConn ~ 6100 4650
NoConn ~ 6100 4550
NoConn ~ 6100 4450
NoConn ~ 6100 4350
NoConn ~ 6100 4250
NoConn ~ 6100 4150
NoConn ~ 6100 4050
NoConn ~ 6100 3750
NoConn ~ 6100 3650
Wire Wire Line
	6350 3950 6100 3950
Text GLabel 6350 3950 2    50   Input ~ 0
SCL
Wire Wire Line
	6350 3850 6100 3850
Text GLabel 6350 3850 2    50   Input ~ 0
SDA
Wire Wire Line
	6300 3350 6100 3350
Text GLabel 6300 3350 2    50   Input ~ 0
HC12_SET
Wire Wire Line
	6300 3550 6100 3550
Text GLabel 6300 3550 2    50   Input ~ 0
HC12_RX
Wire Wire Line
	6300 3450 6100 3450
Text GLabel 6300 3450 2    50   Input ~ 0
HC12_TX
NoConn ~ 6100 2750
NoConn ~ 6100 2550
NoConn ~ 6100 2450
NoConn ~ 4900 4150
NoConn ~ 4900 4050
NoConn ~ 4900 3950
NoConn ~ 4900 3850
NoConn ~ 4900 3750
NoConn ~ 4900 3650
NoConn ~ 4900 2750
NoConn ~ 4900 2650
NoConn ~ 4900 2450
Wire Wire Line
	1900 3350 1900 3500
$Comp
L power:GND #PWR01
U 1 1 6434AE36
P 1900 3500
F 0 "#PWR01" H 1900 3250 50  0001 C CNN
F 1 "GND" H 1905 3327 50  0000 C CNN
F 2 "" H 1900 3500 50  0001 C CNN
F 3 "" H 1900 3500 50  0001 C CNN
	1    1900 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3700 3450 3650
Connection ~ 3450 3700
Wire Wire Line
	2950 3700 3450 3700
Wire Wire Line
	2950 2900 2950 3700
Wire Wire Line
	3450 2900 2950 2900
Wire Wire Line
	3450 3750 3450 3700
$Comp
L power:GND #PWR02
U 1 1 64349FEB
P 3450 3750
F 0 "#PWR02" H 3450 3500 50  0001 C CNN
F 1 "GND" H 3455 3577 50  0000 C CNN
F 2 "" H 3450 3750 50  0001 C CNN
F 3 "" H 3450 3750 50  0001 C CNN
	1    3450 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 5200 5500 5050
$Comp
L power:GND #PWR03
U 1 1 643495A1
P 5500 5200
F 0 "#PWR03" H 5500 4950 50  0001 C CNN
F 1 "GND" H 5505 5027 50  0000 C CNN
F 2 "" H 5500 5200 50  0001 C CNN
F 3 "" H 5500 5200 50  0001 C CNN
	1    5500 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4600 8500 4650
Wire Wire Line
	7700 4600 8500 4600
$Comp
L power:GND #PWR05
U 1 1 64348D80
P 8500 4650
F 0 "#PWR05" H 8500 4400 50  0001 C CNN
F 1 "GND" H 8505 4477 50  0000 C CNN
F 2 "" H 8500 4650 50  0001 C CNN
F 3 "" H 8500 4650 50  0001 C CNN
	1    8500 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 4900 7700 4900
Text GLabel 7850 4900 2    50   Input ~ 0
HC12_SET
Wire Wire Line
	7850 4800 7700 4800
Text GLabel 7850 4800 2    50   Input ~ 0
HC12_TX
Wire Wire Line
	7850 4700 7700 4700
Text GLabel 7850 4700 2    50   Input ~ 0
HC12_RX
Wire Wire Line
	7850 4500 7700 4500
Text GLabel 7850 4500 2    50   Input ~ 0
5V
Wire Wire Line
	3900 3350 3750 3350
Text GLabel 3900 3350 2    50   Input ~ 0
5V
Wire Wire Line
	5500 2050 5500 2250
Wire Wire Line
	4050 2050 5500 2050
Wire Wire Line
	4050 2600 4050 2050
Wire Wire Line
	3750 2600 4050 2600
Wire Wire Line
	2650 2600 3150 2600
Connection ~ 2650 2600
Wire Wire Line
	2650 3350 2650 2600
Wire Wire Line
	3150 3350 2650 3350
Wire Wire Line
	1900 2600 2650 2600
Wire Wire Line
	1900 2950 1900 2600
$Comp
L Regulator_Linear:LM7805_TO220 U2
U 1 1 64344BA6
P 3450 3350
F 0 "U2" H 3450 3592 50  0000 C CNN
F 1 "LM7805" H 3450 3501 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 3450 3575 50  0001 C CIN
F 3 "https://www.onsemi.cn/PowerSolutions/document/MC7800-D.PDF" H 3450 3300 50  0001 C CNN
	1    3450 3350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J1
U 1 1 64343059
P 7500 4700
F 0 "J1" H 7608 5081 50  0000 C CNN
F 1 "HC-12" H 7608 4990 50  0000 C CNN
F 2 "" H 7500 4700 50  0001 C CNN
F 3 "~" H 7500 4700 50  0001 C CNN
	1    7500 4700
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:NHD-0420H1Z U5
U 1 1 6434195C
P 9550 2850
F 0 "U5" H 9800 2100 50  0000 C CNN
F 1 "LCD_20_4" H 9900 2000 50  0000 C CNN
F 2 "Display:NHD-0420H1Z" H 9550 1950 50  0001 C CNN
F 3 "http://www.newhavendisplay.com/specs/NHD-0420H1Z-FSW-GBW-33V3.pdf" H 9650 2750 50  0001 C CNN
	1    9550 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery BT1
U 1 1 6433F2A9
P 1900 3150
F 0 "BT1" H 2008 3196 50  0000 L CNN
F 1 "Battery" H 2008 3105 50  0000 L CNN
F 2 "" V 1900 3210 50  0001 C CNN
F 3 "~" V 1900 3210 50  0001 C CNN
	1    1900 3150
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7805_TO220 U1
U 1 1 6433BCEB
P 3450 2600
F 0 "U1" H 3450 2842 50  0000 C CNN
F 1 "LM2596" H 3450 2751 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 3450 2825 50  0001 C CIN
F 3 "https://www.onsemi.cn/PowerSolutions/document/MC7800-D.PDF" H 3450 2550 50  0001 C CNN
	1    3450 2600
	1    0    0    -1  
$EndComp
$Comp
L RF_Module:ESP32-WROOM-32D U3
U 1 1 64334E4C
P 5500 3650
F 0 "U3" H 6000 5100 50  0000 C CNN
F 1 "ESP32-WROOM-32D" H 6000 5000 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 5500 2150 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf" H 5200 3700 50  0001 C CNN
	1    5500 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 3050 6550 3050
Wire Wire Line
	6550 3050 6550 1100
Wire Wire Line
	6550 1100 6800 1100
Wire Wire Line
	6100 3150 6600 3150
Wire Wire Line
	6600 3150 6600 1500
Wire Wire Line
	6600 1500 6800 1500
Wire Wire Line
	6100 3250 6650 3250
Wire Wire Line
	6650 3250 6650 1900
Wire Wire Line
	6650 1900 6800 1900
$EndSCHEMATC