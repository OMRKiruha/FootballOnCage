#pragma once

#include <istream>

class Color {
  public:
    Color() = default;
    Color(double red, double green, double blue);
    [[nodiscard]] double red() const { return r; };
    [[nodiscard]] double green() const { return g; };
    [[nodiscard]] double blue() const { return b; };

    void setColor(double red, double green, double blue);

  private:
    double r{};
    double g{};
    double b{};
};

