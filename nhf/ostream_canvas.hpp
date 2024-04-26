#ifndef OSTREAM_CANVAS_H
#define OSTREAM_CANVAS_H

#include "canvas.hpp"

class OstreamCanvas : public ICanvas {
    int width = 0, height = 0;
    Color currFgColor = 1, currBgColor = 1;
    std::ostream& os;

  public:
    explicit OstreamCanvas(std::ostream& os);
    void updateScreenSize(std::istream& is);
    Size getSize() const override;
    void drawText(const std::string& text, Color fg, Color bg) override;
    void drawText(const std::string& text, Point pos, Color fg, Color bg)
        override;

  private:
    void setForegroundColor(Color color);
    void setBackgroundColor(Color color);
    void setCursorPosition(Point position);
};

class Expect {
    const char* s;

  public:
    explicit Expect(const char* s);
    void expect(std::istream& is);
};

std::istream& operator>>(std::istream& is, Expect expect);

#endif