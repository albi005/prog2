#pragma once

#include <cstdint>
#include <iostream>
#include <string>

// 32-bit ARGB color
struct Color {
    uint32_t argb;

  public:
    /*implicit*/ Color(uint32_t argb); // NOLINT(*-explicit-constructor)
    uint32_t r() const;
    uint32_t g() const;
    uint32_t b() const;
    void printRgb(std::ostream& os);
    bool operator==(const Color& other) const;
};

std::ostream& operator<<(std::ostream& os, Color color);

struct Size;

struct Point {
    int x, y;

  public:
    Point(int x, int y);
    /*implicit*/ Point(const Size& size); // NOLINT(*-explicit-constructor)
};

struct Size {
    int w, h;

    Size() = default;

    Size(int w, int h);

    /*implicit*/ Size(const Point& point); // NOLINT(*-explicit-constructor)
};

struct Rect {
    int x, y, w, h;
};

class ICanvas {
  public:
    virtual Size getSize() const = 0;

    virtual void drawText(const std::string& text, Color fg, Color bg) = 0;

    virtual void
        drawText(const std::string& text, Point pos, Color fg, Color bg) = 0;
};

class PaddedCanvas final : public ICanvas {
    int l, t, r, b;
    ICanvas& inner;

    virtual void drawText(const std::string& text, Color fg, Color bg) override;

    virtual void drawText(
        const std::string& text, Point pos, Color fg, Color bg
    ) override;

    virtual Size getSize() const override;

  public:
    PaddedCanvas(int l, int t, int r, int b, ICanvas& inner);
};
