#include "AnimalPage.hpp"

TreatmentsRange::TreatmentsRange(
    Animal& animal, std::function<void()> deleteTreatment
)
    : animal(animal), deleteTreatment(deleteTreatment) {}

void TreatmentsRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const {
    /* TODO */
}

bool TreatmentsRange::handleInput(char input, size_t selectedIndex) {
    /* TODO */
    throw;
}

AnimalPage::AnimalPage(Animal& animal, Data& data, PageStack& pageStack)
    : ContentView(new ListView(new std::vector<ListRange*>{
          new EditablePropertyRange("Név", animal.name),
          new EditablePropertyRange("Faj", animal.species),
          new LinkPropertyRange(
              "Tulajdonos",
              animal.owner->name,
              [this]() { /* TODO: open owner */ }
          ),
          new PropertyRange("Cím", animal.owner->address),
          new PaddingRange(),
          new AddButtonRange([this]() { /*TODO: create treatment*/ }),
          new TreatmentsRange(animal, [this]() { /*TODO: delete treatment*/ })
      })),
      StackablePage(pageStack), animal(animal) {}