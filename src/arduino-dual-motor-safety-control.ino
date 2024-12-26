byte enA = 8;
byte in1 = 7;
byte in2 = 6;

byte enB = 3;
byte in3 = 5;
byte in4 = 4;

byte trigPin = 9;
byte echoPin = 10;

const int thresholdDistance = 100;
const unsigned long timerInterval = 5000; // milliseconds (5 seconds)

volatile unsigned long timerCounter = 0;
volatile bool motorsRunning = false;
int lastDirection = 0;
int lastSpeed = 0;

void setup() {
  // Set pins 3-9 as outputs
  for (int i = 3; i < 10; i++)
    pinMode(i, OUTPUT);

  // Initialize motor control pins to LOW
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  // Set analog pins as inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  cli();       // Disable interrupts
  TCCR1A = 0;  // Clear timer1 control register A
  TCCR1B = 0;  // Clear timer1 control register B
  TCNT1 = 0;   // Initialize counter value to 0
  OCR1A = 15624;     // Set compare match register for 1Hz frequency
  TCCR1B |= (1 << WGM12);  // Turn on CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024
  TIMSK1 |= (1 << OCIE1A); // Enable timer compare interrupt
  sei(); // Enable interrupts
}

void loop() {
  // Read potentiometer values for direction and speed
  int direction = analogRead(A0);
  int speed = map(analogRead(A1), 0, 1023, 0, 255);

  // Get distance from ultrasonic sensor
  int distance = getDistance();

  // Check safety conditions
  if (distance <= thresholdDistance || timerCounter >= timerInterval) {
    if (motorsRunning) {
      stopMotors();
      motorsRunning = false;
    }
  } else {
    // Start motors if not running
    if (!motorsRunning) {
      startTimer();
      motorsRunning = true;
    }
    // Reset timer if direction or speed changed
    if (direction != lastDirection || speed != lastSpeed) {
      lastDirection = direction;
      lastSpeed = speed;
      motorsRunning = true;
      timerCounter = 0;
    }
    Control(direction, speed);
  }
}

int getDistance() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);

  // Measure the response
  long duration = pulseIn(echoPin, HIGH);
  int distance = (duration / 2) / 29.154; // Convert to centimeters

  return distance;
}

void Control(int direction, int speed) {
  // Set motor speeds
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  // Control motor direction
  if (direction < 512) {
    // Turn left
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else {
    // Turn right
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}

void startTimer() {
  // Initialize timer counter
  timerCounter = 0;
}

void stopMotors() {
  // Stop both motors
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

ISR(TIMER1_COMPA_vect) { // Timer compare match interrupt handler
  if (motorsRunning) {
    timerCounter += 1000; // Increment counter every second
    if (timerCounter >= timerInterval) {
      stopMotors();
      motorsRunning = false;
    }
  }
}