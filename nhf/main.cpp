#include "App.hpp"
#include "OstreamCanvas.hpp"
#include "View.hpp"
#include "data.hpp"
#include "econio.h"
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
        int input = econio_getch();
        bool handled = app.handleInput(input);
        if (!handled && input == KEY_ESCAPE)
            break;
    }
}
