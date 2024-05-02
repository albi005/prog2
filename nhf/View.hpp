#pragma once

#include "Canvas.hpp"
#include <stack>

class View {
  public:
    // disable copying
    View(const View&) = delete;
    void operator=(const View&) = delete;

    View() = default;
    virtual void draw(ICanvas& canvas) = 0; // non-const to allow caching
    virtual bool handleInput(char input);
    virtual ~View() = default;
};

class ContentView : public virtual View {
    View* content;

  protected:
    explicit ContentView(View* content);

  public:
    virtual void draw(ICanvas& canvas) override;
    virtual bool handleInput(char input) override;
    virtual ~ContentView() override;
};

class Padding final : public ContentView {
    int l, t, r, b;

    void draw(ICanvas& canvas) override;

  public:
    Padding(View* content, int l, int t, int r, int b);
    Padding(View* content, int x, int y);
};

class StackablePage;

class PageStack : public View {
    std::stack<StackablePage*> pages;

  public:
    void push(StackablePage* page);
    void pop();
    virtual void draw(ICanvas& canvas) override;
    ~PageStack() override;
};

class StackablePage : public virtual View {
    PageStack& pageStack;

  public:
    explicit StackablePage(PageStack& pageStack);
    void pop();
    void push(StackablePage* page);
};
