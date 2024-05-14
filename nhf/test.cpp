#include "App.hpp"
#include "OstreamCanvas.hpp"
#include "View.hpp"
#include "constants.h"
#include "data.hpp"
#include <sstream>
#ifdef CPORTA

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

    std::stringstream is;
    is << CSI "50;50R";
    is << KEY_TAB << "jjjjjjj" << KEY_TAB << "jjjjjjjjj" << KEY_TAB;
    is << KEY_ENTER << "jjjj" << KEY_ENTER << "jjj";
    is << KEY_ENTER << "meg valami" << KEY_ESCAPE;
    is << KEY_ENTER << "inkabb ez" << KEY_ENTER;
    is << "qqq";

    std::stringstream os;
    OstreamCanvas canvas(os);

    while (true) {
        canvas.updateScreenSize(is);
        app.draw(canvas);
        canvas.draw({999, 999});

        char input;
        is >> input;
        bool handled = app.handleInput(input);
        if (!handled && (input == KEY_ESCAPE || input == 'q'))
            break;
    }
}
#endif