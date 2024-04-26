#include "canvas.hpp"

Color::Color(uint32_t argb) : argb(argb) {}

uint32_t Color::r() const { return (argb >> 16) & 0xff; }

uint32_t Color::g() const { return (argb >> 8) & 0xff; }

uint32_t Color::b() const { return argb & 0xff; }

void Color::printRgb(std::ostream& os) {
    os << r() << ';' << g() << ';' << b();
}

bool Color::operator==(const Color& other) const { return argb == other.argb; }

std::ostream& operator<<(std::ostream& os, Color color) {
    color.printRgb(os);
    return os;
}

Point::Point(int x, int y) : x(x), y(y) {}

Point::Point(const Size& size) : x(size.w), y(size.h) {}

Size::Size(int w, int h) : w(w), h(h) {}

Size::Size(const Point& point) : w(point.x), h(point.y) {}

Size PaddedCanvas::getSize() const {
    Size orig = inner.getSize();
    return Size(orig.w - l - r, orig.h - t - b);
}

void PaddedCanvas::drawText(const std::string& text, Color fg, Color bg) {
    inner.drawText(text, fg, bg);
}

void PaddedCanvas::drawText(
    const std::string& text, Point pos, Color fg, Color bg
) {
    inner.drawText(text, {pos.x + l, pos.y + t}, fg, bg);
}

PaddedCanvas::PaddedCanvas(int l, int t, int r, int b, ICanvas& inner)
    : l(l), t(t), r(r), b(b), inner(inner) {}
