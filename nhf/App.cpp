#include "App.hpp"
#include "AnimalPage.hpp"
#include "constants.h"

Tabs::Tab::Tab(View& view, const char* title) : view(view), title(title) {}

View& Tabs::Tab::getView() { return view; }

const char* Tabs::Tab::getTitle() { return title; }

Tabs::Tabs(std::vector<Tab>* tabs, PageStack& pageStack)
    : StackablePage(pageStack), tabs(*tabs) {}

void Tabs::draw(ICanvas& canvas) {
    const Color backdrop = SURFACE_CONTAINER_LOWEST;
    const Color surface = SURFACE_CONTAINER;

    canvas.fill({0, 0, canvas.getSize().w, 1}, backdrop);

    canvas.setPosition({0, 0});
    for (size_t i = 0; i < tabs.size(); ++i) {
        bool isSelected = selectedIndex == i;
        canvas.draw(
            isSelected ? ON_SURFACE : ON_SURFACE_VARIANT,
            isSelected ? surface : backdrop
        ) << " "
          << tabs[i].getTitle() << " ";
    }

    Tab& selectedTab = tabs[selectedIndex];
    PaddedCanvas paddedCanvas(0, 1, 0, 0, canvas);
    selectedTab.getView().draw(paddedCanvas);
}

bool Tabs::handleInput(char input) {
    Tab& selectedTab = tabs[selectedIndex];
    if (selectedTab.getView().handleInput(input))
        return true;
    if (input == KEY_TAB) {
        selectedIndex++;
        selectedIndex %= tabs.size();
        return true;
    }
    return false;
}

Tabs::~Tabs() {
    for (auto& tab : tabs)
        delete &tab.getView();
}

App::App(PageStack& pageStack) : ContentView(&pageStack) {}
