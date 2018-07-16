#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>

#include <SPI.h>
#include <SD.h>

Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();
const int chipSelect = 10;
int timer = 0;
#define LSM9DS1_SCK A5
#define LSM9DS1_MISO 12
#define LSM9DS1_MOSI A4
#define LSM9DS1_XGCS 6
#define LSM9DS1_MCS 5


void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}

void setup() {

  Serial.begin(115200);
  while (!Serial) {
    delay(1); // will pause Zero, Leonardo, etc until serial console opens
  }
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
  setupSensor();
}

void loop() {

  timer = timer+1;
  
  lsm.read();  /* ask it to read in the data */ 

  /* Get a new sensor event */ 
  sensors_event_t a, m, g, temp;

  lsm.getEvent(&a, &m, &g, &temp); 
// Acceleration in m/s^2
//  a.acceleration.x
//  a.acceleration.y
//  a.acceleration.z

// Magnetometer in gauss
//  m.magnetic.x
//  m.magnetic.y
//  m.magnetic.z

// Gyro in dps
//  g.gyro.x
//  g.gyro.y
//  g.gyro.z

  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("dataVals.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile && timer<50) {
    dataFile.print("AX:"); dataFile.print(" ");dataFile.print(a.acceleration.x); dataFile.print(" ");
    dataFile.print("AY:"); dataFile.print(" "); dataFile.print(a.acceleration.y); dataFile.print(" ");
    dataFile.print("AZ:"); dataFile.print(" "); dataFile.print(a.acceleration.z); dataFile.print(" ");
    dataFile.print("MX:"); dataFile.print(" "); dataFile.print(m.magnetic.x); dataFile.print(" ");
    dataFile.print("MY:"); dataFile.print(" "); dataFile.print(m.magnetic.y); dataFile.print(" ");
    dataFile.print("MZ:"); dataFile.print(" "); dataFile.print(m.magnetic.z); dataFile.print(" ");
    dataFile.print("GX:"); dataFile.print(" "); dataFile.print(g.gyro.x); dataFile.print(" ");
    dataFile.print("GY:"); dataFile.print(" "); dataFile.print(g.gyro.y); dataFile.print(" ");
    dataFile.print("GZ:"); dataFile.print(" "); dataFile.print(g.gyro.z); dataFile.print(" ");
    dataFile.print("time"); dataFile.print(" "); dataFile.print("0"); dataFile.print(" ");
    dataFile.println();

    dataFile.close();
  }
  else {
    Serial.println("error opening datalog.txt or ran out of time");
  }

    delay(200);
}











