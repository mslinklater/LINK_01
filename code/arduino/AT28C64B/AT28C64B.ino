/* EEPROM AT28C64B */

// 13 address lines = 8K
int pin_A[13] = {29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53};

// 8 data lines
int pin_D[8] = {2, 3, 4, 5, 6, 7, 8, 9};

int pin_CE = 27;
int pin_OE = 25;
int pin_WE = 23;

void set_data_read()
{
  // set data to read
  for(int i=0 ; i<8 ; i++)
  {
    pinMode(pin_D[i], INPUT);
  }
}

void set_data_write()
{
  // set data to write
  for(int i=0 ; i<8 ; i++)
  {
    pinMode(pin_D[i], OUTPUT);
  }
}

void writebytes()
{
  digitalWrite(pin_CE, HIGH);
  digitalWrite(pin_OE, HIGH);
  digitalWrite(pin_WE, HIGH);

  set_data_write();  

  delay(100);
  
  // write some data to the EEPROM
  for(int i=0 ; i<256 ; i++)
  {
    // set up the data bits
    for(int b=0 ; b<8 ; b++)
    {
      digitalWrite(pin_D[b], i & (1 << b) ? HIGH : LOW);
    }
    // set up the address bits
    for(int b=0 ; b<13 ; b++)
    {
      digitalWrite(pin_A[b], i & (1 << b) ? HIGH : LOW);
    }
    digitalWrite(pin_WE, LOW);
    digitalWrite(pin_WE, HIGH);
    delay(1);
  }
}

void readbytes()
{
  set_data_read();
  
  digitalWrite(pin_CE, LOW);
  digitalWrite(pin_OE, LOW);
  digitalWrite(pin_WE, HIGH);
  
  for(int b=0 ; b<8192 ; b++)
  {
    // set address
    for(int addresspin=0 ; addresspin<13 ; addresspin++)
    {
      if(b & (1 << addresspin))
        digitalWrite(pin_A[addresspin], HIGH);
      else
        digitalWrite(pin_A[addresspin], LOW);
    }
    // read data
    int val = 0;
    for(int datapin=0 ; datapin<8 ; datapin++)
    {
      if(digitalRead(pin_D[datapin]))
        val += 1 << datapin;
    }
    
    char buffer[256];
    sprintf(buffer, "%04x %02x\n", b, val);
    Serial.print(buffer);
  }
}

void setup() 
{
  Serial.begin(9600);
  delay(2000);
  
  for(int i=0 ; i<13 ; i++)
  {
    pinMode(pin_A[i], OUTPUT);
  }
  
  pinMode(pin_CE, OUTPUT);
  pinMode(pin_OE, OUTPUT);
  pinMode(pin_WE, OUTPUT);

//  writebytes();
  readbytes();
}


void loop() {
}
