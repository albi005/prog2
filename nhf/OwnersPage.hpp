#pragma once

#include "ListView.hpp"
#include "data.hpp"

class OwnersRange : public ListRange {
    Data& data;
    std::string& searchTerm;
    std::function<void(Owner&)> openOwner;

    // set in onBeforeMeasure
    std::vector<std::pair<Owner*, size_t>> filteredOwners;

    void onBeforeMeasure() override;
    bool isInteractive() const override;
    size_t getHeight() const override;
    void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;
    bool handleInput(char input, size_t selectedIndex) override;

  public:
    OwnersRange(
        Data& data,
        std::string& searchTerm,
        std::function<void(Owner&)> openOwner
    );
};

class OwnersPage : public ContentView {
    Data& data;
    PageStack& pageStack;
    std::string searchTerm = "";

  public:
    OwnersPage(Data& data, PageStack& pageStack);
};