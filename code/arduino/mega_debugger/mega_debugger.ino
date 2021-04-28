#include <LiquidCrystal.h>

#define NUM_READ_PINS 32
#define NUM_DELAY_VALUES 4
#define NUM_DISPLAY_MODES 2
#define NUM_BUTTONS 3
#define BUTTON_DEBOUNCE 50
#define CLOCK_PIN 2

#define LCD_RS 8
#define LCD_EN 9
#define LCD_D4 10
#define LCD_D5 11
#define LCD_D6 12
#define LCD_D7 13

const String mnemonics[256] = {
  "BRK", "ORA(zp,x)", "", "", "TSB zp", "ORA zp", "ASL zp", "RMB0 zp", "PHP", "ORA #", "ASL A", "", "TSB a", "ORA $", "ASL $", "BBR0 r",
  "BPL r", "ORA (zp),y", "ORA (zp)", "", "TRB zp", "ORA zp,x", "ASL zp,x", "RMB1 zp", "CLC", "ORA $,y", "INC A", "", "TRB $", "ORA $,x", "ASL $,x", "BBR1 r",
  "JSR a", "AND (zp,x)", "", "", "BIT zp", "AND zp", "ROL zp", "RMB2 zp", "PLP", "AND #", "ROL A", "", "BIT $", "AND $", "ROL $", "BBR2 r",
  "BMI r", "AND (zp),y", "AND (zp)", "", "BIT zp,x", "AND zp,x", "ROL zp,x", "RMB3 zp", "SEC I", "AND $,y", "DEC A", "", "BIT $,x", "AND $,x", "ROL $,x", "BBR3 r",
  "RTI s", "EOR (zp,x)", "", "", "", "EOR zp", "LSR zp", "RMB4 zp", "PHA", "EOR #", "LSR A", "", "JMP $", "EOR $", "LSR $", "BBR4 r",
  "BVC r", "EOR (zp),y", "EOR (zp)", "", "", "EOR zp,x", "LSR zp,x", "RMB5 zp", "CLI", "EOR $,y", "PHY", "", "", "EOR $,x", "LSR $", "BBR5 r",
  "RTS s", "ADC (zp,x)", "", "", "STZ zp", "ADC zp", "ROR zp", "RMB6 zp", "PLA", "ADC #", "ROR A", "", "JMP ($)", "ADC $", "ROR $", "BBR6 r",
  "BVS r", "ADC (zp),y", "ADC (zp)", "", "STZ zp,x", "ADC zp,x", "ROR zp,x", "RMB7 zp", "SEI", "ADC $,y", "PLY", "", "JMP ($.x)", "ADC $,x", "ROR $,x", "BBR7 r",
  "BRA r", "STA (zp,x)", "", "", "STY zp", "STA zp", "STZ zp", "SMB0 zp", "DEY", "BIT #", "TXA", "", "STY $", "STA $", "STX $", "BBS0 r",
  "BCC r", "STA (zp),y", "STA (zp)", "", "STY zp,x", "STA zp,x", "STZ zp,y", "SMB1 zp", "TYA", "STA $,y", "TSX", "", "STZ $", "STA $,x", "STZ $,x", "BBS1 r",
  "LDY #", "LDA (zp,x)", "LDX #", "", "LDY zp", "LDA zp", "LDX zp", "SMB2 zp", "TAY", "LDA #", "TAX", "", "LDY $", "LDA $", "LDX $", "BBS2 r",
  "BCS r", "LDA (zp),y", "LDA (zp)", "", "LDY zp,x", "LDA zp,x", "LDX zp,y", "SMB3 zp", "CLV", "LDA A,y", "TSX", "", "LDY $,x", "LDA $,x", "LDX $,x", "BBS3 r",
  "CPY #", "CMP (zp,x)", "", "", "CPY zp", "CMP zp", "DEC zp", "SMB4 zp", "INY", "CMP #", "DEX", "WAI", "CPY $", "CMP $", "DEC $", "BBS4 r",
  "BNE r", "CMP (zp),y", "CMP (zp)", "", "", "CMP zp,x", "DEC zp,x", "SMB5 zp", "CLD", "CMP $,y", "PHX", "STP", "", "CMP $,x", "DEC $,x", "BBS5 r",
  "CPX #", "SBC (zp,x)", "", "", "CPX zp", "SBC zp", "INC zp", "SMB6 zp", "INX", "SBC #", "NOP", "", "CPX $", "SBC $", "INC $", "BBS6 r",
  "BEQ r", "SBC (zp),y", "SBC (zp)", "", "", "SBC zp,x", "INC zp,x", "SMB7 zp", "SED", "SBC $,y", "PLX", "", "", "SBC $,x", "INC $,x", "BBS7 r"
};

// input pins
const int read_pins[NUM_READ_PINS] = { 
  23, 25, 27, 29, 31, 33, 35, 37,
  39, 41, 43, 45, 47, 49, 51, 53,
  22, 24, 26, 28, 30, 32, 34, 36,
  38, 40, 42, 44, 46, 48, 50, 52 };

#define RW_PIN 24
#define SYNC_PIN 25
#define CPU_BE_PIN 26

