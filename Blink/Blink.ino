uint32_t base_timer_loop = 0;
uint8_t LED_BUILTIN_state = 0;
uint8_t PRESSURE_SENSOR_state = 0;
int pressure_input_pin = 8;
uint32_t pressure_sensorValue = 0;


uint8_t SENSOR_LEVEL1_PIN = 12;
uint8_t SENSOR_LEVEL2_PIN = 10;

uint8_t LEVEL1_PIN_state = 0;
uint8_t LEVEL2_PIN_state = 0;

uint16_t LEVEL1_POS1 = 4240;
uint16_t LEVEL1_POS2 = 4200;

uint16_t LEVEL2_POS1 = 4160;
uint16_t LEVEL2_POS2 = 4080;

uint8_t DEBUG_SERIAL = 0;
// uint8_t DEBUG_SERIAL = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(SENSOR_LEVEL1_PIN, OUTPUT);
  pinMode(SENSOR_LEVEL2_PIN, OUTPUT);
  digitalWrite(SENSOR_LEVEL1_PIN, HIGH);
  digitalWrite(SENSOR_LEVEL2_PIN, HIGH);

  // pinMode(pressure_input_pin, INPUT_PULLUP);
  pinMode(pressure_input_pin, INPUT);
  if (DEBUG_SERIAL > 0) {
    Serial.begin(9600);
  }

}

// the loop function runs over and over again forever
void loop() {
  base_timer_loop++;
  if (base_timer_loop > 800000) {
    base_timer_loop = 0;

    if ((pressure_sensorValue > LEVEL1_POS1) && ( (LEVEL1_PIN_state > 0))) {
      LEVEL1_PIN_state = 0;
      digitalWrite(SENSOR_LEVEL1_PIN, HIGH);
    }

    if ((pressure_sensorValue < LEVEL1_POS2) && (!(LEVEL1_PIN_state > 0))) {
      LEVEL1_PIN_state = 1;
      digitalWrite(SENSOR_LEVEL1_PIN, LOW);
    }

    if ((pressure_sensorValue > LEVEL2_POS1) && ( (LEVEL2_PIN_state > 0))) {
      LEVEL2_PIN_state = 0;
      digitalWrite(SENSOR_LEVEL2_PIN, HIGH);
    }

    if ((pressure_sensorValue < LEVEL2_POS2) && (!(LEVEL2_PIN_state > 0))) {
      LEVEL2_PIN_state = 1;
      digitalWrite(SENSOR_LEVEL2_PIN, LOW);
    }

    if (DEBUG_SERIAL > 0) {
      Serial.print("P1=[");
      Serial.print(LEVEL1_PIN_state);
      Serial.print("] P2=[");
      Serial.print(LEVEL2_PIN_state);
      Serial.print("] ");
      
      Serial.print("P=[");
      Serial.print(pressure_sensorValue);
      Serial.println("]");
    }

    pressure_sensorValue = 0;

    if (LED_BUILTIN_state > 0) {
      LED_BUILTIN_state = 0;
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    } else {
      LED_BUILTIN_state = 1;
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
  }

  read_sensor_pin();
  delayMicroseconds(1);
}

void read_sensor_pin() {
  uint8_t pinState = digitalRead(pressure_input_pin);
  if (pinState != PRESSURE_SENSOR_state) {
    PRESSURE_SENSOR_state = pinState;
    pressure_sensorValue++;
  }
}
