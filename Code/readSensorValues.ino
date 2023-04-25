#include<Wire.h>
#include<SoftwareSerial.h>

#define thumb  
#define index  
#define middle  
#define ring  
#define pinky

float flexValues[] = {0,0,0,0,0}

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;

void setup(){
  Serial.begin(115200);
  Wire.begin();
  setMPU();
  pinmode(thumb,INPUT);
  pinmode(index,INPUT);
  pinmode(middle,INPUT);
  pinmode(ring,INPUT);
  pinmode(pinky,INPUT);

  printHead();
}

void loop(){
  recordAccelRegisters();
  recordGyroRegisters();
  flexValues[0] = analogRead(thumb);
  flexValues[1] = analogRead(index);
  flexValues[2] = analogRead(middle);
  flexValues[3] = analogRead(ring);
  flexValues[4] = analogRead(pinky);
  printData();
  delay(2500);
}

void setMPU(){
  Wire.beginTransmission(0b1101000);//I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processAccelData();
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processAccelData();
}

void processAccelData(){
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0; 
  gForceZ = accelZ / 16384.0;
}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
}

void printHead(){
  Serial.print("thumb,");
  Serial.print("index,");
  Serial.print("middle,");
  Serial.print("ring,");
  Serial.print("pinky,");
  Serial.print("accelX,");
  Serial.print("accelY,");
  Serial.print("accelZ,");
  Serial.print("gForceX,");
  Serial.print("gForceY,");
  Serial.print("gForceZ,");
  Serial.print("gyroX,");
  Serial.print("gyroY,");
  Serial.print("gyroZ,");
  Serial.print("rotX,");
  Serial.print("rotY,");
  Serial.print("rotZ");
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
  Serial.print(accelX);
  Serial.print(",");
  Serial.print(accelY);
  Serial.print(",");
  Serial.print(accelZ);
  Serial.print(",");
  Serial.print(gForceX);
  Serial.print(",");
  Serial.print(gForceY);
  Serial.print(",");
  Serial.print(gForceZ);
  Serial.print(",");
  Serial.print(gyroX);
  Serial.print(",");
  Serial.print(gyroY);
  Serial.print(",");
  Serial.print(gyroZ);
  Serial.print(",");
  Serial.print(rotX);
  Serial.print(",");
  Serial.print(rotY);
  Serial.print(",");
  Serial.print(rotZ);
  Serial.print("\n");
  
}
