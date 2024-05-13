#pragma once

#include "Canvas.hpp"

class OstreamCanvas final : public ICanvas {
    int width = 0, height = 0;
    Color currFgColor = 1, currBgColor = 1;
    std::ostream& os;
    Color surfaceColor = 0x800080; // purple
    bool cursorPosRequestFinished = true;

  public:
    explicit OstreamCanvas(std::ostream& os);
    void updateScreenSize(std::istream& is);
    Size getSize() const override;
    Color getSurfaceColor() const override;
    void setSurfaceColor(Color color) override;
    std::ostream& draw(Point pos, Color fg, Color bg) override;
    std::ostream& draw(Point pos) override;
    std::ostream& draw(Color fg, Color bg) override;
    std::ostream& draw(Color fg) override;
    std::ostream& draw() override;
    void fill(Rect area, Color bg) override;

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