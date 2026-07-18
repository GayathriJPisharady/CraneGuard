#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Servo craneServo;

// ---------------- Pins ----------------
const int TRIG_PIN   = 5;
const int ECHO_PIN   = 18;

const int SERVO_PIN  = 19;

const int GREEN_LED  = 25;
const int YELLOW_LED = 26;
const int RED_LED    = 27;

const int BUZZER_PIN = 14;

// ---------------- Variables ----------------
float distanceCM = 0;

unsigned long lastBeep = 0;
bool beepState = false;

// ---------------- Function Prototypes ----------------
float readDistance();
void updateOLED(float dist, const char *status);
void allLEDsOff();
void buzzerOff();
void warningBuzzer();
void emergencyBuzzer();

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  craneServo.setPeriodHertz(50);
  craneServo.attach(SERVO_PIN, 500, 2400);
  craneServo.write(90);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  // Startup Screen
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(10, 8);
  display.println("SMART");

  display.setCursor(10, 30);
  display.println("CRANE");

  display.setTextSize(1);
  display.setCursor(20, 54);
  display.println("Anti-Collision");

  display.display();

  delay(2000);

  display.clearDisplay();
  display.display();
}

void loop() {

  distanceCM = readDistance();

  Serial.print("Distance: ");
  Serial.print(distanceCM);
  Serial.println(" cm");

  if (distanceCM > 100) {

    allLEDsOff();
    digitalWrite(GREEN_LED, HIGH);

    craneServo.write(90);

    buzzerOff();

    updateOLED(distanceCM, "SAFE");
  }

  else if (distanceCM >= 50) {

    allLEDsOff();
    digitalWrite(YELLOW_LED, HIGH);

    craneServo.write(60);

    warningBuzzer();

    updateOLED(distanceCM, "WARNING");
  }

  else {

    allLEDsOff();
    digitalWrite(RED_LED, HIGH);

    craneServo.write(0);

    emergencyBuzzer();

    updateOLED(distanceCM, "EMERGENCY");
  }

  delay(50);
}

float readDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return 400.0;
  }

  return duration * 0.0343 / 2.0;
}

void updateOLED(float dist, const char *status) {

  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("CRANE");

  display.setTextSize(1);
  display.setCursor(0, 24);
  display.print("Distance:");

  display.setTextSize(2);
  display.setCursor(0, 36);
  display.print(dist, 1);
  display.print("cm");

  display.setTextSize(1);
  display.setCursor(82, 2);
  display.print(status);

  display.display();
}

void allLEDsOff() {

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void buzzerOff() {

  noTone(BUZZER_PIN);
  beepState = false;
}

void warningBuzzer() {

  if (millis() - lastBeep >= 600) {

    lastBeep = millis();

    if (beepState) {
      noTone(BUZZER_PIN);
    } else {
      tone(BUZZER_PIN, 1500);
    }

    beepState = !beepState;
  }
}

void emergencyBuzzer() {

  if (millis() - lastBeep >= 150) {

    lastBeep = millis();

    if (beepState) {
      noTone(BUZZER_PIN);
    } else {
      tone(BUZZER_PIN, 2500);
    }

    beepState = !beepState;
  }
}
