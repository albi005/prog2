#ifndef VIEW_HPP
#define VIEW_HPP

#include "canvas.hpp"
#include <stack>

class View {
    // disable copying
    View(const View&) = delete;
    void operator=(const View&) = delete;

  public:
    View() {}
    virtual void draw(const ICanvas&) = 0; // non-const to allow caching
    virtual bool handleInput(char input) {return false;}
    virtual ~View() {}
};

class ContentView : public View {
    View* content;

  protected:
    ContentView(View* content) : content(content) {}

  public:
    void draw(const ICanvas&);
    bool handleInput(char input);
    virtual ~ContentView() { delete content; }
};

class Padding : public ContentView {
    virtual void draw(const ICanvas&);

  public:
    Padding(View* content) : ContentView(content) {}
};

class StackablePage;
class PageStack : public View {
    std::stack<StackablePage*> pages;

  public:
    void push(StackablePage* page);
    void pop();
    virtual void draw(const ICanvas&);
    ~PageStack();
};

class StackablePage : public virtual View {
    PageStack& pageStack;

  public:
    StackablePage(PageStack& pageStack) : pageStack(pageStack) {}
    void pop();
    void push(StackablePage* page);
};

#endif
