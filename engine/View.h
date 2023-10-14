#pragma once
#include "../Point.h"

class View {
  public:
    View(const Point& viewPoint, double screenWidth, double screenHeight,
         double scale);
    void onZoom(double step);
    [[nodiscard]] Point toScreen(const Point& worldPos) const;
    [[nodiscard]] double scale() const;

  private:
    double zoomValue;
    Point viewPoint;
    double screenWidth;
    double screenHeight;
    double scale_;
};
