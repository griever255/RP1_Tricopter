#include <Arduino.h>
#include <Servo.h>

#include <Wire.h>
#include <MPU6050.h>

Servo ESC_P;
Servo ESC_S;
MPU6050 mpu;

int pos = 0;
int ESC_P_PIN = 22;
int ESC_S_PIN = 23;
int LED_PIN = LED_BUILTIN;
int led_state = LOW;

const int MPU_addr = 0x68; //I2C address of MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup(){
  ESC_P.attach(ESC_P_PIN);
  ESC_S.attach(ESC_S_PIN);
  ESC_P.writeMicroseconds(1500);
  ESC_S.writeMicroseconds(1500); // send "stop" signal to ESC. Also necessary to arm the ESC
  delay(5000);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);  // set to 0 (wakes up MPU-6050)
  Wire.endTransmission(true);
}

void loop(){
  digitalWrite(LED_PIN, HIGH);
  ESC_P.writeMicroseconds(1470);
  ESC_S.writeMicroseconds(1530);

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  delay(10);



  // for(pos=0; pos < 180; pos+=1){
  //   MG996.write(pos);
  //   delay(15);
  //   if (led_state == LOW)
  //     led_state = HIGH;
  //   else
  //     led_state = LOW;
  //   digitalWrite(LED_PIN, led_state);
  // }
  // digitalWrite(LED_PIN, led_state);
  // delay(1000);
  // for(pos=180; pos>=0; pos-=1){
  //   MG996.write(pos);
  //   delay(15);
  //   if (led_state == LOW)
  //     led_state = HIGH;
  //   else
  //     led_state = LOW;
  //   digitalWrite(LED_PIN, led_state);
  // }
  // digitalWrite(LED_PIN, led_state);
  // delay(1000);
}