#include "circle.h"

#include <math.h>

Circle::Circle(Point c, double r) : center(c), radius(r) {}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double r1 = radius;
  double r2 = otherCircle.radius;
  double d = center.distanceFrom(otherCircle.center);
  double angle1 = 0;
  double angle2 = 0;
  if (r1 + r2 <= d) {
    return 0.0;
  }
  /*if(r1>r2){
    double tmp=r1;
    r1=r2;
    r2=tmp;
    }*/
  if (d <= fabs(r1 - r2)) {
    if (r1 < r2)
      return M_PI * r1 * r1;
    else
      return M_PI * r2 * r2;
  }
  angle1 = acos((r1 * r1 + d * d - r2 * r2) / (2.0 * r1 * d));
  angle2 = acos((r2 * r2 + d * d - r1 * r1) / (2.0 * r2 * d));
  double fan_area1 = 0.5 * r2 * r2 * angle2 * 2;
  double fan_area2 = 0.5 * r1 * r1 * angle1 * 2;
  double tri_area2 = 0.5 * r2 * r2 * sin(2 * angle2);
  double tri_area1 = 0.5 * r1 * r1 * sin(2 * angle1);

  return fan_area1 + fan_area2 - tri_area1 - tri_area2;
}
