#include<Wire.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;

#define thumb 14
#define index 27
#define middle 26
#define ring 25
#define pinky 33

float accelX1, accelY1, accelZ1;
float gForceX1, gForceY1, gForceZ1;

float gyroX1, gyroY1, gyroZ1;

float flexValues[] = {0,0,0,0};

void setup(){

  Serial.begin(115200);
  while (!Serial) {
     delay(10); // wait for serial port to connect. Needed for native USB port only
  }
  
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  printHead();
}

void loop(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  flexValues[0] = analogRead(thumb);
  flexValues[1] = analogRead(index);
  flexValues[2] = analogRead(middle);
  flexValues[3] = analogRead(pinky);
  accelX1 = a.acceleration.x;
  accelY1 = a.acceleration.y;
  accelZ1 = a.acceleration.z;
  gyroX1 = g.gyro.x;
  gyroY1 = g.gyro.y;
  gyroZ1 = g.gyro.z;
  gForceX1 = a.acceleration.heading;
  gForceY1 = a.acceleration.pitch;
  gForceZ1 = a.acceleration.roll;
  printData();
  delay(500);
}

void printHead(){
  Serial.print("thumb1,");
  Serial.print("index1,");
  Serial.print("middle1,");
  Serial.print("pinky1,");
  Serial.print("accelX1,");
  Serial.print("accelY1,");
  Serial.print("accelZ1,");
  Serial.print("gForceX1,");
  Serial.print("gForceY1,");
  Serial.print("gForceZ1,");
  Serial.print("gyroX1,");
  Serial.print("gyroY1,");
  Serial.print("gyroZ1,");
  Serial.print("gesture,");
  Serial.print("\n");  
}

void printData(){
  Serial.print(String(flexValues[0]));
  Serial.print(",");
  Serial.print(String(flexValues[1]));
  Serial.print(",");
  Serial.print(String(flexValues[2]));
  Serial.print(",");
  Serial.print(String(flexValues[3]));
  Serial.print(",");
  Serial.print(accelX1);
  Serial.print(",");
  Serial.print(accelY1);
  Serial.print(",");
  Serial.print(accelZ1);
  Serial.print(",");
  Serial.print(gForceX1);
  Serial.print(",");
  Serial.print(gForceY1);
  Serial.print(",");
  Serial.print(gForceZ1);
  Serial.print(",");
  Serial.print(gyroX1);
  Serial.print(",");
  Serial.print(gyroY1);
  Serial.print(",");
  Serial.print(gyroZ1);
  Serial.print(",");
  Serial.print("OK!"); //Input the gesture u are recording
  Serial.print("\n");
  
}
