#include "Canvas.hpp"
#include "utils.hpp"

Color::Color(uint32_t argb) : argb(argb) {}

Color::Color(const Color& other) : argb(other.argb) {}

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

std::ostream& PaddedCanvas::setPosition(Point pos) {
    pos.x += l;
    pos.y += t;
    return inner.setPosition(pos);
}

Color PaddedCanvas::getSurfaceColor() const { return inner.getSurfaceColor(); }

void PaddedCanvas::setSurfaceColor(Color color) {
    inner.setSurfaceColor(color);
}

std::ostream& PaddedCanvas::draw(Point pos, Color fg, Color bg) {
    pos.x += l;
    pos.y += t;
    return inner.draw(pos, fg, bg);
}

std::ostream& PaddedCanvas::draw(Color fg, Color bg) {
    return inner.draw(fg, bg);
}

std::ostream& PaddedCanvas::draw(Color fg) { return inner.draw(fg); }

std::ostream& PaddedCanvas::draw() { return inner.draw(); }

void PaddedCanvas::fill(Rect area, Color bg) {
    area.x += l;
    area.y += t;
    inner.fill(area, bg);
}

PaddedCanvas::PaddedCanvas(int l, int t, int r, int b, ICanvas& inner)
    : l(l), t(t), r(r), b(b), inner(inner) {}

Clip::Clip(const std::string& s, size_t maxLen) : s(s), maxLen(maxLen) {}

void Clip::write(std::ostream& os) {
    size_t actualWritten = 0;
    for (size_t i = 0; i < s.size() && actualWritten < maxLen;) {
        os << s[i++];
        actualWritten++;
        while (utils::isContinuationByte(s[i]))
            os << s[i++];
    }
}

std::ostream& operator<<(std::ostream& os, Clip clip) {
    clip.write(os);
    return os;
}

SearchedString::SearchedString(
    const std::string& s,
    size_t start,
    size_t length,
    size_t maxLen,
    Color textColor,
    Color highlightColor,
    Color surfaceColor
)
    : s(s), start(start), length(length), maxLen(maxLen), textColor(textColor),
      highlightColor(highlightColor), surfaceColor(surfaceColor) {}

void SearchedString::draw(ICanvas& canvas) const {
    size_t actualWritten = 0;
    canvas.draw(textColor, surfaceColor);
    for (size_t i = 0; i < s.size() && actualWritten < maxLen;) {
        if (i == start)
            canvas.draw(highlightColor);
        else if (i == start + length)
            canvas.draw(textColor);

        canvas.draw() << s[i++];
        actualWritten++;

        while (utils::isContinuationByte(s[i]))
            canvas.draw() << s[i++];
    }
}