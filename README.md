# LINK_01
The LINK_01 machine

## What is LINK_01 ?

LINK_01 is my first hombrew computer. At the moment I'm not sure it will work... but I hope it will.

## Key Features

* To explore 8-bit CPU technology by leveraging modern cheap microcontrollers.
* To be fully software upgradeable
* To let the microcontroller do the heavy lifting with I/O
* To use modern compiler and debugging tools
* To have fun programming the 6502

# Starting the monitor

> minicom -b 115200 -o -D /dev/serial0

ctrl-a q to quit

# Writing the EEPROM

> minipro -p AT28C64B -w ROMFILE

# Outputting a ROM

> hexdump -C FILE

# Raspberry Pi pins

|pin|use|
|---|---|
|6|GND (board)|
|8|UART-TX|
|10|UART-RX|
|18|SWDIO|
|20|GND|
|22|SWCLK|

# Pico pins

|use|GPIO|pin||pin|GPIO|use|
|---|---|---|---|---|---|---|
|UART TX|0|1|###|40|-|5V IN|
|UART RX|1|2|###|39|-||
|GND|-|3|###|38|-|GND|
||2|4|###|37|-||
||3|5|###|36|-||
||4|6|###|35|-||
||5|7|###|34|28|6502 PHI-2|
|GND|-|8|###|33|-|GND|
||6|9|###|32|27|6502 RESB|
||7|10|###|31|26|6502 BE|
||8|11|###|30|-||
||9|12|###|29|22|6502 IRQB|
|GND|-|13|###|28|-|GND|
|6502 RWB|10|14|###|27|21|6502 NMIB|
|SHIFTER OUT|11|15|###|26|20|SHIFTER OE|
|SHIFTER IN|12|16|###|25|19|SHIFTER S0|
|VGA-B|13|17|###|24|18|SHIFTER S1|
|GND|-|18|###|23|-|GND|
|VGA-G|14|19|###|22|17|VGA v-sync|
|VGA-R|15|20|###|21|16|VGA h-sync|

Pin counts (available 28)

UART 2
VGA 5
6502 5
Shifter 5

# VGA pins

|pin|use|
|---|---|
|1|R|
|2|G|
|3|B|
|4|-|
|5|GND|
|6|GND|
|7|GND|
|8|GND|
|9|-|
|10|GND|
|11|-|
|12|-|
|13|H-SYNC|
|14|V-SYNC|
|15|-|

# 65c02 pins

|use|pin||pin|use|
|---|---|---|---|---|
|VPB|1|XXX|40|RESB|
|RDY|2|XXX|39|PHI2O|
|PHI1O|3|XXX|38|SOB|
|IRQB|4|XXX|37|PHI2|
|MLB|5|XXX|36|BE|
|NMIB|6|XXX|35|NC|
|SYNC|7|XXX|34|RWB|
|VDD|8|XXX|33|D0|
|A0|9|XXX|32|D1|
|A1|10|XXX|31|D2|
|A2|11|XXX|30|D3|
|A3|12|XXX|29|D4|
|A4|13|XXX|28|D5|
|A5|14|XXX|27|D6|
|A6|15|XXX|26|D7|
|A7|16|XXX|25|A15|
|A8|17|XXX|24|A14|
|A9|18|XXX|23|A13|
|A10|19|XXX|22|A12|
|A11|20|XXX|21|VSS|

# Voltage Shifter 1 - TSX0108E

|pin|function|
|---|---|
|1|6502 PHI2|
|2|6502 RESB|
|3|6502 BE|
|4|6502 IRQB|
|5|6502 NMIB|
|6|SHIFTER OE|
|7|SHIFTER S0|
|8|SHIFTER S1|

# Voltage Shifter 2 - TSX0108E

|pin|function|
|---|---|
|1|SHIFTER IN|
|2|SHIFTER OUT|
|3|6502 RWB|
|4||
|5||
|6||
|7||
|8||

# Shift register - SN74F299N

|use|pin|---|pin|use|
|---|---|---|---|---|
||1|###|20||
||2|###|19||
||3|###|18||
||4|###|17||
||5|###|16||
||6|###|15||
||7|###|14||
||8|###|13||
||9|###|12||
||10|###|11||

# AT28C64B EEPROM

|pin|num|---|num|pin|
|---|---|---|---|---|
|NC|1|###|28|VCC|
|A12|2|###|27|~WE|
|A7|3|###|26|NC|
|A6|4|###|25|A8|
|A5|5|###|24|A9|
|A4|6|###|23|A11|
|A3|7|###|22|~OE|
|A2|8|###|21|A10|
|A1|9|###|20|~CE|
|A0|10|###|19|I/O7|
|I/O0|11|###|18|I/O6|
|I/O1|12|###|17|I/O5|
|I/O2|13|###|16|I/O4|
|GND|14|###|15|I/O3|

# AS6C6264 8K RAM

