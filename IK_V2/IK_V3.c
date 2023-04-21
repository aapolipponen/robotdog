#include <stdio.h>
#include <math.h>

#define PI 3.14159265

#define A1_LENGTH 75 // length of link between A1 servo and A2 joint
#define A2_LENGTH 150 // length of link between A2 joint and B2 joint
#define B1_LENGTH 150 // length of upper leg segment
#define B2_LENGTH 225 // length of lower leg segment
#define A1_MIN_ANGLE -90 // minimum angle for A1 servo
#define A1_MAX_ANGLE 90 // maximum angle for A1 servo
#define B1_MIN_ANGLE 0 // minimum angle for B1 servo
#define B1_MAX_ANGLE 180 // maximum angle for B1 servo

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

    A1_Angle = (theta1 + 45) * 180 / PI; // convert to degrees for servo A1
    B1_Angle = (theta1 + theta2 - 45) * 180 / PI; // convert to degrees for servo B1

    // limit the servo angles to valid range
    if (A1_Angle < A1_MIN_ANGLE || A1_Angle > A1_MAX_ANGLE) {
        printf("Error: A1 servo angle out of range (%.2f degrees)\n", A1_Angle);
        A1_Angle = fmin(fmax(A1_Angle, A1_MIN_ANGLE), A1_MAX_ANGLE);
    }
    if (B1_Angle < B1_MIN_ANGLE || B1_Angle > B1_MAX_ANGLE) {
        printf("Error: B1 servo angle out of range (%.2f degrees)\n", B1_Angle);
        B1_Angle = fmin(fmax(B1_Angle, B1_MIN_ANGLE), B1_MAX_ANGLE);
    }

    printf("B1 Servo angle: %.2f\n", B1_Angle); // output B1 servo angle
    printf("A1 Servo angle: %.2f\n", A1_Angle); // output A1 servo angle

    return 0;
}
