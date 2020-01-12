EESchema Schematic File Version 4
LIBS:RemoteCable2-cache
EELAYER 26 0
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
L power:+5V #PWR02
U 1 1 5DAC04D5
P 6700 1350
F 0 "#PWR02" H 6700 1200 50  0001 C CNN
F 1 "+5V" H 6715 1523 50  0000 C CNN
F 2 "" H 6700 1350 50  0001 C CNN
F 3 "" H 6700 1350 50  0001 C CNN
	1    6700 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 1350 6700 3750
Wire Wire Line
	6700 3750 7500 3750
$Comp
L power:+3.3V #PWR08
U 1 1 5DAC0529
P 9000 1350
F 0 "#PWR08" H 9000 1200 50  0001 C CNN
F 1 "+3.3V" H 9015 1523 50  0000 C CNN
F 2 "" H 9000 1350 50  0001 C CNN
F 3 "" H 9000 1350 50  0001 C CNN
	1    9000 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 1350 9000 3750
Wire Wire Line
	9000 3750 8650 3750
$Comp
L power:GND #PWR04
U 1 1 5DAC0575
P 7300 4000
F 0 "#PWR04" H 7300 3750 50  0001 C CNN
F 1 "GND" H 7305 3827 50  0000 C CNN
F 2 "" H 7300 4000 50  0001 C CNN
F 3 "" H 7300 4000 50  0001 C CNN
	1    7300 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 3650 7300 3650
$Comp
L power:GND #PWR011
U 1 1 5DAC05B0
P 9600 3250
F 0 "#PWR011" H 9600 3000 50  0001 C CNN
F 1 "GND" H 9605 3077 50  0000 C CNN
F 2 "" H 9600 3250 50  0001 C CNN
F 3 "" H 9600 3250 50  0001 C CNN
	1    9600 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 2900 9600 3200
Wire Wire Line
	9800 2900 9600 2900
Wire Wire Line
	10550 2700 10650 2700
Wire Wire Line
	10650 2700 10650 3200
Wire Wire Line
	9600 3200 9600 3250
$Comp
L power:+3.3V #PWR09
U 1 1 5DAC0673
P 9400 1350
F 0 "#PWR09" H 9400 1200 50  0001 C CNN
F 1 "+3.3V" H 9415 1523 50  0000 C CNN
F 2 "" H 9400 1350 50  0001 C CNN
F 3 "" H 9400 1350 50  0001 C CNN
	1    9400 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 1350 9400 2700
Wire Wire Line
	9400 2700 9800 2700
NoConn ~ 9800 2300
NoConn ~ 9800 2400
NoConn ~ 9800 2500
NoConn ~ 9800 2600
NoConn ~ 10550 2900
NoConn ~ 10550 3000
NoConn ~ 10550 2600
NoConn ~ 10550 2500
NoConn ~ 10550 2300
NoConn ~ 10550 2200
NoConn ~ 10550 2100
NoConn ~ 10550 2000
Wire Wire Line
	7500 2350 7450 2350
Wire Wire Line
	7300 3650 7300 3900
Wire Wire Line
	8650 3650 8800 3650
Wire Wire Line
	8800 3650 8800 3900
Wire Wire Line
	8800 3900 7300 3900
Connection ~ 7300 3900
Wire Wire Line
	7300 3900 7300 4000
Wire Wire Line
	7450 2350 7450 1600
NoConn ~ 10550 2800
Wire Wire Line
	9800 2800 9250 2800
Wire Wire Line
	9250 2800 9250 1600
Wire Wire Line
	9250 1600 7450 1600
Wire Wire Line
	8650 2350 8700 2350
Wire Wire Line
	8700 2350 8700 2000
Wire Wire Line
	8700 2000 9800 2000
Wire Wire Line
	8650 2850 8750 2850
Wire Wire Line
	8750 2850 8750 2100
Wire Wire Line
	8750 2100 9800 2100
Wire Wire Line
	8800 2200 8800 2950
Wire Wire Line
	8800 2950 8650 2950
Wire Wire Line
	9800 1900 8850 1900
Wire Wire Line
	8850 1900 8850 3050
Wire Wire Line
	8850 3050 8650 3050
Wire Wire Line
	8800 2200 9800 2200
Wire Wire Line
	8650 3150 8900 3150
Wire Wire Line
	8900 3150 8900 1800
Wire Wire Line
	8900 1800 10600 1800
Wire Wire Line
	10600 1800 10600 1900
Wire Wire Line
	10600 1900 10550 1900
