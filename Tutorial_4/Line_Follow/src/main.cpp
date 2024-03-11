#include <Arduino.h>
#include <Adafruit_MCP3008.h>
#include <Encoder.h>

// ADC (line sensor)
Adafruit_MCP3008 adc1;
Adafruit_MCP3008 adc2;

const unsigned int ADC_1_CS = 2;
const unsigned int ADC_2_CS = 17;

int adc1_buf[8];
int adc2_buf[8];

uint8_t lineArray[13]; 
float previousPosition = 6;

// Encoders
const unsigned int M1_ENC_A = 39;
const unsigned int M1_ENC_B = 38;
const unsigned int M2_ENC_A = 37;
const unsigned int M2_ENC_B = 36;

// Motors
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

const unsigned int PWM_MAX = 255;
const int freq = 5000;
const int resolution = 8;

// LED
const int ledChannel = 0;

// PID
const int base_pid = 80;
const float mid = 6;

float error;
float last_error;
float total_error;

float Kp = 8;
float Kd = 125;
float Ki = 0;


/*
 *  Line sensor functions
 */
void readADC() {
  for (int i = 0; i < 8; i++) {
    adc1_buf[i] = adc1.readADC(i);
    adc2_buf[i] = adc2.readADC(i);
  }
}

void digitalConvert() {
  for (int i = 0; i < 7; i++) {
    if (adc1_buf[i]>690) {
      lineArray[2*i] = 0; 
    } else {
      lineArray[2*i] = 1;
    }

    if (i<6) {
      if (adc2_buf[i]>690){
        lineArray[2*i+1] = 0;
      } else {
        lineArray[2*i+1] = 1;
      }
    }

    // print line sensor position
    // for(int i = 0; i < 13; i++) {
    //   Serial.print(lineArray[2*i+1]); Serial.print(" ");
    // }
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

/*
 *  Movement functions
 */
void M1_forward(int pwm_value) {
  ledcWrite(M1_IN_1_CHANNEL, 0);
  ledcWrite(M1_IN_2_CHANNEL, pwm_value);
}
void M2_forward(int pwm_value) {
  ledcWrite(M2_IN_1_CHANNEL, 0);
  ledcWrite(M2_IN_2_CHANNEL, pwm_value);
}

void M1_backward(int pwm_value) {
  ledcWrite(M1_IN_1_CHANNEL, pwm_value);
  ledcWrite(M1_IN_2_CHANNEL, 0);
}
void M2_backward(int pwm_value) {
  ledcWrite(M2_IN_1_CHANNEL, pwm_value);
  ledcWrite(M2_IN_2_CHANNEL, 0);
}

void M1_stop() {
  ledcWrite(M1_IN_1_CHANNEL, PWM_MAX);
  ledcWrite(M1_IN_2_CHANNEL, PWM_MAX);
}
void M2_stop() {
  ledcWrite(M2_IN_1_CHANNEL, PWM_MAX);
  ledcWrite(M2_IN_2_CHANNEL, PWM_MAX);
}

//wheel diam = 32mm
// 3.58 ticks per mm
// ticks = 3.58*distance(mm)*correction
void turnCorner(Encoder enc1, Encoder enc2, float pos) {
  long enc_base = 0;
  long enc_value = 0;

  enc_base = enc1.read();
  enc_value = enc_base;

  // move forward until axis is aligned
  M1_forward(base_pid);
  M2_forward(base_pid+5);
  while(abs(enc_value-enc_base) < 268);

  // turn 90 degrees
  if(lineArray[0] == 1) {
    M1_forward(base_pid);
    M2_backward(base_pid+20);
  } else {
    M1_backward(base_pid+20);
    M2_forward(base_pid+5);
  }
  enc_base = enc1.read();
  enc_value = enc_base;
  while(abs(pos-mid) > 1) {
    readADC();
    digitalConvert();
    pos = getPosition(previousPosition);
    previousPosition = pos;
  }
  M1_stop();
  M2_stop();
}

/*
 *  setup and loop
 */
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

  M1_stop();
  M2_stop();

  delay(100);
}

void loop() {


  Encoder enc1(M1_ENC_A, M1_ENC_B);
  Encoder enc2(M2_ENC_A, M2_ENC_B);

  while(true) {
    int t_start = micros();
    readADC();
    int t_end = micros();

    digitalConvert();

    float pos = getPosition(previousPosition);

    error = pos - mid;
    total_error += error;

    int pid_value = Kp*error + Kd*(error-last_error) + Ki*total_error;
    int right_motor = base_pid - pid_value;
    int left_motor = base_pid + pid_value;

    if(right_motor < 0)       right_motor = 0;
    if(left_motor < 0)        left_motor  = 0;
    if(right_motor > PWM_MAX) right_motor = PWM_MAX;
    if(left_motor > PWM_MAX)  left_motor  = PWM_MAX;

    M1_forward(right_motor);
    M2_forward(left_motor);

    
    //
    if((lineArray[0] == 1 || lineArray[12] == 1) && abs(error) <= 4) {
      turnCorner(enc1, enc2, pos);
    }

    last_error = error;
    previousPosition = pos;

    // Serial.print("time: ");   Serial.print(t_end - t_start); Serial.print("\t");
    // Serial.print("pos: ");    Serial.print(pos);             Serial.print("\t");
    // Serial.print("error: ");  Serial.print(error);           Serial.print("\t");
    // Serial.print(" right: "); Serial.print(right_motor);     Serial.print("\t");
    // Serial.print(" left: ");  Serial.print(left_motor);      Serial.print("\t");
    Serial.println();
  }
}
