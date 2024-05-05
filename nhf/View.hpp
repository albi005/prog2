#pragma once

#include "Canvas.hpp"
#include <stack>

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

class StackablePage;

/// A stack of pages, drawn on top of each other
class PageStack : public View {
    std::stack<StackablePage*> pages;

  public:
    void push(StackablePage* page);
    void pop();
    virtual void draw(ICanvas& canvas) override;
    ~PageStack() override;
};

/// Convenience class for pages that can be pushed onto a PageStack.
/// Stores a reference to the PageStack
class StackablePage : public virtual View {
    PageStack& pageStack;

  public:
    explicit StackablePage(PageStack& pageStack);
    void pop();
    void push(StackablePage* page);
};
