/*
  SN74F299N explorer
  */

/*
MODE  CLR S1  S0  OE1 OE2 CLK SL  SR  QA  QB  QC  QD  QE  QF  QG  QH  QA' QH'

Clear L   X   L   L   L   X   X   X   L   L   L   L   L   L   L   L   L   L
      L   L   X   L   L   X   X   X   L   L   L   L   L   L   L   L   L   L
      L   H   H   X   X   X   X   X   X   X   X   X   X   X   X   X   L   L
      
Hold  H   L   L   L   L   X   X   X   QA0 QB0 QC0 QD0 QE0 QF0 QG0 QH0 QA0 QH0
      H   X   X   L   L   L   X   X   QA0 QB0 QC0 QD0 QE0 QF0 QG0 QH0 QA0 QH0
      
Shift H   L   H   L   L   ^   X   H   H   QAn QBn QCn QDn QEn QFn QGn H   QGn
Right H   L   H   L   L   ^   X   L   L   QAn QBn QCn QDn QEn QFn QGn L   QGn

Shift H   H   L   L   L   ^   H   X   QBn QCn QDn QEn QFn QGn QHn H   QBn H
Left  H   H   L   L   L   ^   L   X   QBn QCn QDn QEn QFn QGn QHn L   QBn L

Load  H   H   H   X   X   ^   X   X   a   b   c   d   e   f   g   h   a   h 
*/

int pin_S0 = 52;
int pin_OE1 = 53;
int pin_OE2 = 50;
int pin_QG = 51;
int pin_QE = 48;
int pin_QC = 49;
int pin_QA = 46;
int pin_QAcomp = 47;
int pin_CLR = 44;

int pin_S1 = 38;
int pin_SL = 39;
int pin_QHcomp = 36;
int pin_QH = 37;
int pin_QF = 34;
int pin_QD = 35;
int pin_QB = 32;
int pin_CLK = 33;
int pin_SR = 30;



void setup()
{
  // chip inputs
  pinMode(pin_S0, OUTPUT);
  pinMode(pin_S1, OUTPUT);
  pinMode(pin_OE1, OUTPUT);
  pinMode(pin_OE2, OUTPUT);
  pinMode(pin_CLR, OUTPUT);
  pinMode(pin_CLK, OUTPUT);
  pinMode(pin_SL, OUTPUT);
  pinMode(pin_SR, OUTPUT);
  
  // chip outputs
  pinMode(pin_QAcomp, INPUT);
  pinMode(pin_QHcomp, INPUT);
  
  // All 8 Q pins are R/W
}

void loop()
{
}



