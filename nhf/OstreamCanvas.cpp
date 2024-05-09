#include "OstreamCanvas.hpp"

// Fe Escape sequences
// https://en.wikipedia.org/wiki/ANSI_escape_code#Fe_Escape_sequences
#define ESC "\x1b"

// Control Sequence Introducer
// https://en.wikipedia.org/wiki/ANSI_escape_code#CSI_(Control_Sequence_Introducer)_sequences
#define CSI ESC "["

OstreamCanvas::OstreamCanvas(std::ostream& os) : os(os) {}

void OstreamCanvas::updateScreenSize(std::istream& is) {
    setCursorPosition({9999, 9999});
    os << CSI "6n"; // ask for cursor position

    // response is CSIy;xR
    is >> Expect(CSI) >> height >> Expect(";") >> width >> Expect("R");
}

Size OstreamCanvas::getSize() const { return {width, height}; }

std::ostream& OstreamCanvas::setPosition(Point pos) {
    setCursorPosition(pos);
    return os;
}

std::ostream& OstreamCanvas::draw(Point pos, Color fg, Color bg) {
    setCursorPosition(pos);
    return os;
}

std::ostream& OstreamCanvas::draw(Color fg, Color bg) {
    setForegroundColor(fg);
    setBackgroundColor(bg);
    return os;
}

OstreamCanvas::operator std::ostream&() { return os; }

// prints CSI38;2;r;g;bm
void OstreamCanvas::setForegroundColor(Color color) {
    if (currFgColor == color)
        return;
    currFgColor = color;
    os << CSI "38;2;";
    os << color;
    os << "m";
}

// prints CSI48;2;r;g;bm
void OstreamCanvas::setBackgroundColor(Color color) {
    if (currBgColor == color)
        return;
    currBgColor = color;
    os << CSI "48;2;";
    os << color;
    os << "m";
}

// prints CSIy;xH
void OstreamCanvas::setCursorPosition(Point position) {
    os << CSI << position.y << ";" << position.x << "H";
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
