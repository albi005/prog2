#pragma once

#include "Canvas.hpp"
#include <vector>

class View {
  public:
    View(const View&) = delete; // disable copying of views
    void operator=(const View&) = delete;

    View() = default;
    virtual void draw(ICanvas& canvas) = 0; // non-const to allow caching
    virtual bool handleInput(char input);
    virtual ~View() = default;
};

/// A View that delegates drawing and input handling to its child View
class ContentView : public virtual View {
    View* content;

  protected:
    explicit ContentView(View* content);

  public:
    virtual void draw(ICanvas& canvas) override;
    virtual bool handleInput(char input) override;
    virtual ~ContentView() override;
};

/// A ContentView with padding
class PaddingView final : public ContentView {
    int l, t, r, b;

    void draw(ICanvas& canvas) override;

  public:
    PaddingView(View* content, int l, int t, int r, int b);
    PaddingView(View* content, int x, int y);
};

/// A stack of pages, drawn on top of each other
class PageStack final : public View {
    std::vector<View*> pages;

    Color getSurfaceColor(size_t level) const;

  public:
    void push(View* page); // takes ownership
    void draw(ICanvas& canvas) override;
    bool handleInput(char input) override;
    size_t size() const;
    ~PageStack() override;
};
