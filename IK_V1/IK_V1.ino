//#include <Servo.h>
#include <Wire.h>
#include <math.h>

#define PI 3.14159265

const float pi = M_PI;  //Store pi in a less annoying format

Servo myservo1, myservo2;

float B1_Lenght = 150;
float B2_Lenght = 150;

float A1_Angle = 45;
float B1_Angle = 45;

// Define arm Constants
const float a = B1_Lenght * 0.1;      // lower joint length converted from mm to cm
const float b = B2_Lenght * 0.1;      // upper joint length converted from mm to cm

//TODO: Fix the numbers
// Correction factors to align servo values with their respective axis
const float S_1_CorrectionFactor = -10;     // Align arm "a" with the horizontal when at 0 degrees
const float S_2_CorrectionFactor = -77;     // Align arm "b" with arm "a" when at 0 degrees

//TODO: Fix the numbers
// Correction factor to shift origin out to edge of the mount
const float X_CorrectionFactor = 6.5;       // X direction correction factor (cm)
const float Y_CorrectionFactor = -4;       // Y direction correction factor (cm)

float A;            //Angle oppposite side a (between b and c)
float B;            //Angle oppposite side b
float C;            //Angle oppposite side c
float theta;        //Angle formed between line from origin to (x,y) and the horizontal

float x;            // x position (cm)
float y;            // y position (cm)
float c;            // Hypotenuse length in cm



void setup() {
  myservo1.attach(1);         //A1 Servo
  myservo2.attach(0);         //B1 Servo
  Serial.begin(9600);             //For debugging
  Serial.println("Initializing Servos...");
  //servo_base();
  servo_center();
}

void loop() {
  FixCoordinates(10, 10);           // Enter coordinates of point.
  inverseKinematics();         // Calculate angles of servos
  printvalues();
  //ServoMovement();                        //Move servos
  delay(1000); // wait for one second before printing again
  //delay(30);
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

void printvalues() {
//  Serial.println(A);
//  Serial.println(B);
//  Serial.println(C);
//  Serial.println(theta);
  Serial.println(A1_Angle);
  Serial.println(B1_Angle);
}

void servo_center() {
  myservo1.write(90);
  myservo2.write(90);
}


void servo_base() {
  myservo1.write(0);
  myservo2.write(0);
}

// Update / move the servos
void ServoMovement() {
  myservo1.write(A1_Angle);
  myservo2.write(B1_Angle);
}

//void servo_center() {
  //A1.write(90);
  //B1.write(90);
//}


//void servo_base() {
  //A1.write(0);
  //B1.write(90);
//}

// Update / move the servos
//void ServoMovement() {
  //A1.write(A1_Angle);
  //B1.write(B1_Angle);
//}



