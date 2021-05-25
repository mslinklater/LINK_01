#define VPB 0
#define RDY 1
#define PHI1O 2
#define IRQB 3
#define MLB 4
#define NMIB 5
#define SYNC 6
#define VDD 7
#define A0 8
#define A1 9
#define A2 10
#define A3 11
#define A4 12
#define A5 13
#define A6 14
#define A7 15
#define A8 16
#define A9 17
#define A10 18
#define A11 19
#define VSS 20
#define A12 21
#define A13 22
#define A14 23
#define A15 24
#define D7 25
#define D6 26
#define D5 27
#define D4 28
#define D3 29
#define D2 30
#define D1 31
#define D0 32
#define RWB 33
#define NC 34
#define BE 35
#define PHI2 36
#define SOB 37
#define PHI2O 38
#define RESB 39

int pin[40] = {  0, 1, 2, 3, 4, 5, 6, -1, 23, 25,
                 27, 29, 31, 33, 35, 37, 39, 41, 43, 45,
                 -1, 47, 49, 51, 53, 36, 34, 32, 30, 28,
                 26, 24, 22, 7, -1, 8, 9, 10, 11, 12};

void setup()
{
  Serial.begin(115200);
}

void loop()
{
}
