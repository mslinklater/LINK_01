
//---------------------------------
// --- read only pins
//---------------------------------

// Address bus
#define A0 9
#define A1 10
#define A2 11
#define A3 12
#define A4 13
#define A5 14
#define A6 15
#define A7 16
#define A8 17
#define A9 18
#define A10 19
#define A11 20
#define A12 22
#define A13 23
#define A14 24
#define A15 25

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
#define D7 26
#define D6 27
#define D5 28
#define D4 29
#define D3 30
#define D2 31
#define D1 32
#define D0 33

//---------------------------------
// --- non-functional pins
//---------------------------------

// 5V
#define VDD 8

// No-connect
#define NC 35

// 0V
#define VSS 21

int pin[41] = {  -1,
                0, 1, 2, 3, 4, 5, 6, -1, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45,
                -1, 47, 49, 51, 53, 36, 34, 32, 30, 28, 26, 24, 22, 7, -1, 8, 9, 10, 11, 12};

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  // read the monitor input
  
}