int cached_read_pins[NUM_READ_PINS];

// button pins
const int button_pins[NUM_BUTTONS] = {
  7, 6, 5};
int last_button_state[NUM_BUTTONS] = {
  LOW, LOW, LOW};
unsigned long button_debounce[NUM_BUTTONS];

// clock interrupt

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

int displayMode = 0;

String command = "";

void setup()
{
  // input pins
  for(int i=0 ; i<NUM_READ_PINS ; i++)
  {
    pinMode(read_pins[i], INPUT);
  }

  // button pins
  for(int i=0 ; i<NUM_BUTTONS ; i++)
  {
    pinMode(button_pins[i], INPUT);
  }

  // clear LCD
  lcd.begin(16,2);

  // clock interrupt
  pinMode(CLOCK_PIN, INPUT);
  attachInterrupt(0, onClock, RISING);

  Serial.begin(115200);
}

void onClock()
{
  display();
}

void draw_hex()
{
  lcd.setCursor(0,0);

  int pin=0;
  char buffer [32];

  // address
  int addrVal = 0;
//  int iVal = 0;
  for(int nibble=0 ; nibble<4 ; nibble++)
  {
//    val[iVal] = 0;
    for(int bit=0 ; bit < 4 ; bit++)
    {
      addrVal <<= 1;
      addrVal += cached_read_pins[pin] == HIGH ? 1 : 0;
      pin++;
    }
//    iVal++;
  }

  // data
  pin = 16;
  int dataVal = 0;
  for(int nibble=0 ; nibble<2 ; nibble++)
  {
    for(int bit=0 ; bit < 4 ; bit++)
    {
      dataVal <<= 1;
      dataVal += cached_read_pins[pin] == HIGH ? 1 : 0;
      pin++;
    }
  }
  sprintf(buffer, "A:0x%04X D:0x%02X ", addrVal, dataVal);
  lcd.print(buffer);
  Serial.print(buffer);

  String instruction = "          ";
  if(digitalRead(read_pins[SYNC_PIN]) == HIGH)
  {
    instruction = mnemonics[dataVal];
  }
  else
  {
    switch(addrVal)
    {
      case 0xfffc:
      case 0xfffd:
        instruction = "RESET";
        break;
    }
  }

  // R/W
  sprintf(buffer, "%s%s %s", digitalRead(read_pins[RW_PIN]) == HIGH ? "R" : "W",digitalRead(read_pins[CPU_BE_PIN]) == HIGH ? "B" : "b", instruction.c_str());
  lcd.setCursor(0,1);
  lcd.print(buffer); 
  Serial.println(buffer);
}

void draw_raw()
{
  char buffer [32];
  
  // draw raw inputs on 32 pins
  lcd.setCursor(0,0);
  sprintf(buffer, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
            cached_read_pins[0],
            cached_read_pins[1],
            cached_read_pins[2],
            cached_read_pins[3],
            cached_read_pins[4],
            cached_read_pins[5],
            cached_read_pins[6],
            cached_read_pins[7],
            cached_read_pins[8],
            cached_read_pins[9],
            cached_read_pins[10],
            cached_read_pins[11],
            cached_read_pins[12],
            cached_read_pins[13],
            cached_read_pins[14],
            cached_read_pins[15]);
  lcd.print(buffer);
  lcd.setCursor(0,1);
  sprintf(buffer, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
            cached_read_pins[16],
            cached_read_pins[17],
            cached_read_pins[18],
            cached_read_pins[19],
            cached_read_pins[20],
            cached_read_pins[21],
            cached_read_pins[22],
            cached_read_pins[23],
            cached_read_pins[24],
            cached_read_pins[25],
            cached_read_pins[26],
            cached_read_pins[27],
            cached_read_pins[28],
            cached_read_pins[29],
            cached_read_pins[30],
            cached_read_pins[31]);
  lcd.print(buffer);
 
}

void display()
{
  if(command.length() > 0)
    return;

  cache_pins();
  
  // display to LCD
  switch(displayMode)
  {
  case 0:
    draw_hex();
    break;
  case 1:
    draw_raw();
    break;
  }
}

void cache_pins()
{
  for(int i=0 ; i<NUM_READ_PINS ; i++)
  {
    cached_read_pins[i] = digitalRead(read_pins[i]);
  }
}

void loop()
{
  if(command.length() > 0)
  {
    // display command
    lcd.begin(16,2);
    lcd.print(command);
    delay(750);  // need to get rid of this too
    command = "";
  }

  // read button 1
  int val = digitalRead(button_pins[0]);
  if((val == HIGH) && (last_button_state[0] == LOW))
  {
    if(button_debounce[0] + BUTTON_DEBOUNCE < millis())
    {
      displayMode++;
      if(displayMode >= NUM_DISPLAY_MODES)
        displayMode = 0;
      switch(displayMode)
      {
      case 0: 
        command="Display - HEX"; 
        break;
      case 1: 
        command="Display - RAW"; 
        break;
      }
      button_debounce[0] = millis();
    }
  }
  last_button_state[0] = val;
  
  delay(10);
}




