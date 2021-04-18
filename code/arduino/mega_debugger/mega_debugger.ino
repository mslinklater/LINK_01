#include <LiquidCrystal.h>

#define NUM_READ_PINS 32
#define NUM_DELAY_VALUES 4
#define NUM_DISPLAY_MODES 2

const int rs=8, en=9, d4=10, d5=11, d6=12, d7=13;

const int read_pins[NUM_READ_PINS] = { 
  23, 25, 27, 29, 31, 33, 35, 37,
  39, 41, 43, 45, 47, 49, 51, 53,
  22, 24, 26, 28, 30, 32, 34, 36,
  38, 40, 42, 44, 46, 48, 50, 52 };

const int button1_pin = 7;
const int button2_pin = 6;
const int button3_pin = 5;

// other debug pins
const int rw_pin = 16;
const int cpu_be_pin = 17;
const int clock_pin = 18;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int displayMode = 0;
int delayMode = 0;
int delayValues[NUM_DELAY_VALUES] = { 0, 100, 500, 1000 };

String command = "";

void setup()
{
  // input pins
  for(int i=0 ; i<NUM_READ_PINS ; i++)
  {
    pinMode(read_pins[i], INPUT);
  }

  // button pins
  pinMode(button1_pin, INPUT);
  pinMode(button2_pin, INPUT);
  pinMode(button3_pin, INPUT);

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
  lcd.print(digitalRead(read_pins[clock_pin]) == HIGH ? "+ " : "- "); 
  lcd.print(digitalRead(read_pins[rw_pin]) == HIGH ? "R " : "W "); 
  lcd.print(digitalRead(read_pins[cpu_be_pin]) == HIGH ? "Be" : "B-"); 

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

void display()
{
  if(command.length() > 0)
  {
    // display command
    lcd.begin(16,2);
    lcd.print(command);
    delay(1000);
    command = "";
  }
  
  // display to LCD
  switch(displayMode)
  {
  case 0:
    draw_raw();
    break;
  case 1:
    draw_hex();
    break;
  }
}

void loop()
{
  static int last_button1 = false;
  static int last_button2 = false;
  static int last_button3 = false;
  
  // read button 1
  int val = digitalRead(button1_pin);
  if((val == HIGH) && (last_button1 == LOW))
  {
    displayMode++;
    if(displayMode >= NUM_DISPLAY_MODES)
      displayMode = 0;
    switch(displayMode)
    {
      case 0: command="Display - RAW"; break;
      case 1: command="Display - BUS"; break;
    }
  }
  last_button1 = val;

  // read button 3
  val = digitalRead(button3_pin);
  if((val == HIGH) && (last_button3 == LOW))
  {
    delayMode++;
    if(delayMode > NUM_DELAY_VALUES)
      delayMode = 0;
    switch(delayMode)
    {
      case 0: command="Delay - 0ms"; break;
      case 1: command="Delay - 100ms"; break;
      case 2: command="Delay - 500ms"; break;
      case 3: command="Delay - 1000ms"; break;
    }
  }
  last_button3 = val;

  display();
  
  // delay between updates
  delay(delayValues[delayMode]);
}

