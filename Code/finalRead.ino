#include<Wire.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;

#define thumb  
#define index  
#define middle  
#define ring  
#define pinky

float accelX1, accelY1, accelZ1;
float gForceX1, gForceY1, gForceZ1;

float accelX2, accelY2, accelZ2;
float gForceX2, gForceY2, gForceZ2;

float gyroX1, gyroY1, gyroZ1;
float gyroX2, gyroY2, gyroZ2;

float flexValues[] = {0,0,0,0,0,0,0,0,0,0}

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
  flexValues[3] = analogRead(ring);
  flexValues[4] = analogRead(pinky);
  accelX1 = a.acceleration.x;
  accelY1 = a.acceleration.y;
  accelZ1 = a.acceleration.z;
  gyroX1 = g.gyro.x;
  gyroY1 = g.gyro.y;
  gyroZ1 = g.gyro.z;
  gForceX1 = a.acceleration.heading;
  gForceY1 = a.acceleration.pitch;
  gForceZ1 = a.acceleration.roll;
  delay(500);
  flexValues[5] = analogRead(thumb);
  flexValues[6] = analogRead(index);
  flexValues[7] = analogRead(middle);
  flexValues[8] = analogRead(ring);
  flexValues[9] = analogRead(pinky);
  accelX2 = a.acceleration.x;
  accelY2 = a.acceleration.y;
  accelZ2 = a.acceleration.z;
  gyroX2 = g.gyro.x;
  gyroY2 = g.gyro.y;
  gyroZ2 = g.gyro.z;
  gForceX2 = a.acceleration.heading;
  gForceY2 = a.acceleration.pitch;
  gForceZ2 = a.acceleration.roll;
  printData();
  delay(2000);
}

void printHead(){
  Serial.print("thumb1,");
  Serial.print("index1,");
  Serial.print("middle1,");
  Serial.print("ring1,");
  Serial.print("pinky1,");
  Serial.print("thumb2,");
  Serial.print("index2,");
  Serial.print("middle2,");
  Serial.print("ring2,");
  Serial.print("pinky2,");
  Serial.print("accelX1,");
  Serial.print("accelY1,");
  Serial.print("accelZ1,");
  Serial.print("gForceX1,");
  Serial.print("gForceY1,");
  Serial.print("gForceZ1,");
  Serial.print("gyroX1,");
  Serial.print("gyroY1,");
  Serial.print("gyroZ1,");
  Serial.print("accelX2,");
  Serial.print("accelY2,");
  Serial.print("accelZ2,");
  Serial.print("gForceX2,");
  Serial.print("gForceY2,");
  Serial.print("gForceZ2,");
  Serial.print("gyroX2,");
  Serial.print("gyroY2,");
  Serial.print("gyroZ2,");
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
  Serial.print(String(flexValues[4]));
  Serial.print(",");
  Serial.print(String(flexValues[5]));
  Serial.print(",");
  Serial.print(String(flexValues[6]));
  Serial.print(",");
  Serial.print(String(flexValues[7]));
  Serial.print(",");
  Serial.print(String(flexValues[8]));
  Serial.print(",");
  Serial.print(String(flexValues[8]));
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
  Serial.print(accelX2);
  Serial.print(",");
  Serial.print(accelY2);
  Serial.print(",");
  Serial.print(accelZ2);
  Serial.print(",");
  Serial.print(gForceX2);
  Serial.print(",");
  Serial.print(gForceY2);
  Serial.print(",");
  Serial.print(gForceZ2);
  Serial.print(",");
  Serial.print(gyroX2);
  Serial.print(",");
  Serial.print(gyroY2);
  Serial.print(",");
  Serial.print(gyroZ2);
  Serial.print("\n");
  
}
