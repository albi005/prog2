#include "App.hpp"
#include "OstreamCanvas.hpp"
#include "View.hpp"
#include "data.hpp"
#include "econio.h"
#include <iostream>

int main() {
    Data data = Data("owners", "animals", "treatments");

    PageStack& pageStack = *new PageStack();
    Tabs* tabs = new Tabs(
        new std::vector<Tabs::Tab>{
            Tabs::Tab(*new VaccinationsPage(data, pageStack), "Oltások"),
            Tabs::Tab(*new OwnersPage(data, pageStack), "Tulajdonosok"),
            Tabs::Tab(*new AnimalsPage(data, pageStack), "Állatok")
        },
        pageStack
    );
    pageStack.push(tabs);

    App app(pageStack);

    // enable handling key presses as they come in
    // instead of waiting for newlines
    econio_rawmode();

    OstreamCanvas canvas(std::cout);

    while (true) {
        canvas.updateScreenSize(std::cin);
        econio_flush();
        for (int i = 0; i < canvas.getSize().h; i++)
            canvas.draw({0, i}, 0, SURFACE) << "\x1b[J"; // clear line
        econio_flush();
        app.draw(canvas);
        econio_flush();

        int input = econio_getch();
        bool handled = app.handleInput(input);
        if (!handled && (input == KEY_ESCAPE || input == 'q'))
            break;
    }

    econio_normalmode();
}
