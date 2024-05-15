#include "OwnerPage.hpp"
#include "AnimalPage.hpp"
#include "ListView.hpp"
#include "constants.hpp"

void OwnerAnimalsRange::onBeforeMeasure() {
    animals.clear();
    animals.reserve(owner.animals.size());
    for (const auto& animalPair : owner.animals)
        animals.push_back(animalPair.second);
    std::sort(animals.begin(), animals.end(), [](auto& a, auto& b) {
        return a->name < b->name;
    });
}

bool OwnerAnimalsRange::isInteractive() const { return !owner.animals.empty(); }

size_t OwnerAnimalsRange::getHeight() const {
    if (owner.animals.empty())
        return 1;
    return owner.animals.size();
}

void OwnerAnimalsRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const {
    if (owner.animals.empty()) {
        canvas.draw({2, 0}, ON_SURFACE_VARIANT, canvas.getSurfaceColor())
            << "Még nem lett állat felvéve";
        return;
    }

    for (size_t i = firstIndex; i <= lastIndex; i++) {
        Animal& animal = *animals[i];
        int y = i - firstIndex;
        bool selected = i == selectedIndex;
        Color textColor = selected ? SURFACE : ON_SURFACE;
        Color textVariant = selected ? SURFACE : ON_SURFACE_VARIANT;
        Color surfaceColor = selected ? ON_SURFACE : canvas.getSurfaceColor();
        if (selected)
            canvas.fill({0, y, canvas.getSize().w, 1}, surfaceColor);
        canvas.draw({2, y}, textColor, surfaceColor) << Clip(animal.name, 11);
        canvas.draw({16, y}, textVariant, surfaceColor) << animal.species;
    }
}

bool OwnerAnimalsRange::handleInput(char input, size_t selectedIndex) {
    if (input == KEY_ENTER) {
        openAnimal(*animals[selectedIndex]);
        return true;
    } else if (input == 'D') {
        removeAnimal(*animals[selectedIndex]);
        return true;
    }
    return false;
}

OwnerAnimalsRange::OwnerAnimalsRange(
    Owner& owner,
    std::function<void(Animal&)> openAnimal,
    std::function<void(Animal&)> removeAnimal
)
    : owner(owner), openAnimal(openAnimal), removeAnimal(removeAnimal) {}

OwnerPage::OwnerPage(Owner& owner, Data& data, PageStack& pageStack)
    : ContentView(new PaddingView(
          new ListView(new std::vector<ListRange*>{
              new EditablePropertyRange("Név", owner.name),
              new EditablePropertyRange("Cím", owner.address),
              new EditablePropertyRange("Elérhetőség", owner.contact),
              new PaddingRange(),
              new AddButtonRange([&data, &pageStack, &owner]() mutable {
                  auto animal = data.animals.createNew(owner);
                  pageStack.push(new AnimalPage(*animal, data, pageStack));
              }),
              new OwnerAnimalsRange(
                  owner,
                  [&pageStack, &data](Animal& animal) {
                      pageStack.push(new AnimalPage(animal, data, pageStack));
                  },
                  [&data](Animal& animal) { data.animals.remove(animal); }
              )
          }),
          3,
          1
      )),
      owner(owner), pageStack(pageStack), data(data) {}

bool OwnerPage::handleInput(char input) {
    if (!ContentView::handleInput(input)) {
        if (input == 'D') {
            data.owners.remove(owner);
            pageStack.pop();
            return true;
        }
    }
    return false;
}
