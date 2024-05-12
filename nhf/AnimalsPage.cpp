#include "AnimalsPage.hpp"
#include "AnimalPage.hpp"
#include "ListView.hpp"

// TODO: perhaps refactor AnimalsPage and OwnersPage into a template
void AnimalsRange::onBeforeMeasure() {
    filteredAnimals.clear();

    if (data.animals.empty())
        return;

    for (auto [id, animal] : data.animals) {
        if (searchTerm.empty()) {
            filteredAnimals.push_back({animal, 0});
        } else {
            size_t index = animal->name.find(searchTerm);
            if (index != std::string::npos)
                filteredAnimals.push_back({animal, index});
        }
    }

    std::sort(
        filteredAnimals.begin(),
        filteredAnimals.end(),
        [](auto a, auto b) { return a.second < b.second; }
    );
}

bool AnimalsRange::isInteractive() const { return !filteredAnimals.empty(); }

size_t AnimalsRange::getHeight() const {
    if (filteredAnimals.empty())
        return 1;
    return filteredAnimals.size();
}

void AnimalsRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const {
    if (filteredAnimals.empty()) {
        canvas.draw({2, 0}, ON_SURFACE_VARIANT, canvas.getSurfaceColor())
            << (searchTerm.empty() ? "Még nem lett felvéve állat"
                                   : "Nincs találat");
        return;
    }

    for (size_t i = firstIndex; i <= lastIndex; i++) {
        int y = i - firstIndex;
        auto [animal, startIndex] = filteredAnimals[i];
        auto& name = animal->name;
        bool selected = selectedIndex == i;

        if (selected)
            canvas.fill({0, y, canvas.getSize().w, 1}, ON_SURFACE);

        Color textColor = selected ? SURFACE : ON_SURFACE;
        Color surfaceColor = selected ? ON_SURFACE : canvas.getSurfaceColor();

        canvas.setPosition({2, y});
        if (searchTerm.empty())
            canvas.draw(textColor, surfaceColor) << Clip(name, 8);
        else
            SearchedString(
                name,
                startIndex,
                searchTerm.size(),
                8,
                textColor,
                OUTLINE,
                surfaceColor
            )
                .draw(canvas);

        canvas.draw({12, y}, textColor, surfaceColor)
            << Clip(animal->species, 8);
        canvas.setPosition({24, y}) << Clip(animal->owner->name, 24);
        canvas.setPosition({48, y}) << Clip(animal->owner->address, 35);
    }
}

bool AnimalsRange::handleInput(char input, size_t selectedIndex) {
    /*todo*/
    return false;
}

AnimalsRange::AnimalsRange(
    Data& data, std::string& searchTerm, std::function<void(Animal&)> openAnimal
)
    : data(data), searchTerm(searchTerm), openAnimal(openAnimal) {}

AnimalsPage::AnimalsPage(Data& data, PageStack& pageStack)
    : ContentView(new ListView(new std::vector<ListRange*>{
          new EditablePropertyRange("Keresés", searchTerm),
          new PaddingRange(),
          new AnimalsRange(
              data,
              searchTerm,
              [&pageStack, &data](Animal& animal) {
                  pageStack.push(new AnimalPage(animal, data, pageStack));
              }
          )
      })),
      data(data), pageStack(pageStack) {}
