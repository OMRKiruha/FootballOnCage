
#include <algorithm>
#include <cmath>

#include "View.h"


inline constexpr double maxZoom = 40.;
inline constexpr double minZoom = 10.;
inline constexpr double initialZoom = 20;
inline constexpr double zoomCoef = 0.01;
inline constexpr double minScale = 0.01;

View::View(const Point &viewPoint, double screenWidth, double screenHeight,
           double scale)
        : zoomValue{initialZoom}, viewPoint{viewPoint}, screenWidth{screenWidth},
          screenHeight{screenHeight}, scale_{scale} {
    onZoom(0.);
}

Point View::toScreen(const Point &worldPos) const {
    // Не самая эффективная, но тривиальная реализация
    // перехода от мировых координат к экранным

    // Смещаем worldPos относительно наблюдаемой точки, масштабируем и центруем на экране
    // (чтобы наблюдаемая точка оказалась в центре)
    Point screenPos = (worldPos - viewPoint) * scale_ + Point(screenWidth / 2., screenHeight / 2);

    // инвертируем ось y
    screenPos.y = screenHeight - screenPos.y;
    return screenPos;
}

void View::onZoom(double step) {
    zoomValue = std::clamp(zoomValue + step, minZoom, maxZoom);
    scale_ = std::exp(zoomValue * zoomCoef) - 1. + minScale;
}

double View::scale() const {
    return scale_;
}
