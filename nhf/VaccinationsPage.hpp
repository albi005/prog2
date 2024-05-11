#pragma once

#include "ListView.hpp"
#include "data.hpp"

class VaccinationsRange : public ListRange {
    Data& data;
    std::function<void(Owner&)> openOwner;

    bool isInteractive() const override;
    void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;

  public:
    VaccinationsRange(Data& data, std::function<void(Owner&)> openOwner);
};

class VaccinationsPage : public ContentView {
    Data& data;
    PageStack& pageStack;

  public:
    VaccinationsPage(Data& data, PageStack& pageStack);
};
