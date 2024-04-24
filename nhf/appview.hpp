#ifndef APPVIEW_HPP
#define APPVIEW_HPP

#include "data.hpp"
#include "listview.hpp"
#include "utils.hpp"
#include <functional>

class VaxItemsRange : public ListRange {
    AppData& appData;
    std::function<void(Owner&)> openOwner;

    bool getIsInteractive() const { return true; }
    void draw(
        const ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const;

  public:
    VaxItemsRange(AppData& appData, std::function<void(Owner&)> openOwner)
        : appData(appData), openOwner(openOwner) {}
};

class VaxTab : public ContentView {
    AppData& appData;
    PageStack& pageStack;

  public:
    VaxTab(AppData& appData, PageStack& pageStack)
        : ContentView(new ListView(new std::vector<ListRange*>{
              new VaxItemsRange(
                  appData, [this](Owner& owner) { /* TODO: open owner page */ }
              )})),
          appData(appData), pageStack(pageStack) {}
};

class OwnersTab : public ContentView {
    AppData& appData;
    PageStack& pageStack;
    std::string searchTerm = "";

  public:
    OwnersTab(AppData& appData, PageStack& pageStack)
        : ContentView(new ListView(new std::vector<ListRange*>{
              new EditablePropertyRange("Keresés", searchTerm),
              new AddButtonRange([this]() { /* TODO: create and open owner */ })})),
          appData(appData), pageStack(pageStack) {}
};

class TreatmentsRange : public ListRange {
    Animal& animal;
    std::function<void()> deleteTreatment;
    StringEditor* treatmentNameEditor = nullptr;

    bool getIsInteractive() const { return true; }
    void draw(
        const ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const;
    virtual void handleInput(char input, size_t selectedIndex) const;

  public:
    TreatmentsRange(
        Animal& animal, std::function<void()> deleteTreatment
    )
        : animal(animal), deleteTreatment(deleteTreatment) {}
};

class AnimalPage : public ContentView {
    Animal& animal;

  public:
    AnimalPage(Animal& animal)
        : ContentView(new ListView(new std::vector<ListRange*>{
              new EditablePropertyRange("Név", animal.name),
              new EditablePropertyRange("Faj", animal.species),
              new LinkPropertyRange("Tulajdonos", animal.owner->name, [this](){ /* TODO: open owner */ }),
              new PropertyRange("Cím", animal.owner->address),
          })),
          animal(animal) {}
};

class AnimalsTab : public ContentView {
    AppData& appData;
    PageStack& pageStack;

  public:
    AnimalsTab(AppData& appData, PageStack& pageStack)
        : ContentView(new ListView(new std::vector<ListRange*>{/* TODO: add animals tab ranges */})),
          appData(appData), pageStack(pageStack) {}
    void createEntity();
};

class Tabs : public virtual View, public StackablePage {
    VaxTab* vaxTab;
    OwnersTab* ownersTab;
    AnimalsTab* animalsTab;

  public:
    Tabs(
        VaxTab* vaxTab,
        OwnersTab* ownersTab,
        AnimalsTab* animalsTab,
        PageStack& pageStack
    )
        : vaxTab(vaxTab), ownersTab(ownersTab), animalsTab(animalsTab),
          StackablePage(pageStack) {}
    void draw(const ICanvas&);
    bool handleInput(char input);
    virtual ~Tabs();
};

class App : public ContentView {
  public:
    App(View* mainView) : ContentView(mainView) {}
};
#endif