$Comp
L power:+5V #PWR010
U 1 1 5DAC6E51
P 9550 1350
F 0 "#PWR010" H 9550 1200 50  0001 C CNN
F 1 "+5V" H 9565 1523 50  0000 C CNN
F 2 "" H 9550 1350 50  0001 C CNN
F 3 "" H 9550 1350 50  0001 C CNN
	1    9550 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 1350 9550 3000
Wire Wire Line
	9550 3000 9800 3000
$Comp
L Switch:SW_Push SW3
U 1 1 5DAC8CA4
P 3200 3400
F 0 "SW3" H 3200 3685 50  0000 C CNN
F 1 "SW_Push_U" H 3200 3594 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS645" H 3200 3600 50  0001 C CNN
F 3 "" H 3200 3600 50  0001 C CNN
	1    3200 3400
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW4
U 1 1 5DAC8D0D
P 3200 3800
F 0 "SW4" H 3200 4085 50  0000 C CNN
F 1 "SW_Push_OK" H 3200 3994 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS645" H 3200 4000 50  0001 C CNN
F 3 "" H 3200 4000 50  0001 C CNN
	1    3200 3800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW5
U 1 1 5DAC9462
P 3200 4200
F 0 "SW5" H 3200 4485 50  0000 C CNN
F 1 "SW_Push_D" H 3200 4394 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS645" H 3200 4400 50  0001 C CNN
F 3 "" H 3200 4400 50  0001 C CNN
	1    3200 4200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW6
U 1 1 5DAC9BCC
P 4000 3800
F 0 "SW6" H 4000 4085 50  0000 C CNN
F 1 "SW_Push_R" H 4000 3994 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS645" H 4000 4000 50  0001 C CNN
F 3 "" H 4000 4000 50  0001 C CNN
	1    4000 3800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5DACA349
P 2450 3800
F 0 "SW1" H 2450 4085 50  0000 C CNN
F 1 "SW_Push_L" H 2450 3994 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS645" H 2450 4000 50  0001 C CNN
F 3 "" H 2450 4000 50  0001 C CNN
	1    2450 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5DACB23D
P 2900 4550
F 0 "#PWR01" H 2900 4300 50  0001 C CNN
F 1 "GND" H 2905 4377 50  0000 C CNN
F 2 "" H 2900 4550 50  0001 C CNN
F 3 "" H 2900 4550 50  0001 C CNN
	1    2900 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 3800 2750 3800
$Comp
L Switch:SW_Push SW7
U 1 1 5DACAAED
P 4650 3050
F 0 "SW7" H 4650 3335 50  0000 C CNN
F 1 "SW_Push_SHOOT" H 4650 3244 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS645" H 4650 3250 50  0001 C CNN
F 3 "" H 4650 3250 50  0001 C CNN
	1    4650 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3400 2900 3400
Wire Wire Line
	2900 3400 2900 3800
Wire Wire Line
	3000 3800 2900 3800
Connection ~ 2900 3800
Wire Wire Line
	2900 3800 2900 4200
Wire Wire Line
	3000 4200 2900 4200
Connection ~ 2900 4200
Wire Wire Line
	2900 4200 2900 4400
Wire Wire Line
	2250 3800 2200 3800
Wire Wire Line
	2200 3800 2200 4400
Wire Wire Line
	2200 4400 2900 4400
Connection ~ 2900 4400
Wire Wire Line
	2900 4400 2900 4550
Wire Wire Line
	2900 4400 3750 4400
Wire Wire Line
	3750 4400 3750 3800
Wire Wire Line
	3750 3800 3800 3800
Wire Wire Line
	4450 3050 4400 3050
Wire Wire Line
	4400 3050 4400 4400
Wire Wire Line
	4400 4400 3750 4400
Connection ~ 3750 4400
Wire Wire Line
	3400 4200 5650 4200
Wire Wire Line
	5650 4200 5650 3550
Wire Wire Line
	5650 3550 7500 3550
Wire Wire Line
	5600 3800 5600 3450
Wire Wire Line
	5600 3450 7500 3450
Wire Wire Line
	4200 3800 5600 3800
Wire Wire Line
	3400 3800 3550 3800
Wire Wire Line
	3550 3800 3550 3900
Wire Wire Line
	3550 3900 5550 3900
Wire Wire Line
	5550 3900 5550 3350
Wire Wire Line
	5550 3350 7500 3350
Wire Wire Line
	2750 3800 2750 4000
Wire Wire Line
	2750 4000 5500 4000
Wire Wire Line
	5500 4000 5500 3250
Wire Wire Line
	5500 3250 7500 3250
Wire Wire Line
	3400 3400 5450 3400
Wire Wire Line
	5450 3400 5450 3150
Wire Wire Line
	5450 3150 7500 3150
