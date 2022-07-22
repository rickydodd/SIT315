// sensor pins
const uint8_t motion_pin = 3;
const uint8_t force_pin = 2;

// led pins
const uint8_t motion_led_pin = 5;
const uint8_t force_led_pin = 6;

// interrupt pins
const uint8_t force_interrupt_pin = 2;

bool is_motion = false;
bool is_force = false;

void setup()
{
  // setting actuators to output
  pinMode(motion_led_pin, OUTPUT);
  pinMode(force_led_pin, OUTPUT);
  
  // setting sensors to input
  pinMode(motion_pin, INPUT);
  pinMode(force_pin, INPUT);
  
  // attaching functions to handle interrupts on sensors
  attachInterrupt(digitalPinToInterrupt(motion_pin), handleMotionSensor, CHANGE);
  attachInterrupt(digitalPinToInterrupt(force_pin), handleForceSensor, CHANGE);
  
  Serial.begin(9600);
}

void loop()
{}

// motion sensor interrupt handler
void handleMotionSensor()
{
  is_motion = digitalRead(motion_pin);
  
  Serial.print("Is motion? : ");
  Serial.println(is_motion ? "True" : "False");
  
  if(is_motion == true)
  {
    digitalWrite(motion_led_pin, HIGH);
    Serial.println("Motion LED is on.");
  }
  else
  {
    digitalWrite(motion_led_pin, LOW);
    Serial.println("Motion LED is off.");
  }
}

// force sensor interrupt handler
void handleForceSensor()
{
  is_force = digitalRead(force_pin);
  
  Serial.print("Is force? : ");
  Serial.println(is_force ? "True" : "False");
  
  if(is_force == true)
  {
    digitalWrite(force_led_pin, HIGH);
    Serial.println("Force LED is on.");
  }
  else
  {
  	digitalWrite(force_led_pin, LOW);
    Serial.println("Force LED is off.");
  }
}
