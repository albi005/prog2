#include "appview.hpp"

bool VaxItemsRange::getIsInteractive() const { return true; }

void VaxItemsRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const { /*todo*/ }

VaxItemsRange::VaxItemsRange(
    AppData& appData, std::function<void(Owner&)> openOwner
)
    : appData(appData), openOwner(openOwner) {}

VaxTab::VaxTab(AppData& appData, PageStack& pageStack)
    : ContentView(new ListView(new std::vector<ListRange*>{new VaxItemsRange(
          appData, [this](Owner& owner) { /* TODO: open owner page */ }
      )})),
      appData(appData), pageStack(pageStack) {}

OwnersTab::OwnersTab(AppData& appData, PageStack& pageStack)
    : ContentView(new ListView(new std::vector<ListRange*>{
          new EditablePropertyRange("Keresés", searchTerm),
          new AddButtonRange([this]() { /* TODO: create and open owner */ })
      })),
      appData(appData), pageStack(pageStack) {}

TreatmentsRange::TreatmentsRange(
    Animal& animal, std::function<void()> deleteTreatment
)
    : animal(animal), deleteTreatment(deleteTreatment) {}

void TreatmentsRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const {
    /* TODO */
}

bool TreatmentsRange::handleInput(char input, size_t selectedIndex) const {
    /* TODO */
    throw;
}

AnimalPage::AnimalPage(Animal& animal)
    : ContentView(new ListView(new std::vector<ListRange*>{
          new EditablePropertyRange("Név", animal.name),
          new EditablePropertyRange("Faj", animal.species),
          new LinkPropertyRange(
              "Tulajdonos",
              animal.owner->name,
              [this]() { /* TODO: open owner */ }
          ),
          new PropertyRange("Cím", animal.owner->address),
      })),
      animal(animal) {}

AnimalsTab::AnimalsTab(AppData& appData, PageStack& pageStack)
    : ContentView(new ListView(
          new std::vector<ListRange*>{/* TODO: add animals tab ranges */}
      )),
      appData(appData), pageStack(pageStack) {}

void AnimalsTab::createEntity() { /* TODO */ }

Tabs::Tabs(
    VaxTab* vaxTab,
    OwnersTab* ownersTab,
    AnimalsTab* animalsTab,
    PageStack& pageStack
)
    : StackablePage(pageStack), vaxTab(vaxTab), ownersTab(ownersTab),
      animalsTab(animalsTab) {}

void Tabs::draw(ICanvas& canvas) { /* TODO */ }

Tabs::~Tabs() { /* TODO */ }

App::App(View* mainView) : ContentView(mainView) {}