Wire Wire Line
	4850 3050 7500 3050
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 5DB06236
P 10200 4050
F 0 "J2" H 10279 4042 50  0000 L CNN
F 1 "Conn_OLED" H 10279 3951 50  0000 L CNN
F 2 "Connector_JST:JST_XH_S04B-XH-A_1x04_P2.50mm_Horizontal" H 10200 4050 50  0001 C CNN
F 3 "~" H 10200 4050 50  0001 C CNN
	1    10200 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 3950 10000 3950
$Comp
L power:+3.3V #PWR012
U 1 1 5DB0A18A
P 9700 3800
F 0 "#PWR012" H 9700 3650 50  0001 C CNN
F 1 "+3.3V" H 9715 3973 50  0000 C CNN
F 2 "" H 9700 3800 50  0001 C CNN
F 3 "" H 9700 3800 50  0001 C CNN
	1    9700 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 3800 9700 4050
Wire Wire Line
	9700 4050 10000 4050
Wire Wire Line
	10000 4150 9150 4150
Wire Wire Line
	9150 4150 9150 2450
Wire Wire Line
	9150 2450 8650 2450
Wire Wire Line
	10000 4250 9050 4250
Wire Wire Line
	9050 4250 9050 2750
Wire Wire Line
	9050 2750 8650 2750
$Comp
L power:GND #PWR013
U 1 1 5DB1C150
P 9900 5000
F 0 "#PWR013" H 9900 4750 50  0001 C CNN
F 1 "GND" H 9905 4827 50  0000 C CNN
F 2 "" H 9900 5000 50  0001 C CNN
F 3 "" H 9900 5000 50  0001 C CNN
	1    9900 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 3200 10650 3200
$Comp
L power:GND #PWR07
U 1 1 5DB22ECE
P 8850 5800
F 0 "#PWR07" H 8850 5550 50  0001 C CNN
F 1 "GND" H 8855 5627 50  0000 C CNN
F 2 "" H 8850 5800 50  0001 C CNN
F 3 "" H 8850 5800 50  0001 C CNN
	1    8850 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 5700 8850 5800
$Comp
L Device:R R1
U 1 1 5DB2C0F2
P 8750 4850
F 0 "R1" H 8820 4896 50  0000 L CNN
F 1 "1K" H 8820 4805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8680 4850 50  0001 C CNN
F 3 "~" H 8750 4850 50  0001 C CNN
	1    8750 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5DB2C19B
P 8950 4850
F 0 "R2" H 9020 4896 50  0000 L CNN
F 1 "4.7K" H 9020 4805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 8880 4850 50  0001 C CNN
F 3 "~" H 8950 4850 50  0001 C CNN
	1    8950 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 5000 8750 5100
Wire Wire Line
	8950 5000 8950 5100
Wire Wire Line
	8950 4700 8950 3350
Wire Wire Line
	8950 3350 8650 3350
$Comp
L Switch:SW_SPDT SW8
U 1 1 5DB3D4ED
P 6450 4500
F 0 "SW8" H 6450 4785 50  0000 C CNN
F 1 "SW_ONE_SHOOT" H 6450 4694 50  0000 C CNN
F 2 "Button_Switch_THT:SW_SLIDE_AitendoSS12F21G5" H 6450 4500 50  0001 C CNN
F 3 "" H 6450 4500 50  0001 C CNN
	1    6450 4500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5DB3FF48
P 6850 4650
F 0 "#PWR03" H 6850 4400 50  0001 C CNN
F 1 "GND" H 6855 4477 50  0000 C CNN
F 2 "" H 6850 4650 50  0001 C CNN
F 3 "" H 6850 4650 50  0001 C CNN
	1    6850 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 4600 6850 4600
Wire Wire Line
	6850 4600 6850 4650
Wire Wire Line
	6250 2950 7500 2950
Wire Wire Line
	6250 2950 6250 4500
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5DB48405
P 10200 4800
F 0 "J3" H 10280 4792 50  0000 L CNN
F 1 "Conn_BUZZER" H 10280 4701 50  0000 L CNN
F 2 "Connector_JST:JST_XH_S02B-XH-A_1x02_P2.50mm_Horizontal" H 10200 4800 50  0001 C CNN
F 3 "~" H 10200 4800 50  0001 C CNN
	1    10200 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 3950 9900 4900
Wire Wire Line
	10000 4900 9900 4900
Connection ~ 9900 4900
Wire Wire Line
	9900 4900 9900 5000
Wire Wire Line
	9300 4800 9300 3550
Wire Wire Line
	9300 3550 8650 3550
Wire Wire Line
	9300 4800 10000 4800
