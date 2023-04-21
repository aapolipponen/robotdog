//#include <Servo.h>
//#include <Wire.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

//Servo A1, B1

#define sq = sqrt(x); 

#define PI 3.14159265

float B1_Lenght = 150;
float B2_Lenght = 150;

float A1_Angle = 45;
float B1_Angle = 45;

// Define arm Constants
#define A_LENGTH (B1_Length * 0.1)     // lower joint length converted from mm to cm
#define B_LENGTH (B2_Length * 0.1)      // upper joint length converted from mm to cm

// Correction factors to align servo values with their respective axis
const float S_1_CorrectionFactor = -10;     // Align arm "a" with the horizontal when at 0 degrees
const float S_2_CorrectionFactor = -77;     // Align arm "b" with arm "a" when at 0 degrees

// Correction factor to shift origin out to edge of the mount
const float X_CorrectionFactor = 6.5;       // X direction correction factor (cm)
const float Y_CorrectionFactor = -4;       // Y direction correction factor (cm)

float A;            //Angle oppposite side a (between b and c)
float B;            //Angle oppposite side b
float C;            //Angle oppposite side c
float theta;        //Angle formed between line from origin to (x,y) and the horizontal

float x;            // x position (cm)
float y;            // y position (cm)
float c;            // Hypotenuse legngth in cm



void setup() {
//  A1.attach(1);         //A1 Servo
//  B1.attach(0);         //B1 Servo
//  Serial.begin(9600);             //For debugging
//  Serial.println("Initializing Servos...");
  ResetServos();
}



void loop() {
  FixCoordinates(10, 10);           // Enter coordinates of point.
  inverseKinematics();         // Calculate angles of servos
  ServoMovement();                        //Move servos
  //delay(30);
  waitFor(30);
}

// Get x and y measured from the bottom of the base. Function corrects for offset
void FixCoordinates(float x_input, float y_input)
{
 x = x_input + X_CorrectionFactor;
 y = y_input + Y_CorrectionFactor;
}

void ResetServos() {
  A1_Angle = 0;
  B1_Angle = 0;
}

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

// Calculate necessary servo angles to move arm to desired points
void inverseKinematics() {
  float r = sqrt(x * x + y * y); // calculate distance from origin to (x, y)
  float cosBeta = (r * r + a * a - b * b) / (2 * r * a);
  float sinBeta = sqrt(1 - cosBeta * cosBeta);

  // calculate servo angles
  A1_Angle = atan2(y, x) * 180 / PI - atan2(a * sinBeta, r - a * cosBeta) * 180 / PI;
  B1_Angle = -acos((r - a * cosBeta) / b) * 180 / PI;

  // add correction factors
  A1_Angle += S_1_CorrectionFactor;
  B1_Angle += S_2_CorrectionFactor;
}


// Update / move the servos
void ServoMovement() {
//  A1.write(A1_Angle);
//  B1.write(B1_Angle);
printf("floats: %4.2f %+.0e %E \n", A1_Angle);
printf("floats: %4.2f %+.0e %E \n", B1_Angle);
}