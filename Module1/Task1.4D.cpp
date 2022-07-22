// sensor pins
const uint8_t motion_pin = PD3;
const uint8_t force_pin = PD2;
const uint8_t switch_pin = PB0;

// led pins
const uint8_t onboard_led_pin = PB5;
const uint8_t switch_led_pin = PD4;
const uint8_t motion_led_pin = PD5;
const uint8_t force_led_pin = PD6;

// counter and compare values
const uint16_t t1_load = 0;
const uint16_t t1_comp = 15625;

bool is_motion = false;
bool is_force = false;

void setup()
{
  // setting inputs
  DDRB |= _BV(switch_pin); // for pin change interrupt
  DDRB |= _BV(onboard_led_pin);
  DDRD |= _BV(motion_led_pin) | _BV(force_led_pin) | _BV(switch_led_pin);
  
  // setting outputs, ensuring off
  PORTD &= ~(1 << motion_led_pin);
  PORTD &= ~(1 << force_led_pin);
  PORTD &= ~(1 << switch_led_pin);
  
  // attaching functions to handle external interrupts
  attachInterrupt(digitalPinToInterrupt(motion_pin), handleMotionSensor, CHANGE);
  attachInterrupt(digitalPinToInterrupt(force_pin), handleForceSensor, CHANGE);
  
  /* timing interrupt set-up */
  // reset Timer1 control reg A
  TCCR1A = 0;
  
  // set CTC mode
  TCCR1B &= ~_BV(WGM13);
  TCCR1B |= _BV(WGM12);
  
  // set the clock source to 101, prescalar of 1024
  TCCR1B |= _BV(CS12);
  TCCR1B &= ~_BV(CS11);
  TCCR1B |= _BV(CS10);
  
  // reset Timer1 and set compare value
  TCNT1 = t1_load;
  OCR1A = t1_comp;
  
  // enable Timer1 compare interrupt
  TIMSK1 = _BV(OCIE1A);
  
  /* pin change interrupt set-up */
  // bit 0 of Pin Change Interrupt Control Register to 1 (PCINT7..0 interrupts enabled)
  PCICR |= 1;
  
  // switch pin will trigger pin change interrupt
  PCMSK0 |= 1;
  
  sei();
  Serial.begin(9600);
}

void loop()
{
  delay(500);
}

// motion sensor interrupt handler
void handleMotionSensor()
{
  is_motion = (PIND & _BV(motion_pin)) >> motion_pin;
  
  Serial.print("Is motion? : ");
  Serial.println(is_motion ? "True" : "False");
  
  if(is_motion == true)
  {
    PORTD |= _BV(motion_led_pin);
    Serial.println("Motion LED is on.");
  }
  else
  {
    PORTD &= ~_BV(motion_led_pin);
    Serial.println("Motion LED is off.");
  }
}

// force sensor interrupt handler
void handleForceSensor()
{
  is_force = (PIND & _BV(force_pin)) >> force_pin;
  
  Serial.print("Is force? : ");
  Serial.println(is_force ? "True" : "False");
  
  if(is_force == true)
  {
    PORTD |= _BV(force_led_pin);
    Serial.println("Force LED is on.");
  }
  else
  {
  	PORTD &= _BV(force_led_pin);
    Serial.println("Force LED is off.");
  }
}

// interrupt service routine for compare match interrupt 
ISR(TIMER1_COMPA_vect)
{
  Serial.println("Compare match interrupt. Timer1 CompA ISR triggered.");
  PORTB ^= (1 << onboard_led_pin);
}

// interrupt service routine for port B (PB0-PB7) pin change interrupt
ISR(PCINT0_vect)
{
  Serial.println("Pin change interrupt. Port B PC INT ISR triggered.");
  PORTD ^= (1 << switch_led_pin);
}
