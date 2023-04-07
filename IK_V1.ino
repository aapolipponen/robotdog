#include <Servo.h>
#include <Wire.h>
#include <math.h>


Servo A1, B1

#define PI 3.14159265

float B1_Lenght = 150;
float B2_Lenght = 150;

float A1_Angle = 45;
float B1_Angle = 45;

// Define arm Constants
const float a = B1_Lenght * 0.1;      // lower joint length converted from mm to cm
const float b = B2_Lenght * 0.1;      // upper joint length converted from mm to cm

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

const float pi = M_PI;  //Store pi in a less annoying format



void setup() {
  A1.attach(1);         //A1 Servo
  B1.attach(0);         //B1 Servo
  Serial.begin(9600);             //For debugging
  Serial.println("Initializing Servos...");
  ResetServos();
}



void loop() {
  FixCoordinates(10, 10);           // Enter coordinates of point.
  inverseKinematics();         // Calculate angles of servos
  ServoMovement();                        //Move servos
  delay(30);
}

// Get x and y measured from the bottom of the base. Function corrects for offset
void FixCoordinates(float x_input, float y_input)
{
 x = x_input + X_CorrectionFactor;
 y = y_input + Y_CorrectionFactor;
}

// Calculate necessary servo angles to move arm to desired points
void inverseKinematics() {
  c = sqrt( sq(x) + sq(y) );                                            // pythagorean theorem
  B = (acos( (sq(b) - sq(a) - sq(c))/(-2*a*c) )) * (180/pi);            // Law of cosines: Angle opposite upper arm section
  C = (acos( (sq(c) - sq(b) - sq(a))/(-2*a*b) )) * (180/pi);            // Law of cosines: Angle opposite hypotenuse
  theta = (asin( y / c )) * (180/pi);                                   // Solve for theta to correct for lower joint's impact on upper joint's angle
  B1_Angle = B + theta + S_1_CorrectionFactor;                    // Find necessary angle. Add Correction
  A1_Angle = C + S_2_CorrectionFactor;                            // Find neceesary angle. Add Correction
}

// Update / move the servos
void ServoMovement() {
  A1.write(A1_Angle);
  B1.write(B1_Angle);
}



