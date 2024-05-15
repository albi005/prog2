#pragma once

#include "ListView.hpp"
#include "View.hpp"
#include "data.hpp"
#include <functional>

class OwnerAnimalsRange : public ListRange {
    Owner& owner;
    std::function<void(Animal&)> openAnimal;
    std::function<void(Animal&)> removeAnimal;

    std::vector<Animal*> animals;

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
    OwnerAnimalsRange(
        Owner& owner,
        std::function<void(Animal&)> openAnimal,
        std::function<void(Animal&)> removeAnimal
    );
};

class OwnerPage final : public ContentView {
    Owner& owner;
    PageStack& pageStack;
    Data& data;

    bool handleInput(char input) override;

  public:
    OwnerPage(Owner& owner, Data& data, PageStack& pageStack);
};