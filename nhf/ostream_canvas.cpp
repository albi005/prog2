#include "ostream_canvas.hpp"

#define ESC "\x1b"

OstreamCanvas::OstreamCanvas(std::ostream& os) : os(os) {}

void OstreamCanvas::updateScreenSize(std::istream& is) {
    setCursorPosition({9999, 9999});
    os << ESC "[6n"; // ask for cursor position

    // response is ESC[y;xR
    is >> Expect(ESC "[") >> height >> Expect(";") >> width >> Expect("R");
}

Size OstreamCanvas::getSize() const { return {width, height}; }

void OstreamCanvas::drawText(const std::string& text, Color fg, Color bg) {
    setForegroundColor(fg);
    setBackgroundColor(bg);
    os << text;
}

void OstreamCanvas::drawText(
    const std::string& text, Point pos, Color fg, Color bg
) {
    setCursorPosition(pos);
    drawText(text, fg, bg);
}

// prints ESC[38;2;r;g;bm
void OstreamCanvas::setForegroundColor(Color color) {
    if (currFgColor == color)
        return;
    currFgColor = color;
    os << ESC "[38;2;";
    os << color;
    os << "m";
}

// prints ESC[48;2;r;g;bm
void OstreamCanvas::setBackgroundColor(Color color) {
    if (currBgColor == color)
        return;
    currBgColor = color;
    os << ESC "[48;2;";
    os << color;
    os << "m";
}

// prints ESC[y;xH
void OstreamCanvas::setCursorPosition(Point position) {
    os << ESC << "[" << position.y << ";" << position.x << "H";
}

Expect::Expect(const char* s) : s(s) {}

void Expect::expect(std::istream& is) {
    for (size_t i = 0; s[i] != 0; i++)
        if (is.get() != s[i])
            throw std::runtime_error("unexpected escape sequence");
}

std::istream& operator>>(std::istream& is, Expect expect) {
    expect.expect(is);
    return is;
}
