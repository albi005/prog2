#include "AnimalsPage.hpp"
#include "AnimalPage.hpp"
#include "ListView.hpp"

bool AnimalsRange::isInteractive() const { return true; }

void AnimalsRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const { /*todo*/ }

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
