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

int pin_S0 = 52;
int pin_OE1 = 53;
//int pin_OE2 = 50;
int pin_QAcomp = 47;
//int pin_CLR = 44;

int pin_S1 = 38;
int pin_SL = 39;
//int pin_QHcomp = 36;
int pin_CLK = 33;
//int pin_SR = 30;

int clock = 0;

void setup()
{
  Serial.begin(9600);
  
  // chip inputs
  pinMode(pin_S0, OUTPUT);
  pinMode(pin_S1, OUTPUT);
  pinMode(pin_OE1, OUTPUT);
//  pinMode(pin_OE2, OUTPUT);
//  pinMode(pin_CLR, OUTPUT);
  pinMode(pin_CLK, OUTPUT);
  pinMode(pin_SL, OUTPUT);
  //pinMode(pin_SR, OUTPUT);
  
  // chip outputs
  pinMode(pin_QAcomp, INPUT);
  //pinMode(pin_QHcomp, INPUT);
  
  // All 8 Q pins are R/W
}

void clear()  // we never need this...
{
  Serial.println("clear");
//  digitalWrite(pin_CLR, LOW);
  digitalWrite(pin_S0, HIGH);
  digitalWrite(pin_S1, HIGH);
//  digitalWrite(pin_QAcomp, LOW);
//  digitalWrite(pin_QHcomp, LOW);
  digitalWrite(pin_OE1, HIGH);
//  digitalWrite(pin_OE2, HIGH);
  delay(1);
}

void set_input()
{
  digitalWrite(pin_OE1, HIGH);
//  digitalWrite(pin_OE2, HIGH);
}

void set_output()
{
  digitalWrite(pin_OE1, LOW);
//  digitalWrite(pin_OE2, LOW);
}

void tick()
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
  delay(20);
}

void left(int value)
{
//  digitalWrite(pin_CLR, HIGH);
  digitalWrite(pin_S1, HIGH);
  digitalWrite(pin_S0, LOW);
  digitalWrite(pin_SL, value);
  tick();
  tick();
}

//void right(int value)
//{
//  digitalWrite(pin_CLR, HIGH);
//  digitalWrite(pin_S1, LOW);
//  digitalWrite(pin_S0, HIGH);
//  digitalWrite(pin_SR, value);
//  tick();
//  tick();
//}

int value = 0;

void loop()
{
  set_output();
  left(1);
  left(1);
  left(1);
  left(1);
  left(1);
  left(1);
  left(1);
  left(1);
  left(0);
  left(0);
  left(0);
  left(0);
  left(0);
  left(0);
  left(0);
  left(0);
//  right(0);
//  right(0);
//  right(0);
//  right(0);
//  right(0);
//  right(0);
//  right(0);
//  right(0);
}
