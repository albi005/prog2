#pragma once

#include <cstdint>
#include <iostream>
#include <string>

// 32-bit ARGB color
struct Color {
    uint32_t argb;

  public:
    /*implicit*/ Color(uint32_t argb); // NOLINT(*-explicit-constructor)
    Color(const Color& other);

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
    virtual std::ostream& draw(Point pos) = 0;

    virtual Color getSurfaceColor() const = 0;
    virtual void setSurfaceColor(Color color) = 0;

    /// Moves the cursor to pos and sets the foreground and background color.
    /// @returns the stream to draw on.
    virtual std::ostream& draw(Point pos, Color fg, Color bg) = 0;

    /// @brief Sets the foreground and background color.
    /// @returns the stream to draw on.
    /// @details Does not move the cursor.
    virtual std::ostream& draw(Color fg, Color bg) = 0;

    /// @brief Sets the foreground color.
    /// @returns the stream to draw on.
    /// @details Does not move the cursor.
    virtual std::ostream& draw(Color fg) = 0;

    /// @returns the stream to draw on.
    /// @details Does not move the cursor.
    virtual std::ostream& draw() = 0;

    virtual void fill(Rect area, Color bg) = 0;
};

class PaddedCanvas final : public ICanvas {
    int l, t, r, b;
    ICanvas& inner;

  public:
    PaddedCanvas(int l, int t, int r, int b, ICanvas& inner);
    Size getSize() const override;
    Color getSurfaceColor() const override;
    void setSurfaceColor(Color color) override;
    std::ostream& draw(Point pos, Color fg, Color bg) override;
    std::ostream& draw(Point pos) override;
    std::ostream& draw(Color fg, Color bg) override;
    std::ostream& draw(Color fg) override;
    std::ostream& draw() override;
    void fill(Rect area, Color bg) override;
};

/// @brief Clips a string to a maximum length.
class Clip {
    const std::string& s;
    size_t maxLen;

  public:
    Clip(const std::string& s, size_t maxLen);
    void write(std::ostream& os);
};

std::ostream& operator<<(std::ostream& os, Clip clip);

class SearchedString {
    const std::string& s;
    const size_t start;
    const size_t length;
    const size_t maxLen;
    const Color textColor;
    const Color highlightColor;
    const Color surfaceColor;

  public:
    SearchedString(
        const std::string& s,
        size_t start,
        size_t length,
        size_t maxLen,
        Color textColor,
        Color highlightColor,
        Color surfaceColor
    );
    void draw(ICanvas& canvas) const;
};
