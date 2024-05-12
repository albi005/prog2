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
    virtual std::ostream& setPosition(Point pos) = 0;

    /// Moves the cursor to pos and sets the foreground and background color.
    /// @returns the stream to draw on.
    virtual std::ostream& draw(Point pos, Color fg, Color bg) = 0;

    /// @brief Sets the foreground and background color.
    /// @returns the stream to draw on.
    /// @details Does not move the cursor.
    virtual std::ostream& draw(Color fg, Color bg) = 0;

    /// @returns the stream to draw on.
    /// @details Does not move the cursor.
    virtual std::ostream& draw() = 0;

    virtual void fill(Rect area, Color bg) = 0;
};

class PaddedCanvas final : public ICanvas {
    int l, t, r, b;
    ICanvas& inner;

    Size getSize() const override;
    std::ostream& setPosition(Point pos) override;
    std::ostream& draw(Point pos, Color fg, Color bg) override;
    std::ostream& draw(Color fg, Color bg) override;
    std::ostream& draw() override;
    void fill(Rect area, Color bg) override;

  public:
    PaddedCanvas(int l, int t, int r, int b, ICanvas& inner);
};

// https://alb1.hu/#materialcolorutilities btw
#define PRIMARY 0x9BD595
#define ON_PRIMARY 0x00390A
#define PRIMARY_CONTAINER 0x1C511F
#define ON_PRIMARY_CONTAINER 0xB6F2AF
#define SECONDARY 0xEEB8CA
#define ON_SECONDARY 0x492534
#define SECONDARY_CONTAINER 0x623B4A
#define ON_SECONDARY_CONTAINER 0xFFD9E4
#define TERTIARY 0xBEC3FA
#define ON_TERTIARY 0x272C5A
#define TERTIARY_CONTAINER 0x3E4372
#define ON_TERTIARY_CONTAINER 0xDFE0FF
#define ERROR 0xFFB4AB
#define ON_ERROR 0x690005
#define ERROR_CONTAINER 0x93000A
#define ON_ERROR_CONTAINER 0xFFB4AB
#define SURFACE 0x12131A
#define ON_SURFACE 0xE3E1EC
#define ON_SURFACE_VARIANT 0xC7C5D0
#define INVERSE_SURFACE 0xE3E1EC
#define INVERSE_ON_SURFACE 0x2F3038
#define INVERSE_PRIMARY 0x356A35
#define SURFACE_DIM 0x12131A
#define SURFACE_BRIGHT 0x383841
#define SURFACE_CONTAINER_LOWEST 0x0D0E15
#define SURFACE_CONTAINER_LOW 0x1A1B23
#define SURFACE_CONTAINER 0x1F1F27
#define SURFACE_CONTAINER_HIGH 0x292931
#define SURFACE_CONTAINER_HIGHEST 0x34343C
#define OUTLINE 0x91909A
#define OUTLINE_VARIANT 0x46464F
