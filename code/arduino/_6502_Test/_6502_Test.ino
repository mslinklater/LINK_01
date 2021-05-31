
//---------------------------------
// --- read only pins
//---------------------------------

// Address bus
#define A_0 9
#define A_1 10
#define A_2 11
#define A_3 12
#define A_4 13
#define A_5 14
#define A_6 15
#define A_7 16
#define A_8 17
#define A_9 18
#define A_10 19
#define A_11 20
#define A_12 22
#define A_13 23
#define A_14 24
#define A_15 25

// Vector pull
#define VPB 1

// Clock phase 1 out
#define PHI1O 3

// Clock phase 2 out
#define PHI2O 39

// Memory lock
#define MLB 5

// Syncronize with opcode fetch
#define SYNC 7

// Read/Write
#define RWB 34

//---------------------------------
// --- write only pins
//---------------------------------

// Interrupt request
#define IRQB 4

// Non-Maskable interrupt
#define NMIB 6

// Bus enable
#define BE 36

// Clock input
#define PHI2 37

// Set overflow
#define SOB 38

// Reset
#define RESB 40

//---------------------------------
// --- read/write pins
//---------------------------------

// Ready
#define RDY 2

// Data bus
#define D_7 26
#define D_6 27
#define D_5 28
#define D_4 29
#define D_3 30
#define D_2 31
#define D_1 32
#define D_0 33

//---------------------------------
// --- non-functional pins
//---------------------------------

// 5V
#define VDD 8

// No-connect
#define NC 35

// 0V
#define VSS 21

// these are the actual pin numbers for the chip pins - starts from index 1
int pin[41] = {  -1,
                15, 14, 2, 3, 4, 5, 6, -1, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45,
                -1, 47, 49, 51, 53, 36, 34, 32, 30, 28, 26, 24, 22, 7, -1, 8, 9, 10, 11, 12};

int bTickState = LOW;

void setup()
{
  Serial.begin(115200);
  
  // setup the RO pins
  pinMode(pin[A_0], INPUT);
  pinMode(pin[A_1], INPUT);
  pinMode(pin[A_2], INPUT);
  pinMode(pin[A_3], INPUT);
  pinMode(pin[A_4], INPUT);
  pinMode(pin[A_5], INPUT);
  pinMode(pin[A_6], INPUT);
  pinMode(pin[A_7], INPUT);
  pinMode(pin[A_8], INPUT);
  pinMode(pin[A_9], INPUT);
  pinMode(pin[A_10], INPUT);
  pinMode(pin[A_11], INPUT);
  pinMode(pin[A_12], INPUT);
  pinMode(pin[A_13], INPUT);
  pinMode(pin[A_14], INPUT);
  pinMode(pin[A_15], INPUT);
  
  pinMode(pin[VPB], INPUT);
  pinMode(pin[PHI1O], INPUT);
  pinMode(pin[PHI2O], INPUT);
  pinMode(pin[MLB], INPUT);
  pinMode(pin[SYNC], INPUT);
  pinMode(pin[RWB], INPUT);

  // setup the WO pins
  pinMode(pin[RWB], OUTPUT);
  pinMode(pin[NMIB], OUTPUT);
  pinMode(pin[BE], OUTPUT);
  pinMode(pin[PHI2], OUTPUT);
  pinMode(pin[SOB], OUTPUT);
  pinMode(pin[RESB], OUTPUT);

  // set the RW pins to read for now...
  pinMode(pin[RDY], INPUT);
  pinMode(pin[D_0], INPUT);
  pinMode(pin[D_1], INPUT);
  pinMode(pin[D_2], INPUT);
  pinMode(pin[D_3], INPUT);
  pinMode(pin[D_4], INPUT);
  pinMode(pin[D_5], INPUT);
  pinMode(pin[D_6], INPUT);
  pinMode(pin[D_7], INPUT);

  // temp
  set_data(0xea);

  Serial.println("6502 Test Initialised...");
}

void print_status()
{
  int address = get_address();
  
  // print address
  char buffer[64];
  sprintf(buffer, "%04x", address);
  Serial.println(buffer);
}

void set_data(int data)
{
  digitalWrite(pin[D_0], data & 0x01 ? HIGH : LOW);
  digitalWrite(pin[D_1], data & 0x02 ? HIGH : LOW);
  digitalWrite(pin[D_2], data & 0x04 ? HIGH : LOW);
  digitalWrite(pin[D_3], data & 0x08 ? HIGH : LOW);
  digitalWrite(pin[D_4], data & 0x10 ? HIGH : LOW);
  digitalWrite(pin[D_5], data & 0x20 ? HIGH : LOW);
  digitalWrite(pin[D_6], data & 0x40 ? HIGH : LOW);
  digitalWrite(pin[D_7], data & 0x80 ? HIGH : LOW);
}

int get_data()
{
  int ret = 0;
  ret += digitalRead(pin[D_0]) == HIGH ? 0x01 : 0;
  ret += digitalRead(pin[D_1]) == HIGH ? 0x02 : 0;
  ret += digitalRead(pin[D_2]) == HIGH ? 0x04 : 0;
  ret += digitalRead(pin[D_3]) == HIGH ? 0x08 : 0;
  ret += digitalRead(pin[D_4]) == HIGH ? 0x10 : 0;
  ret += digitalRead(pin[D_5]) == HIGH ? 0x20 : 0;
  ret += digitalRead(pin[D_6]) == HIGH ? 0x40 : 0;
  ret += digitalRead(pin[D_7]) == HIGH ? 0x80 : 0;
  return ret;
}

int get_address()
{
  int ret = 0;
  ret += digitalRead(pin[A_0]) == HIGH ? 0x0001 : 0;
  ret += digitalRead(pin[A_1]) == HIGH ? 0x0002 : 0;
  ret += digitalRead(pin[A_2]) == HIGH ? 0x0004 : 0;
  ret += digitalRead(pin[A_3]) == HIGH ? 0x0008 : 0;
  ret += digitalRead(pin[A_4]) == HIGH ? 0x0010 : 0;
  ret += digitalRead(pin[A_5]) == HIGH ? 0x0020 : 0;
  ret += digitalRead(pin[A_6]) == HIGH ? 0x0040 : 0;
  ret += digitalRead(pin[A_7]) == HIGH ? 0x0080 : 0;
  ret += digitalRead(pin[A_8]) == HIGH ? 0x0100 : 0;
  ret += digitalRead(pin[A_9]) == HIGH ? 0x0200 : 0;
  ret += digitalRead(pin[A_10]) == HIGH ? 0x0400 : 0;
  ret += digitalRead(pin[A_11]) == HIGH ? 0x0800 : 0;
  ret += digitalRead(pin[A_12]) == HIGH ? 0x1000 : 0;
  ret += digitalRead(pin[A_13]) == HIGH ? 0x2000 : 0;
  ret += digitalRead(pin[A_14]) == HIGH ? 0x4000 : 0;
  ret += digitalRead(pin[A_15]) == HIGH ? 0x8000 : 0;
  return ret;
}

void loop()
{
  bool bTick = true;
  
  // read the monitor input

  if(Serial.available())
  {
    // parse command line
  }
  
  if(bTick)
  {
    if(bTickState == LOW)
    {
      digitalWrite(pin[PHI2], HIGH);
      bTickState = HIGH;
    }
    else
    {
      digitalWrite(pin[PHI2], LOW);
      bTickState = LOW;
    }
  }
  
  print_status();
  
}
