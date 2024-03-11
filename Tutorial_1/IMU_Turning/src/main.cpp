#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Debug flag to make life easy
// #define DEBUG

// Parameters
#define YAW_DRIFT -0.005  // account for rotational drift in sensor
#define CORRECTION 1.2    // angle correction (90: 1.23, 360: 1.1)
#define PWM_MAX 255       // 8 bit PWM max value, partially in here just as documentation
#define FREQ 5000         // PWM params
#define RESOLUTION 8

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
  sensors_event_t a, g, temp; // A struct that holds mpu reading
  float curr_angle = 0;       // current angle of mouse
  float g_0 = 0;              // current g.gyro.z reading
  float g_1 = 0;              // previous g.gyto.z reading (delay of 1)
  unsigned long t_delta;      // change in milis() time (ms)
  unsigned long t_prev;       // previous milis() time (ms)

  // Start counting time just before motors first move 
  t_prev = millis();

  // Turn to correct direction
  if (goal > 0) {
    M1_forward(80);
    M2_backward(90);
  } else {
    M1_backward(90);
    M2_forward(80);
  }

  // Poll angle until goal is reached
  while (abs(curr_angle) < abs(goal)) {
    // Latest MPU update
    mpu.getEvent(&a, &g, &temp);
    g_0 = g.gyro.z - YAW_DRIFT;
  
    // Update time elapsed
    t_delta = millis() - t_prev;
    t_prev = t_delta + t_prev;
  
    // Run the integral and increment angle
    // t_delta is in ms, so multiply by 0.001
    // need to convert rad to deg, so it is multipled by 180/3.1416
    curr_angle += CORRECTION*(180/3.1416)*(t_delta*0.001)*(g_0 + g_1)/2;

    g_1 = g_0;
    
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

  M1_stop();
  M2_stop();

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
  turn_angle(90.0);
  delay(2000);
  turn_angle(90.0);
  delay(2000);
  turn_angle(90.0);
  delay(2000);
  turn_angle(-360.0);
  delay(2000);
}
