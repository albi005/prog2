#include "View.hpp"

bool View::handleInput(char input) {
    throw std::runtime_error("handleInput not implemented");
}

ContentView::ContentView(View* content) : content(content) {}

void ContentView::draw(ICanvas& canvas) { content->draw(canvas); }

bool ContentView::handleInput(char input) {
    return content->handleInput(input);
}

ContentView::~ContentView() { delete content; }

Padding::Padding(View* content, int l, int t, int r, int b)
    : ContentView(content), l(l), t(t), r(r), b(b) {}

Padding::Padding(View* content, int x, int y) : Padding(content, x, y, x, y) {}

void Padding::draw(ICanvas& canvas) {
    PaddedCanvas padded(l, t, r, b, canvas);
    ContentView::draw(padded);
}

void PageStack::push(StackablePage* page) { /*TODO*/ }

void PageStack::pop() { /*TODO*/ }

void PageStack::draw(ICanvas& canvas) { /*TODO*/ }

PageStack::~PageStack() { /*TODO*/ }

StackablePage::StackablePage(PageStack& pageStack) : pageStack(pageStack) {}

void StackablePage::pop() { /*TODO*/ }

void StackablePage::push(StackablePage* page) { /*TODO*/ }
