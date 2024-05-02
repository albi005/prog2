#include "App.hpp"
#include "AnimalPage.hpp"

Tabs::Tabs(
    VaccinationsPage* vaccinationsPage,
    OwnersPage* ownersPage,
    AnimalsPage* animalsPage,
    PageStack& pageStack
)
    : StackablePage(pageStack), vaccinationsPage(vaccinationsPage),
      ownersPage(ownersPage), animalsPage(animalsPage) {}

void Tabs::draw(ICanvas& canvas) { /* TODO */ }

Tabs::~Tabs() { /* TODO */ }

App::App(View* mainView) : ContentView(mainView) {}
