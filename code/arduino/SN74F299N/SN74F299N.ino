/*
  SN74F299N explorer
  */

/*
MODE  CLR S1  S0  OE1 OE2 CLK SL  SR  QA  QB  QC  QD  QE  QF  QG  QH  QA' QH'

Clear L   X   L   L   L   X   X   X   L   L   L   L   L   L   L   L   L   L
      L   L   X   L   L   X   X   X   L   L   L   L   L   L   L   L   L   L
      L   H   H   X   X   X   X   X   X   X   X   X   X   X   X   X   L   L
      
Hold  H   L   L   L   L   X   X   X   QA0 QB0 QC0 QD0 QE0 QF0 QG0 QH0 QA0 QH0
      H   X   X   L   L   L   X   X   QA0 QB0 QC0 QD0 QE0 QF0 QG0 QH0 QA0 QH0   <
      
Shift H   L   H   L   L   ^   X   H   H   QAn QBn QCn QDn QEn QFn QGn H   QGn
Right H   L   H   L   L   ^   X   L   L   QAn QBn QCn QDn QEn QFn QGn L   QGn

Shift H   H   L   L   L   ^   H   X   QBn QCn QDn QEn QFn QGn QHn H   QBn H     <
Left  H   H   L   L   L   ^   L   X   QBn QCn QDn QEn QFn QGn QHn L   QBn L     <

Load  H   H   H   X   X   ^   X   X   a   b   c   d   e   f   g   h   a   h     <
*/

int pin_S0 = 23;
int pin_S1 = 25;

int pin_OE = 27;

int pin_SHIFT_IN = 29;

int pin_CLK = 51;

int clock = 0;
int pause = 10;

void setup()
{
  Serial.begin(9600);
  
  pinMode(pin_S0, OUTPUT);
  pinMode(pin_S1, OUTPUT);
  pinMode(pin_OE, OUTPUT);
  pinMode(pin_CLK, OUTPUT);
  pinMode(pin_SHIFT_IN, OUTPUT);
  
}

void clear()  // we never need this...
{
  Serial.println("clear");
  set_output();
  left();
  for(int i=0 ; i<24 ; i++)
  {
    shift(0, 0);
  }
}

void set_input()
{
  digitalWrite(pin_OE, HIGH);
}

void set_output()
{
  digitalWrite(pin_OE, LOW);
}

void tick(int t)
{
  if(clock == 0)
  {
    digitalWrite(pin_CLK, LOW);
    clock = 1;
  }
  else
  {
    digitalWrite(pin_CLK, HIGH);
    clock = 0;
  }
  delay(t);
}

void left()
{
  digitalWrite(pin_S1, HIGH);
  digitalWrite(pin_S0, LOW);
}

void right()
{
  digitalWrite(pin_S1, LOW);
  digitalWrite(pin_S0, HIGH);
}

void shift(int value, int t)
{
  digitalWrite(pin_SHIFT_IN, value);
  tick(t);
  tick(t);  
}

int value = 0;

void set_value(int data, int addr, int t)
{
  set_input();
  left();
  for(int i=0 ; i<16 ; i++)
  {
    if(addr & (1<<i))
      shift(1, 0);
    else
      shift(0, 0);
  }
  for(int i=0 ; i<8 ; i++)
  {
    if(data & (1<<i))
      shift(1, 0);
    else
      shift(0, 0);
  }  
  set_output();
  delay(t);
}

int dataval = 0;
int addrval = 0;

void loop()
{
  set_value(dataval, addrval, 100);
  dataval--;
  addrval++;
  
  /*
  left();
  for(int i=0 ; i<8 ; i++)
  {
    shift(1, pause);
  }
  for(int i=0 ; i<24 ; i++)
  {
    shift(0, pause);
  }
  right();
  for(int i=0 ; i<8 ; i++)
  {
    shift(1, pause);
  }
  for(int i=0 ; i<24 ; i++)
  {
    shift(0, pause);
  }
  */
}
