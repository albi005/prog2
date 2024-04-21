#include "appview.hpp"
#include "canvas.hpp"
#include "data.hpp"
#include "view.hpp"
#include <iostream>

int main() {
    AppData data = AppData();

    PageStack* pageStack = new PageStack();
    pageStack->push(new Tabs(
        new VaxTab(data, *pageStack),
        new OwnersTab(data, *pageStack),
        new AnimalsTab(data, *pageStack),
        *pageStack
    ));
    App app = App(pageStack);

    OstreamCanvas canvas = OstreamCanvas(std::cout);

    while (true) {
        app.draw(canvas);
        canvas.handleEscapeCode(std::cin);
        char input = getchar();
        if (!app.handleInput(input) && input == 27) // TODO: use constant
            break;
    }
}
