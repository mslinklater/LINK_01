#define BUS_SIZE 8

int bus_a_pins[BUS_SIZE] = {39, 41, 43, 45, 47, 49, 51, 53};
int bus_b_pins[BUS_SIZE] = {38, 40, 42, 44, 46, 48, 50, 52};
int dir_pin = 37;
int oe_pin = 36;

void set_a_to_b()
{
  digitalWrite(dir_pin, HIGH);
  for(int i=0 ; i<BUS_SIZE ; i++)
  {
    pinMode(bus_a_pins[i], OUTPUT);
    pinMode(bus_b_pins[i], INPUT);
  }
}

void set_b_to_a()
{
  digitalWrite(dir_pin, LOW);
  for(int i=0 ; i<BUS_SIZE ; i++)
  {
    pinMode(bus_a_pins[i], INPUT);
    pinMode(bus_b_pins[i], OUTPUT);
  }
}

void set_output_enable(bool enable)
{
  if(enable)
  {
    digitalWrite(oe_pin, LOW);
  }
  else
  {
    digitalWrite(oe_pin, HIGH);
  }
}

void write_a(int value)
{
  for(int i=0 ; i<BUS_SIZE ; i++)
  {
    digitalWrite(bus_a_pins[i], value & (1<<i) ? HIGH: LOW);
  }
}

int read_a()
{
  int ret = 0;
  
  for(int i=0 ; i<BUS_SIZE ; i++)
  {
    ret += digitalRead(bus_a_pins[i]) == HIGH ? 1 << i : 0;
  }
  
  return ret;
}

void write_b(int value)
{
  for(int i=0 ; i<BUS_SIZE ; i++)
  {
    digitalWrite(bus_b_pins[i], value & (1<<i) ? HIGH: LOW);
  }
}

int read_b()
{
  int ret = 0;
  
  for(int i=0 ; i<BUS_SIZE ; i++)
  {
    ret += digitalRead(bus_b_pins[i]) == HIGH ? 1 << i : 0;
  }
  
  return ret;
}

void setup() {
  Serial.begin(115200);
  pinMode(dir_pin, OUTPUT);
  pinMode(oe_pin, OUTPUT);
  // buffer pins are set in the read/write methods
}

void loop() {
  // test a->b works
  delay(10);
  set_output_enable(true);
  set_a_to_b();
  for(int i=0 ; i<10 ; i++)
  {
    int val = random(0,256);
    write_a(val);
    int readval = read_b();
    if(val != readval)
    {
      Serial.println("a-b enabled failed");
    }
  }
  write_a(0);  // clear the values
  
  // test a->b disabled
  delay(10);
  set_output_enable(false);
  set_a_to_b();
  for(int i=0 ; i<10 ; i++)
  {
    int val = random(1,256);
    write_a(val);
    int readval = read_b();
    if(0 != readval)
    {
      Serial.println("a-b disabled failed");
    }
  }
  // test b->a works
  delay(10);
  set_output_enable(true);
  set_b_to_a();
  for(int i=0 ; i<10 ; i++)
  {
    int val = random(0,256);
    write_b(val);
    int readval = read_a();
    if(val != readval)
    {
      Serial.println("b-a enabled failed");
    }
  }
  write_b(0);  // clear the values
  // test b->a disabled
  delay(10);
  set_output_enable(false);
  set_b_to_a();
  for(int i=0 ; i<10 ; i++)
  {
    int val = random(1,256);
    write_b(val);
    int readval = read_a();
    if(0 != readval)
    {
      Serial.println("b-a disabled failed");
    }
  }
  delay(1000);
}

