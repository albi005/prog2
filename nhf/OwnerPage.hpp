#pragma once

#include "ListView.hpp"
#include "View.hpp"
#include "data.hpp"
#include <functional>

class OwnerAnimalsRange : public ListRange {
    Owner& owner;
    std::function<void(Animal&)> openAnimal;

    bool isInteractive() const override;
    void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;
    virtual bool handleInput(char input, size_t selectedIndex) override;

  public:
    OwnerAnimalsRange(Owner& owner, std::function<void(Animal&)> openAnimal);
};

class OwnerPage : public ContentView, public StackablePage {
    Owner& owner;

  public:
    OwnerPage(Owner& owner, Data& data, PageStack& pageStack);
};