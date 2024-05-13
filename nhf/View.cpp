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

void PageStack::push(View* page) { pages.push_back(page); }

size_t PageStack::size() const { return pages.size(); }

void PageStack::draw(ICanvas& canvas) {
    size_t level = 0;
    for (auto page : pages) {
        PaddedCanvas paddedCanvas(
            level * 6, level * 2, level * 6, level * 2, canvas
        );
        canvas.setSurfaceColor(getSurfaceColor(level));
        Size size = paddedCanvas.getSize();
        paddedCanvas.fill(
            {0, 0, size.w, size.h}, paddedCanvas.getSurfaceColor()
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
        delete pages.back();
        pages.pop_back();
        if (pages.empty())
            return false;
        return true;
    }
    return false;
}

Color PageStack::getSurfaceColor(size_t level) const {
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
