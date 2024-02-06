#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Debug flag to make life easy
// #define DEBUG

// Parameters
#define ANGLE_SCALE .00001 // Convert angle rate * delta t into degrees
#define MIN_ANGLE 0.01 // Change in angle below with it should be clamped to 0 (reduce error)
#define TURN_GOAL 90 // Amount to turn in degrees
#define PWM_MAX 512 // 8 bit PWM max value, partially in here just as documentation
#define FREQ 5000 // PWM params
#define RESOLUTION 10

// Globals, mostly pin declarations
Adafruit_MPU6050 mpu;

const unsigned int ADC_1_CS = 2;
const unsigned int ADC_2_CS = 17;
const unsigned int M1_IN_1 = 13;
const unsigned int M1_IN_2 = 12;
const unsigned int M2_IN_1 = 25;
const unsigned int M2_IN_2 = 14;

const unsigned int M1_IN_1_CHANNEL = 8;
const unsigned int M1_IN_2_CHANNEL = 9;
const unsigned int M2_IN_1_CHANNEL = 10;
const unsigned int M2_IN_2_CHANNEL = 11;

void M1_backward(int pwm_value) {
  ledcWrite(M1_IN_1_CHANNEL, pwm_value);
  ledcWrite(M1_IN_2_CHANNEL, 0);
}

void M1_forward(int pwm_value) {
  ledcWrite(M1_IN_1_CHANNEL, 0);
  ledcWrite(M1_IN_2_CHANNEL, pwm_value);
}

void M1_stop() {
  ledcWrite(M1_IN_1_CHANNEL, PWM_MAX);
  ledcWrite(M1_IN_2_CHANNEL, PWM_MAX);
}

void M2_backward(int pwm_value) {
  ledcWrite(M2_IN_1_CHANNEL, pwm_value);
  ledcWrite(M2_IN_2_CHANNEL, 0);
}

void M2_forward(int pwm_value) {
  ledcWrite(M2_IN_1_CHANNEL, 0);
  ledcWrite(M2_IN_2_CHANNEL, pwm_value);
}

void M2_stop() {
  ledcWrite(M2_IN_1_CHANNEL, PWM_MAX);
  ledcWrite(M2_IN_2_CHANNEL, PWM_MAX);
}

// Turns in appropriate direction, using integral for angle until is reached, then stops motors
void turn_angle(float goal) {
  // A struct that holds mpu reading
  sensors_event_t a, g, temp;

  bool cw; // keep track of direction so we can account for a little overshoot
  float curr_angle = 0;
  unsigned long t_delta;

  // Start counting time just before motors first move 
  t_delta = millis();

  // Turn to correct direction
  if (curr_angle < goal) {
    cw = false;
    M1_backward(300);
    M2_forward(300);

  }
  else if (curr_angle > goal) {
    cw = true;
    M1_forward(300);
    M2_backward(300);
  }

  // Poll angle until goal is reached
  while ((!cw && curr_angle <= goal) || (cw && curr_angle >= goal)) {
    // Latest MPU update
    mpu.getEvent(&a, &g, &temp);
  
    // Update time elapsed
    t_delta = millis() - t_delta;
  
    // Run the integral and increment angle
    // Rate is rad/s, time in ms, so should div by 1000
    // Should be multiplying by 180/pi for the rad
    // But I found this offset works better while testing
    // Also it misrepresents sitting still as a small increment in angle,
    // But that adds up
    if (abs(t_delta*g.gyro.z*ANGLE_SCALE) > MIN_ANGLE)
      curr_angle += t_delta*g.gyro.z*ANGLE_SCALE;

    #ifdef DEBUG
      Serial.print("Current angle: ");
      Serial.print(curr_angle);
      Serial.println("");
    #endif
  }

  M1_stop();
  M2_stop();
}

void setup() {
  // Stop the right motor by setting pin 14 low
  // this pin floats high or is pulled
  // high during the bootloader phase for some reason
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
  delay(100);

  // Serial will only be used for debugging
  #ifdef DEBUG
    Serial.begin(115200);
    while (!Serial)
      delay(10);
  #endif

  // Setup motor pins
  ledcSetup(M1_IN_1_CHANNEL, FREQ, RESOLUTION);
  ledcSetup(M1_IN_2_CHANNEL, FREQ, RESOLUTION);
  ledcSetup(M2_IN_1_CHANNEL, FREQ, RESOLUTION);
  ledcSetup(M2_IN_2_CHANNEL, FREQ, RESOLUTION);

  ledcAttachPin(M1_IN_1, M1_IN_1_CHANNEL);
  ledcAttachPin(M1_IN_2, M1_IN_2_CHANNEL);
  ledcAttachPin(M2_IN_1, M2_IN_1_CHANNEL);
  ledcAttachPin(M2_IN_2, M2_IN_2_CHANNEL);
  
  // Setup IMU pins
  pinMode(ADC_1_CS, OUTPUT);
  pinMode(ADC_2_CS, OUTPUT);

  digitalWrite(ADC_1_CS, HIGH); // Without this the ADC's write
  digitalWrite(ADC_2_CS, HIGH); // to the SPI bus while the nRF24 is!!!!

  while (!mpu.begin())
    delay(10);

  // Calibrate
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {
  turn_angle(90.0);
  delay(2000);
}
