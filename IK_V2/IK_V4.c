#include <math.h>
#include <stdio.h>

#define A1_LENGTH 75
#define A2_LENGTH 150
#define B1_LENGTH 150
#define B2_LENGTH 225

#define PI 3.14159265358979323846

// function to calculate inverse kinematics
void inverseKinematics(int x, int y, float *a1Angle, float *b1Angle) {
  float r2 = x * x + y * y;

  // calculate A1 angle
  float alpha = atan2(y, x);
  float beta = acos((A1_LENGTH * A1_LENGTH + r2 - A2_LENGTH * A2_LENGTH) / (2 * A1_LENGTH * sqrt(r2)));
  *a1Angle = (alpha - beta) * 180 / PI + 45;

  // calculate B1 angle
  float gamma = acos((A2_LENGTH * A2_LENGTH + B1_LENGTH * B1_LENGTH - B2_LENGTH * B2_LENGTH) / (2 * A2_LENGTH * B1_LENGTH));
  float delta = acos((B1_LENGTH * B1_LENGTH + B2_LENGTH * B2_LENGTH - r2) / (2 * B1_LENGTH * B2_LENGTH));
  *b1Angle = (gamma + delta - PI / 2) * 180 / PI - 45;
}

int main() {
  int x, y;
  
  printf("Enter x, y coordinates of foot (in mm): ");
  scanf("%d %d", &x, &y);

  // calculate servo angles
  float a1Angle, b1Angle;
  inverseKinematics(x, y, &a1Angle, &b1Angle);

  // limit servo angles to range [-90, 90]
  if (a1Angle < -90) {
    a1Angle = -90;
  } else if (a1Angle > 90) {
    a1Angle = 90;
  }
  if (b1Angle < -90) {
    b1Angle = -90;
  } else if (b1Angle > 90) {
    b1Angle = 90;
  }

  // output results
  printf("A1 servo angle: %.2f degrees\n", a1Angle);
  printf("B1 servo angle: %.2f degrees\n", b1Angle);

  return 0;
}