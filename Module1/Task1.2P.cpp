const uint8_t led_pin = 2;
const uint8_t motion_pin = 3;

bool isMotion;

void setup()
{
  pinMode(led_pin, OUTPUT);
  pinMode(motion_pin, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(motion_pin), handle, CHANGE);
  
  Serial.begin(9600);
}

void loop()
{}

void handle()
{
  isMotion = digitalRead(motion_pin);
  
  Serial.print("Is motion? : ");
  Serial.println(isMotion ? "True" : "False");
  
  if(isMotion == true)
  {
    digitalWrite(led_pin, HIGH);
    Serial.println("LED is on.");
  }
  else
  {
    digitalWrite(led_pin, LOW);
    Serial.println("LED is off.");
  }
}
