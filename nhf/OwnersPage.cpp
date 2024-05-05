#include "OwnersPage.hpp"
#include "OwnerPage.hpp"

bool OwnersRange::getIsInteractive() const { return true; }

void OwnersRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const { /*todo*/ }

bool OwnersRange::handleInput(char input, size_t selectedIndex) const {
    /*todo*/
    throw;
}

OwnersRange::OwnersRange(
    Data& data, std::string& searchTerm, std::function<void(Owner&)> openOwner
)
    : data(data), searchTerm(searchTerm), openOwner(openOwner) {}

OwnersPage::OwnersPage(Data& data, PageStack& pageStack)
    : ContentView(new ListView(new std::vector<ListRange*>{
          new EditablePropertyRange("Keresés", searchTerm),
          new PaddingRange(),
          new AddButtonRange([&pageStack, &data]() mutable {
              Owner* owner = data.owners.createNew();
              pageStack.push(new OwnerPage(*owner, data, pageStack));
          }),
          new OwnersRange(
              data,
              searchTerm,
              [&pageStack, &data](Owner& owner) {
                  pageStack.push(new OwnerPage(owner, data, pageStack));
              }
          ),
      })),
      data(data), pageStack(pageStack) {}
