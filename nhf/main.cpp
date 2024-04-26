#include "appview.hpp"
#include "data.hpp"
#include "ostream_canvas.hpp"
#include "view.hpp"
#include <iostream>

int main() {
    AppData data = AppData("owners", "animals", "treatments");

    auto* pageStack = new PageStack();
    pageStack->push(new Tabs(
        new VaxTab(data, *pageStack),
        new OwnersTab(data, *pageStack),
        new AnimalsTab(data, *pageStack),
        *pageStack
    ));

    App app(pageStack);

    OstreamCanvas canvas(std::cout);

    while (true) {
        app.draw(canvas);
        canvas.updateScreenSize(std::cin);
        char input = getchar();
        if (!app.handleInput(input) && input == 27) // TODO: use constant
            break;
    }
}
