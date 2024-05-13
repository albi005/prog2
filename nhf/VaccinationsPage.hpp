#pragma once

#include "ListView.hpp"
#include "data.hpp"
#include <map>

class VaccinationsRange : public ListRange {
    Data& data;
    std::function<void(Owner&)> openOwner;

    // set in onBeforeMeasure
    std::vector<std::pair<time_t, Owner*>> orderedOwners;

    bool isInteractive() const override;
    void onBeforeMeasure() override;
    size_t getHeight() const override;
    void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;
    bool handleInput(char input, size_t selectedIndex) override;

  public:
    VaccinationsRange(Data& data, std::function<void(Owner&)> openOwner);
};

class VaccinationsPage : public ContentView {
    Data& data;
    PageStack& pageStack;

  public:
    VaccinationsPage(Data& data, PageStack& pageStack);
};
