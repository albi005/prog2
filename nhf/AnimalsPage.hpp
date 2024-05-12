#pragma once

#include "ListView.hpp"
#include "View.hpp"
#include "data.hpp"
#include <functional>

class AnimalsRange : public ListRange {
    Data& data;
    std::string& searchTerm;
    std::function<void(Animal&)> openAnimal;

    bool isInteractive() const override;
    void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;
    bool handleInput(char input, size_t selectedIndex) override;

  public:
    AnimalsRange(
        Data& data,
        std::string& searchTerm,
        std::function<void(Animal&)> openAnimal
    );
};

class AnimalsPage : public ContentView {
    Data& data;
    PageStack& pageStack;
    std::string searchTerm = "";

  public:
    AnimalsPage(Data& data, PageStack& pageStack);
};