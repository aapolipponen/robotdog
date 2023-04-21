#include <stdio.h>
#include <math.h>

#define PI 3.14159265

#define B1_LENGTH 150 // length of upper leg segment
#define B2_LENGTH 150 // length of lower leg segment

int main()
{
    float x, y; // coordinates of end effector
    float l1 = B1_LENGTH, l2 = B2_LENGTH; // lengths of links
    float theta1, theta2; // joint angles
    float A1_Angle, B1_Angle; // angles for servos

    printf("Enter the coordinates of the end effector (x,y): ");
    scanf("%f %f", &x, &y);

    float r = sqrt(x*x + y*y); // distance from origin to end effector
    float phi = atan2(y, x); // angle from x-axis to end effector

    float alpha = acos((l1*l1 + r*r - l2*l2) / (2*l1*r)); // angle between links
    theta1 = phi - alpha; // first joint angle

    float beta = acos((l1*l1 + l2*l2 - r*r) / (2*l1*l2)); // angle between links
    theta2 = PI - beta; // second joint angle

    A1_Angle = theta1 * 180 / PI; // convert to degrees for servo
    B1_Angle = (theta1 + theta2) * 180 / PI; // convert to degrees for servo

    printf("B1 Servo angle: %.2f\n", B1_Angle); // output B1 servo angle
    printf("A1 Servo angle: %.2f\n", A1_Angle); // output A1 servo angle

    return 0;
}
