#include "OwnerPage.hpp"
#include "AnimalPage.hpp"
#include "ListView.hpp"

bool OwnerAnimalsRange::isInteractive() const { return true; }

void OwnerAnimalsRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const { /*todo*/ }

bool OwnerAnimalsRange::handleInput(char input, size_t selectedIndex) const {
    /*todo*/
    throw;
}

OwnerAnimalsRange::OwnerAnimalsRange(
    Owner& owner, std::function<void(Animal&)> openAnimal
)
    : owner(owner), openAnimal(openAnimal) {}

OwnerPage::OwnerPage(Owner& owner, Data& data, PageStack& pageStack)
    : ContentView(new ListView(new std::vector<ListRange*>{
          new EditablePropertyRange("Név", owner.name),
          new EditablePropertyRange("Cím", owner.address),
          new EditablePropertyRange("Elérhetőség", owner.contact),
          new PaddingRange(),
          new AddButtonRange([data, &pageStack, &owner]() mutable {
              auto animal = data.animals.createNew(owner);
              pageStack.push(new AnimalPage(*animal, data, pageStack));
          }),
          new OwnerAnimalsRange(
              owner,
              [&pageStack, &data](Animal& animal) {
                  pageStack.push(new AnimalPage(animal, data, pageStack));
              }
          )
      })),
      StackablePage(pageStack), owner(owner) {}
