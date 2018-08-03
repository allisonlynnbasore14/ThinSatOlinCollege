#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>

#include <SPI.h>
#include <SD.h>

Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();
const int chipSelect = 10;
int timer = 0;
const int delayVal = 50;
// The sample rate for the accelormeter data is 20 HZ with a delay.
// Therefore, the time units for the start and durations are in 5/6 of a second: i.e. a duration of 100 is ~83 seconds.

// Burn Wire Setup
const int burnWirePin = 7;
int burnTick = 0;
const int burnStart = 72; // in 5/6 seconds
const int burnDuration = 100;

// DC motor with H Bridge Setup
const int motorClockPin = 8;    // Turn the motor Clockwise
const int motorCounterPin = 9;    // Turn the motor Counter Clockwise
int motorTick = 0;
const int motorStart = 100; // in 5/6 seconds
const int motorDuration = 100;


// Solenoid with Relay (Or any other 5V mechanism with a relay)
const int SolenoidPin = 5;
int soleTick = 0;
const int soleStart = 100;
const int soleDuration = 100;
=+++
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

  pinMode(burnWirePin, OUTPUT);

  pinMode(motorClockPin, OUTPUT);
  pinMode(motorCounterPin, OUTPUT);

  pinMode(SolenoidPin, OUTPUT);
  
  pinMode(13, OUTPUT);
  
  if (!lsm.begin())
  {
    Serial.println("Unable to initialize the LSM9DS1. Check your wiring.");
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

  // DC WITH H BRIDGE MOTOR -------------------------------------------

   if(motorTick > motorStart && motorTick < motorStart + motorDuration){
      digitalWrite(motorClockPin, HIGH);
   }
  
   if(motorTick > motorStart + motorDuration && motorTick < motorStart + 2*motorDuration){
      digitalWrite(motorClockPin, LOW);
   }

   motorTick = motorTick +1;
   
  // BURN WIRE --------------------------------------------------------
  if(burnTick > burnStart  && burnTick < burnStart + burnDuration){
    digitalWrite(burnWirePin,HIGH);
  }
  if(burnTick > burnStart + burnDuration && burnTick < burnStart + 2*burnDuration){
    digitalWrite(burnWirePin,LOW);
  }
  burnTick = burnTick +1;


  // SOLENOID WITH RELAY ---------------------------------------------
  if(soleTick > soleStart && soleTick < soleStart + soleDuration){
    digitalWrite(SolenoidPin, HIGH);
  }
  if(soleTick > soleStart + soleDuration && soleTick < soleStart + 2*soleDuration){
    digitalWrite(SolenoidPin, LOW);
  }

  soleTick = soleTick + 1;

  // READ AND SAVE ACCEL DATA -----------------------------------------
  timer = timer+1;
  
  lsm.read();   
  sensors_event_t a, m, g, temp;
  lsm.getEvent(&a, &m, &g, &temp); 
  
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
    
    delay(delayVal); // Samples once every 50 milliseconds, 20Hz
}

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
