#pragma once

#include "ListView.hpp"
#include "View.hpp"
#include "data.hpp"
#include <functional>

class TreatmentsRange : public ListRange {
    Animal& animal;
    std::function<void(Treatment&)> deleteTreatment;
    StringEditor* treatmentNameEditor = nullptr;

    // set in onBeforeMeasure
    std::vector<Treatment*> treatments;

    void onBeforeMeasure() override;
    bool isInteractive() const override;
    size_t getHeight() const override;
    void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;
    virtual bool handleInput(char input, size_t selectedIndex) override;

  public:
    TreatmentsRange(
        Animal& animal, std::function<void(Treatment&)> deleteTreatment
    );
};

class AnimalPage : public ContentView {
    Animal& animal;

  public:
    AnimalPage(Animal& animal, Data& data, PageStack& pageStack);
};
