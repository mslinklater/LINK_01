
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

#define PIN_S0 0
#define PIN_OE1 1
#define PIN_OE2 2
#define PIN_G 3
#define PIN_E 4
#define PIN_C 5
#define PIN_A 6
#define PIN_QA 7
#define PIN_CLR 8

#define PIN_SR 9
#define PIN_CLK 10
#define PIN_B 11
#define PIN_D 12
#define PIN_F 13
#define PIN_H 14
#define PIN_QH 15
#define PIN_SL 16
#define PIN_S1 17

int pin[18] = {
  52, 50, 48, 46, 44, 42, 40, 38, 36,
  37, 39, 41, 43, 45, 47, 49, 51, 53
};

void setup()
{
  Serial.begin(112500);

  // pin directions
  pinMode(pin[PIN_S0], OUTPUT);
  pinMode(pin[PIN_OE1], OUTPUT);
  pinMode(pin[PIN_OE2], OUTPUT);
  pinMode(pin[PIN_CLR], OUTPUT);
  pinMode(pin[PIN_SR], OUTPUT);
  pinMode(pin[PIN_CLK], OUTPUT);
  pinMode(pin[PIN_SL], OUTPUT);
  pinMode(pin[PIN_S1], OUTPUT);
  pinMode(pin[PIN_QA], INPUT);
  pinMode(pin[PIN_QH], INPUT);

  set_bus(INPUT);  
}

void set_bus(int value)
{
  pinMode(pin[PIN_A], value);
  pinMode(pin[PIN_B], value);
  pinMode(pin[PIN_C], value);
  pinMode(pin[PIN_D], value);
  pinMode(pin[PIN_E], value);
  pinMode(pin[PIN_F], value);
  pinMode(pin[PIN_G], value);
  pinMode(pin[PIN_H], value);
}

void set_bus_value(int value)
{
  digitalWrite(pin[PIN_A], value & 0x01);
  digitalWrite(pin[PIN_B], value & 0x02);
  digitalWrite(pin[PIN_C], value & 0x04);
  digitalWrite(pin[PIN_D], value & 0x08);
  digitalWrite(pin[PIN_E], value & 0x10);
  digitalWrite(pin[PIN_F], value & 0x20);
  digitalWrite(pin[PIN_G], value & 0x40);
  digitalWrite(pin[PIN_H], value & 0x80);
}

int read_bus_value()
{
  int out = 0;
  out += digitalRead(pin[PIN_A]) == HIGH ? 0x01 : 0;
  out += digitalRead(pin[PIN_B]) == HIGH ? 0x02 : 0;
  out += digitalRead(pin[PIN_C]) == HIGH ? 0x04 : 0;
  out += digitalRead(pin[PIN_D]) == HIGH ? 0x08 : 0;
  out += digitalRead(pin[PIN_E]) == HIGH ? 0x10 : 0;
  out += digitalRead(pin[PIN_F]) == HIGH ? 0x20 : 0;
  out += digitalRead(pin[PIN_G]) == HIGH ? 0x40 : 0;
  out += digitalRead(pin[PIN_H]) == HIGH ? 0x80 : 0;
  
  return out;
}

void clock()
{
  digitalWrite(pin[PIN_CLK], LOW);
  digitalWrite(pin[PIN_CLK], HIGH);
}

void load()
{
  digitalWrite(pin[PIN_CLR], HIGH);
  digitalWrite(pin[PIN_S1], HIGH);
  digitalWrite(pin[PIN_S0], HIGH);
  clock();
}

void hold()
{
  digitalWrite(pin[PIN_CLR], HIGH);
  digitalWrite(pin[PIN_S0], LOW);
  digitalWrite(pin[PIN_S1], LOW);
  digitalWrite(pin[PIN_OE1], LOW);
  digitalWrite(pin[PIN_OE2], LOW);
}

void left()
{
  digitalWrite(pin[PIN_CLR], HIGH);
  digitalWrite(pin[PIN_S1], HIGH);
  digitalWrite(pin[PIN_S0], LOW);
  digitalWrite(pin[PIN_OE1], LOW);
  digitalWrite(pin[PIN_OE2], LOW);
//  digitalWrite(pin[PIN_SL], HIGH);
  clock();  
}

void right()
{
  digitalWrite(pin[PIN_CLR], HIGH);
  digitalWrite(pin[PIN_S1], LOW);
  digitalWrite(pin[PIN_S0], HIGH);
  digitalWrite(pin[PIN_OE1], LOW);
  digitalWrite(pin[PIN_OE2], LOW);
//  digitalWrite(pin[PIN_SR], HIGH);
  clock();  
}

void read_random_value()
{
  // set bus to random value
  
  int write_value = random(0,256);
  
  set_bus(OUTPUT);
  set_bus_value(write_value);
  
  load();
  
  // hold the value
  hold();
    
  // set bus to write
  set_bus(INPUT);
  
  // roll value and rebuild number
  int read_value = 0;
  for(int i=0 ; i<8 ; i++)
  {
    read_value <<= 1;
    read_value += digitalRead(pin[PIN_H]) == HIGH ? 1 : 0;
    right();
  }
  
  char buffer[32];
  sprintf(buffer, "bus write %02x shift read %02x", write_value, read_value);  
  Serial.println(buffer);
}

void write_random_value()
{
  set_bus(INPUT);

  int write_value = random(0,256);
  
  // shift in a value

  for(int i=0 ; i<8 ; i++)
  {
    digitalWrite(pin[PIN_SR], (write_value & (0x80>>i)) == 0 ? LOW : HIGH );
    right();
  }
  
  // read value from bus
  int read_value = read_bus_value();

  char buffer[32];
  sprintf(buffer, "shift write %02x bus read %02x", write_value, read_value);
  Serial.println(buffer);
}

void loop()
{
  Serial.println("---");
  read_random_value();
  write_random_value();
  delay(1000);
}
