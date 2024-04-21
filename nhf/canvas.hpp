#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <cstdint>
#include <iostream>
#include <string>

typedef uint32_t Color;
struct Size;
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    Point(const Size& size);
};
struct Size {
    int w, h;
    Size(int w, int h) : w(w), h(h) {}
    Size(const Point& point) : w(point.x), h(point.y) {}
};
inline Point::Point(const Size& size) : x(size.w), y(size.h) {}
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

class OstreamCanvas : public ICanvas {
    std::ostream& os;

  protected:
    int width, height;

  public:
    OstreamCanvas(std::ostream& os) : os(os) {}
    bool handleEscapeCode(std::istream&);
    Size getSize() const { return Size(width, height); }
    void drawText(const std::string& text, Color fg, Color bg);
    void drawText(const std::string& text, Point pos, Color fg, Color bg);
};

class PaddedCanvas : public ICanvas {
    int l, t, r, b;
    ICanvas& inner;
    virtual void
        drawText(const std::string& text, Point pos, Color fg, Color bg) {
        ICanvas::drawText(text, Point(pos.x + l, pos.y + t), fg, bg);
    }
    virtual Size getSize() const {
        Size orig = inner.getSize();
        return Size(orig.w - l - r, orig.h - t - b);
    }

  public:
    PaddedCanvas(int l, int t, int r, int b, ICanvas& inner)
        : l(l), t(t), r(r), b(b), inner(inner) {}
    PaddedCanvas(int x, int y, ICanvas& inner)
        : PaddedCanvas(x, y, x, y, inner) {}
};

#endif
