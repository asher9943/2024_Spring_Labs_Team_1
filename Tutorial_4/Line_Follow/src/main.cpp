#include <Arduino.h>
#include <Adafruit_MCP3008.h>
#include <Encoder.h>

Adafruit_MCP3008 adc1;
Adafruit_MCP3008 adc2;

const unsigned int M1_ENC_A = 39;
const unsigned int M1_ENC_B = 38;
const unsigned int M2_ENC_A = 37;
const unsigned int M2_ENC_B = 36;

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

const unsigned int M1_I_SENSE = 35;
const unsigned int M2_I_SENSE = 34;

const unsigned int PWM_MAX = 255; // Max PWM given 8 bit resolution

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

int adc1_buf[8];
int adc2_buf[8];

float mid = 6.5;
int base_pid = 80;

uint8_t lineArray[13]; 
float previousPosition = 6;


float error;
float last_error;
float total_error;

float Kp = 8;
float Kd = 125;
float Ki = 0;

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


void readADC() {
  for (int i = 0; i < 8; i++) {
    adc1_buf[i] = adc1.readADC(i);
    adc2_buf[i] = adc2.readADC(i);
  }
}

void digitalConvert(){
  for (int i = 0; i < 7; i++) {
    // Serial.print(adc1_buf[i]); Serial.print(" ");
    if (adc1_buf[i]>690) {
      lineArray[2*i] = 0; 
    } else {
      lineArray[2*i] = 1;
    }
    Serial.print(lineArray[2*i]); Serial.print(" ");
    // Serial.print(adc1_buf[i]); Serial.print("\t");

    if (i<6) {
      // Serial.print(adc2_buf[i]); Serial.print(" ");
      if (adc2_buf[i]>690){
        lineArray[2*i+1] = 0;
      } else {
        lineArray[2*i+1] = 1;
      }
      Serial.print(lineArray[2*i+1]); Serial.print(" ");
      // Serial.print(adc2_buf[i]); Serial.print("\t");
    }
  }
}

float getPosition(float previousPosition) {
  
  float pos = 0;
  uint8_t white_count = 0;
  for (int i = 0; i < 13; i++) {
    if (lineArray[i] == 1) {
      pos += i;
      white_count+=1;
    } 
  }

  if (white_count == 0) {
    return previousPosition;
  }
  return pos/white_count;
}
void setup() {

  Serial.begin(115200);

  ledcSetup(M1_IN_1_CHANNEL, freq, resolution);
  ledcSetup(M1_IN_2_CHANNEL, freq, resolution);
  ledcSetup(M2_IN_1_CHANNEL, freq, resolution);
  ledcSetup(M2_IN_2_CHANNEL, freq, resolution);

  ledcAttachPin(M1_IN_1, M1_IN_1_CHANNEL);
  ledcAttachPin(M1_IN_2, M1_IN_2_CHANNEL);
  ledcAttachPin(M2_IN_1, M2_IN_1_CHANNEL);
  ledcAttachPin(M2_IN_2, M2_IN_2_CHANNEL);

  adc1.begin(ADC_1_CS);  
  adc2.begin(ADC_2_CS);

  pinMode(M1_I_SENSE, INPUT);
  pinMode(M2_I_SENSE, INPUT);

  delay(100);
}

void loop() {
  long enc_base = 0;
  long enc_value = 0;

  Encoder enc1(M1_ENC_A, M1_ENC_B);
  Encoder enc2(M2_ENC_A, M2_ENC_B);

  int t_start = micros();
  readADC();
  int t_end = micros();

  digitalConvert();

  float pos = getPosition(previousPosition);
  previousPosition = pos;

  error = pos - mid + 1;
  total_error += error;

  int pid_value = Kp*error + Kd*(error-last_error) + Ki*total_error;
  int right_motor = base_pid - pid_value;
  int left_motor = base_pid + pid_value;

  M1_forward(right_motor);
  M2_forward(left_motor);

  // Serial.print("time: \t"); Serial.print(t_end - t_start); Serial.print("\t");
  // Serial.print("pos: \t"); Serial.print(pos);
  Serial.print("error: \t"); Serial.print(error);
  Serial.print(" right: \t"); Serial.print(right_motor); Serial.print(" left: \t"); Serial.print(left_motor); 
  Serial.println();

  //wheel diam = 3.3cm
  //
  // if(lineArray[0] == 1) {
  //     enc_base = enc1.read();
  //     enc_value = enc_base;

  //     while (abs(enc_value-enc_base) < 576) {
  //       M1_forward(base_pid);
  //       M2_forward(base_pid);

  //       enc_value = enc1.read();
  //     }
  //     enc_base = enc1.read();
  //     enc_value = enc_base;
  //     while (abs(enc_value-enc_base) < 270) {
  //       M1_forward(base_pid);
  //       M2_backward(base_pid);

  //       enc_value = enc1.read();
  //     }
  // } else if(lineArray[12] == 1) {
  //     enc_base = enc1.read();
      
  //     // while () {
  //     //   M1_forward(0);
  //     //   M2_forward(base_pid);

  //     //   enc_value = enc1.read();
  //     // }
  // }
  last_error = error;


}
