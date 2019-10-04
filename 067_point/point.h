#include <math.h>
class Point
{
 private:
  double x;
  double y;

 public:
  Point() : x(0), y(0) {}
  void move(double dx, double dy) {
    x += dx;
    y += dy;
  }
  double distanceFrom(const Point & p) {
    double dist = 0;
    dist = pow((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y), 1.0 / 2);
    return dist;
  }
};
