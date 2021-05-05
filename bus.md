# 5V Bus

|ID|Count|Description|
|---|---|---|
|GND|1|Ground 0V - VDD|
|5V|1|5V Supply - VCC|
|A0-A15|16|Address lines 0-15|
|D0-D7|8|Data lines 0-7|
|R/~W|1|Rear/Write - from 6502 or Pico|
|~R|1|Read pulse|
|~W|1|Write pulse|
|CLK|1|Clock - from Pico|
|RESET|1|6502 Reset - from Pico|
|NMIB|1|Non-maskable interrupt - pulled up|
|IRQB|1|Interrupt request - pulled up|
|FREE|3|Left to assign|
|TOTAL|36|Max lines on the veroboard|

If things become tight the ~R and ~W channels could be retired. This would mean those signals would need to be generated locally per module rather than as part of the 6502 module.

# 3V3 Bus

|ID|Count|Description|
|---|---|---|
|GND|1|Ground 0V VDD|
|3V3|1|3.3V Supply VCC|
|B0-B15|16|General purpose signals|
|TOTAL|18||