$Comp
L Switch:SW_Push SW2
U 1 1 5DB57017
P 2500 3000
F 0 "SW2" H 2500 3285 50  0000 C CNN
F 1 "SW_Push_MENU" H 2500 3194 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS645" H 2500 3200 50  0001 C CNN
F 3 "" H 2500 3200 50  0001 C CNN
	1    2500 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 3000 2200 3000
Wire Wire Line
	2200 3000 2200 3800
Connection ~ 2200 3800
Wire Wire Line
	2700 3000 4200 3000
Wire Wire Line
	4200 3000 4200 3250
Wire Wire Line
	4200 3250 5250 3250
Wire Wire Line
	5250 3250 5250 2850
Wire Wire Line
	5250 2850 7500 2850
NoConn ~ 7500 2450
NoConn ~ 7500 2550
NoConn ~ 7500 2650
NoConn ~ 7500 2750
$Comp
L MiniUSBHostShield:MiniUSBHostShield U2
U 1 1 5DBC23F1
P 10200 2400
F 0 "U2" H 10175 3125 50  0000 C CNN
F 1 "MiniUSBHostShield" H 10175 3034 50  0000 C CNN
F 2 "Module:MiniUSBHostShield" H 10100 2400 50  0001 C CNN
F 3 "" H 10100 2400 50  0001 C CNN
	1    10200 2400
	1    0    0    -1  
$EndComp
NoConn ~ 8650 2550
NoConn ~ 8650 2650
NoConn ~ 10550 2400
NoConn ~ 6650 4400
Connection ~ 9600 3200
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5DF95E74
P 10500 1400
F 0 "#FLG0101" H 10500 1475 50  0001 C CNN
F 1 "PWR_FLAG" H 10500 1573 50  0000 C CNN
F 2 "" H 10500 1400 50  0001 C CNN
F 3 "~" H 10500 1400 50  0001 C CNN
	1    10500 1400
	1    0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5DF99729
P 10100 1350
F 0 "#FLG0102" H 10100 1425 50  0001 C CNN
F 1 "PWR_FLAG" H 10100 1524 50  0000 C CNN
F 2 "" H 10100 1350 50  0001 C CNN
F 3 "~" H 10100 1350 50  0001 C CNN
	1    10100 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5DF9976D
P 10100 1350
F 0 "#PWR0101" H 10100 1100 50  0001 C CNN
F 1 "GND" H 10105 1177 50  0000 C CNN
F 2 "" H 10100 1350 50  0001 C CNN
F 3 "" H 10100 1350 50  0001 C CNN
	1    10100 1350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 5DF9CFE3
P 10500 1400
F 0 "#PWR0102" H 10500 1250 50  0001 C CNN
F 1 "+5V" H 10515 1573 50  0000 C CNN
F 2 "" H 10500 1400 50  0001 C CNN
F 3 "" H 10500 1400 50  0001 C CNN
	1    10500 1400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0103
U 1 1 5DFA0859
P 10800 1400
F 0 "#PWR0103" H 10800 1250 50  0001 C CNN
F 1 "+3.3V" H 10815 1573 50  0000 C CNN
F 2 "" H 10800 1400 50  0001 C CNN
F 3 "" H 10800 1400 50  0001 C CNN
	1    10800 1400
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5DFA40CF
P 10800 1400
F 0 "#FLG0103" H 10800 1475 50  0001 C CNN
F 1 "PWR_FLAG" H 10800 1573 50  0000 C CNN
F 2 "" H 10800 1400 50  0001 C CNN
F 3 "~" H 10800 1400 50  0001 C CNN
	1    10800 1400
	1    0    0    1   
$EndComp
$Comp
L Device:LED_Dual_ACA D?
U 1 1 5E0FB46D
P 8850 5400
F 0 "D?" V 8896 5190 50  0000 R CNN
F 1 "LED_Dual_ACA" V 8805 5190 50  0000 R CNN
F 2 "" H 8850 5400 50  0001 C CNN
F 3 "~" H 8850 5400 50  0001 C CNN
	1    8850 5400
	0    -1   -1   0   
$EndComp
$Comp
L RemoteCable2-rescue:ESP32DEV(DOIT)-MCU_Module U1
U 1 1 5DF68167
P 8050 3100
F 0 "U1" H 8075 4115 50  0000 C CNN
F 1 "ESP32DEV(DOIT)-MCU_Module" H 8075 4024 50  0000 C CNN
F 2 "Module:MODULE_ESP32DEV(DOIT)" H 8250 3250 50  0001 C CNN
F 3 "" H 8250 3250 50  0001 C CNN
	1    8050 3100
	1    0    0    -1  
$EndComp
NoConn ~ 8650 3450
Wire Wire Line
	8750 4700 8750 3250
Wire Wire Line
	8750 3250 8650 3250
$EndSCHEMATC