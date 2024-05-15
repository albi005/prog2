#ifndef CPORTA
#include "App.hpp"
#include "OstreamCanvas.hpp"
#include "View.hpp"
#include "constants.hpp"
#include "data.hpp"
#include "econio.hpp"
#include <iostream>

int main() {
    Data data = Data("owners", "animals", "treatments");

    PageStack& pageStack = *new PageStack();
    Tabs* tabs = new Tabs(new std::vector<Tabs::Tab>{
        Tabs::Tab(*new VaccinationsPage(data, pageStack), "Oltások"),
        Tabs::Tab(*new OwnersPage(data, pageStack), "Tulajdonosok"),
        Tabs::Tab(*new AnimalsPage(data, pageStack), "Állatok")
    });
    pageStack.push(tabs);

    App app(pageStack);

    // enable handling key presses as they come in,
    // instead of waiting for newlines
    econio_rawmode();

    OstreamCanvas canvas(std::cout);

    while (true) {
        canvas.updateScreenSize(std::cin);
        app.draw(canvas);
        canvas.draw({999, 999}); // move cursor to bottom right
        std::cout.flush();

        char input = econio_getch();
        bool handled = app.handleInput(input);
        if (!handled && (input == KEY_ESCAPE || input == 'q'))
            break;
    }

    data.save("owners", "animals", "treatments");

    econio_normalmode();
}
#endif
