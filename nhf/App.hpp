#pragma once

#include "AnimalsPage.hpp"
#include "ListView.hpp"
#include "OwnersPage.hpp"
#include "VaccinationsPage.hpp"
#include "data.hpp"
#include "utils.hpp"
#include <functional>

class Tabs : public virtual View, public StackablePage {
    VaccinationsPage* vaccinationsPage;
    OwnersPage* ownersPage;
    AnimalsPage* animalsPage;

  public:
    Tabs(
        VaccinationsPage* vaccinationsPage,
        OwnersPage* ownersPage,
        AnimalsPage* animalsPage,
        PageStack& pageStack
    );
    void draw(ICanvas& canvas) override;
    virtual ~Tabs();
};

class App : public ContentView {
  public:
    explicit App(View* mainView);
};