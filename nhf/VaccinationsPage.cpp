#include "VaccinationsPage.hpp"
#include "OwnerPage.hpp"

bool VaccinationsRange::getIsInteractive() const { return true; }

void VaccinationsRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const { /*todo*/ }

VaccinationsRange::VaccinationsRange(
    Data& data, std::function<void(Owner&)> openOwner
)
    : data(data), openOwner(openOwner) {}

VaccinationsPage::VaccinationsPage(Data& data, PageStack& pageStack)
    : ContentView(
          new ListView(new std::vector<ListRange*>{new VaccinationsRange(
              data,
              [&pageStack, &data](Owner& owner) {
                  pageStack.push(new OwnerPage(owner, data, pageStack));
              }
          )})
      ),
      data(data), pageStack(pageStack) {}
