#include "View.hpp"
#include "constants.h"

bool View::handleInput(char input) {
    // todo: add custom exception if needed
    throw std::runtime_error("handleInput not implemented for this view");
}

ContentView::ContentView(View* content) : content(content) {}

void ContentView::draw(ICanvas& canvas) { content->draw(canvas); }

bool ContentView::handleInput(char input) {
    return content->handleInput(input);
}

ContentView::~ContentView() { delete content; }

PaddingView::PaddingView(View* content, int l, int t, int r, int b)
    : ContentView(content), l(l), t(t), r(r), b(b) {}

PaddingView::PaddingView(View* content, int x, int y)
    : PaddingView(content, x, y, x, y) {}

void PaddingView::draw(ICanvas& canvas) {
    PaddedCanvas padded(l, t, r, b, canvas);
    ContentView::draw(padded);
}

void PageStack::push(StackablePage* page) {
    pages.push_back(page);
    page->setLevel(pages.size() - 1);
}

void PageStack::pop(const StackablePage& page) {
    if (pages.back() != &page)
        throw std::logic_error("Can't pop page that is not the top of the stack"
        );
    pages.pop_back();
}

void PageStack::draw(ICanvas& canvas) {
    size_t level = 0;
    for (auto& page : pages) {
        PaddedCanvas paddedCanvas(
            level * 6, level * 2, level * 6, level * 2, canvas
        );
        page->draw(paddedCanvas);
        level++;
    }
}

PageStack::~PageStack() {
    for (auto* page : pages)
        delete page;
}

bool PageStack::handleInput(char input) {
    if (pages.back()->handleInput(input))
        return true;
    if (input == KEY_ESCAPE || input == 'q') {
        pages.pop_back();
        return true;
    }
    return false;
}

StackablePage::StackablePage(PageStack& pageStack) : pageStack(pageStack) {}

void StackablePage::popSelf() { pageStack.pop(*this); }

void StackablePage::push(StackablePage* page) { pageStack.push(page); }

void StackablePage::setLevel(uint8_t value) { this->level = value; }

Color StackablePage::getSurfaceColor() const {
    static const Color colors[] = {
        SURFACE_CONTAINER_LOWEST,
        SURFACE_CONTAINER_LOW,
        SURFACE_CONTAINER,
        SURFACE_CONTAINER_HIGH,
        SURFACE_CONTAINER_HIGHEST
    };

    // Tabs uses SURFACE_CONTAINER_LOWEST as the backdrop
    uint8_t actualLevel = level + 1;
    if (actualLevel > 4)
        return colors[4];
    return colors[actualLevel];
}
