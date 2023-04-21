#include <math.h>
#include <stdio.h>
#include "gfx.h"

#define A1_LENGTH 75
#define A2_LENGTH 150
#define B1_LENGTH 150
#define B2_LENGTH 225

// Define the position of the origin
int origin_x = 500, origin_y = 800;

// Initialize variables for the coordinates of each point
float a1_x, a1_y, a2_x, a2_y, b1_x, b1_y, b2_x, b2_y, p_x, p_y;

#define PI 3.14159265358979323846

// function to calculate inverse kinematics
void inverseKinematics(int x, int y, float *a1Angle, float *b1Angle, float *a1x, float *a1y, float *a2x, float *a2y, float *b1x, float *b1y, float *b2x, float *b2y) {
  float r2 = x * x + y * y;

  // calculate A1 angle
  float alpha = atan2(y, x);
  float beta = acos((A1_LENGTH * A1_LENGTH + r2 - A2_LENGTH * A2_LENGTH) / (2 * A1_LENGTH * sqrt(r2)));
  *a1Angle = (alpha - beta) * 180 / PI + 45;

  // calculate A1 coordinates
  *a1x = origin_x;
  *a1y = origin_y;
  
  // calculate A2 coordinates
  *a2x = A1_LENGTH * cos(*a1Angle * PI / 180.0) + *a1x;
  *a2y = A1_LENGTH * sin(*a1Angle * PI / 180.0) + *a1y;
  
  // calculate B1 angle
  float gamma = acos((A2_LENGTH * A2_LENGTH + B1_LENGTH * B1_LENGTH - B2_LENGTH * B2_LENGTH) / (2 * A2_LENGTH * B1_LENGTH));
  float delta = acos((B1_LENGTH * B1_LENGTH + B2_LENGTH * B2_LENGTH - r2) / (2 * B1_LENGTH * B2_LENGTH));
  *b1Angle = (gamma + delta - PI / 2) * 180 / PI - 45;

  // calculate B1 coordinates
  *b1x = A2_LENGTH * cos(*a1Angle * PI / 180.0) + *a1x;
  *b1y = A2_LENGTH * sin(*a1Angle * PI / 180.0) + *a1y;
  
  // calculate B2 coordinates
  *b2x = B1_LENGTH * cos(*b1Angle * PI / 180.0) + *b1x;
  *b2y = B1_LENGTH * sin(*b1Angle * PI / 180.0) + *b1y;
}

int main() {
  int x, y;
  float a1_x = 0, a1_y = 0, a2_x = 0, a2_y = 0, b1_x = 0, b1_y = 0, b2_x = 0, b2_y = 0;
  printf("Enter x, y coordinates of foot (in mm): ");
  scanf("%d %d", &x, &y);
  float tempx = x;
  float tempy = y;

  // calculate servo angles and coordinates of leg points
  float a1Angle, b1Angle;
  inverseKinematics(x, y, &a1Angle, &b1Angle, &a1_x, &a1_y, &a2_x, &a2_y, &b1_x, &b1_y, &b2_x, &b2_y);

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

  // initialize graphics window
  gfx_open(1000, 1000, "IK Visualization");

  // set drawing color to black
  gfx_color(0,255,0);

  // draw initial leg position
  gfx_line(origin_x, origin_y, b1_x, b1_y);
  gfx_line(b1_x, b1_y, b2_x, b2_y);
  gfx_line(origin_x, origin_y, a1_x, a1_y);
  gfx_line(a1_x, a1_y, a2_x, a2_y);
  gfx_line(a2_x, a2_y, tempx, tempy);

  // output results
  printf("A1 servo angle: %.2f degrees\n", a1Angle);
  printf("B1 servo angle: %.2f degrees\n", b1Angle);

  // draw new leg position
  gfx_line(origin_x, origin_y, b1_x, b1_y);
  gfx_line(b1_x, b1_y, b2_x, b2_y);
  gfx_line(origin_x, origin_y, a1_x, a1_y);
  gfx_line(a1_x, a1_y, a2_x, a2_y);
  gfx_line(a2_x, a2_y, tempx, tempy);

  while (1) {
    if (gfx_event_waiting()) {
      if (gfx_wait() == 'q') {
        return 0;
      }
    }
  }
}
