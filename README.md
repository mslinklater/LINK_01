# LINK_01
The LINK_01 machine
# Starting the monitor

> minicom -b 115200 -o -D /dev/serial0

ctrl-a q to quit

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
||9|12|###|29|22||
|GND|-|13|###|28|-|GND|
||10|14|###|27|21||
||11|15|###|26|20||
||12|16|###|25|19||
|VGA-B|13|17|###|24|18||
|GND|-|18|###|23|-|GND|
|VGA-G|14|19|###|22|17|VGA v-sync|
|VGA-R|15|20|###|21|16|VGA h-sync|

# VGA pins

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

# Voltage Shifter 1

|pin|function|
|---|---|
|1|6502 PHI2|
|2|6502 RESB|
|3|6502 BE|
|4||
|5||
|6||
|7||
|8||

