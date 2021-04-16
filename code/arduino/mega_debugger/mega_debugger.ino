#include <LiquidCrystal.h>

#define NUM_READ_PINS 32

const int rs=8, en=9, d4=10, d5=11, d6=12, d7=13;

const int read_pins[32] = { 23, 25, 27, 29, 31, 33, 35, 37,
                        39, 41, 43, 45, 47, 49, 51, 53,
                        22, 24, 26, 28, 30, 32, 34, 36,
                        38, 40, 42, 44, 46, 48, 50, 52 };

const int button_pin = 7;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int displayMode = 1;

void setup()
{
  // input pins
  for(int i=0 ; i<NUM_READ_PINS ; i++)
  {
    pinMode(read_pins[i], INPUT);
  }
  // button pin
  pinMode(button_pin, INPUT);
  
//  lcd.begin(16,2);
//  lcd.print("First Line");
//  lcd.setCursor(0,1);
//  lcd.print("Second Line");
  lcd.begin(16,2);
}

void draw_hex()
{
  lcd.setCursor(0,0);
  
  int pin=0;
  char buffer [16];

  // address
  lcd.print("A:0x");  
  for(int nibble=0 ; nibble<4 ; nibble++)
  {
    int val = 0;
    for(int bit=0 ; bit < 4 ; bit++)
    {
      val <<= 1;
      val = val + (digitalRead(read_pins[pin]) == HIGH ? 1 : 0);
      pin++;
    }
    sprintf(buffer, "%X", val);
    lcd.print(buffer);
  }
  
  // data
  pin = 24;
  lcd.print(" D:0x");  
  for(int nibble=0 ; nibble<2 ; nibble++)
  {
    int val = 0;
    for(int bit=0 ; bit < 4 ; bit++)
    {
      val <<= 1;
      val = val + (digitalRead(read_pins[pin]) == HIGH ? 1 : 0);
      pin++;
    }
    sprintf(buffer, "%X", val);
    lcd.print(buffer);
  }
  
  // R/W
  lcd.setCursor(0,1);
  if(digitalRead(read_pins[16]) == HIGH)
  {
    lcd.print("READ");
  }
  else
  {
    lcd.print("WRITE");
  }
}

void draw_raw()
{
  // draw raw inputs on 32 pins
  
  lcd.setCursor(0,0);
  for(int i=0 ; i<NUM_READ_PINS/2 ; i++)
  {
    if(digitalRead(read_pins[i]) == HIGH)
    {
      lcd.print("O");
    }
    else
    {
      lcd.print("-");
    }
  }
  lcd.setCursor(0,1);
  for(int i=NUM_READ_PINS/2 ; i<NUM_READ_PINS ; i++)
  {
    if(digitalRead(read_pins[i]) == HIGH)
    {
      lcd.print("O");
    }
    else
    {
      lcd.print("-");
    }
  }
}

void loop()
{
  static int last_button = false;
  // read button

  if((digitalRead(button_pin) == HIGH) && !last_button)
  {
    displayMode++;
    if(displayMode > 1)
      displayMode = 0;
    lcd.begin(16,2);
  }
  last_button = digitalRead(button_pin);
  
  // read input pins
  switch(displayMode)
  {
    case 0:
      draw_raw();
      break;
    case 1:
      draw_hex();
      break;
  }
  // 
  delay(100);
}
