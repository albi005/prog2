#include "App.hpp"
#include "OstreamCanvas.hpp"
#include "View.hpp"
#include "data.hpp"
#include <iostream>

int main() {
    Data data = Data("owners", "animals", "treatments");

    auto* pageStack = new PageStack();
    pageStack->push(new Tabs(
        new VaccinationsPage(data, *pageStack),
        new OwnersPage(data, *pageStack),
        new AnimalsPage(data, *pageStack),
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
