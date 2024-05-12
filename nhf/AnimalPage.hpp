#pragma once

#include "ListView.hpp"
#include "View.hpp"
#include "data.hpp"
#include <functional>

class TreatmentsRange : public ListRange {
    Animal& animal;
    std::function<void()> deleteTreatment;
    StringEditor* treatmentNameEditor = nullptr;

    bool isInteractive() const override { return true; }

    void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;
    virtual bool handleInput(char input, size_t selectedIndex) override;

  public:
    TreatmentsRange(Animal& animal, std::function<void()> deleteTreatment);
};

class AnimalPage : public ContentView, public StackablePage {
    Animal& animal;

  public:
    AnimalPage(Animal& animal, Data& data, PageStack& pageStack);
};
