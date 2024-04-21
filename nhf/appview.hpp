#ifndef APPVIEW_HPP
#define APPVIEW_HPP

#include "callback.hpp"
#include "data.hpp"
#include "listview.hpp"
#include "utils.hpp"

class VaxItemsRange : public ListRange {
    AppData& appData;
    ShowDetailsCallback<Owner>& openOwner;

    bool getIsInteractive() const { return true; }
    void draw(
        const ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const;

  public:
    VaxItemsRange(AppData& appData, ShowDetailsCallback<Owner>& openOwner)
        : appData(appData), openOwner(openOwner) {}
};

class VaxTab : public ContentView, public ShowDetailsCallback<Owner> {
    AppData& appData;
    PageStack& pageStack;

  public:
    VaxTab(AppData& appData, PageStack& pageStack)
        : ContentView(new ListView(
              new std::vector<ListRange*>{new VaxItemsRange(appData, *this)}
          )),
          appData(appData), pageStack(pageStack) {}
    void showDetails(Owner& owner);
    void deleteEntity(Owner& owner);
};

class OwnersTab : public ContentView, public CreateEntityCallback {
    AppData& appData;
    PageStack& pageStack;
    std::string searchTerm = "";

  public:
    OwnersTab(AppData& appData, PageStack& pageStack)
        : ContentView(new ListView(new std::vector<ListRange*>{
              new EditablePropertyRange("Keresés", searchTerm),
              new AddButtonRange(*this)
          })),
          appData(appData), pageStack(pageStack) {}
    void createEntity();
};

class TreatmentsRange : public ListRange {
    Animal& animal;
    DeleteEntityCallback<Treatment>& deleteTreatment;
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
        Animal& animal, DeleteEntityCallback<Treatment>& deleteTreatment
    )
        : animal(animal), deleteTreatment(deleteTreatment) {}
};

class AnimalPage : public ContentView, public OpenLinkCallback {
    Animal& animal;

  public:
    AnimalPage(Animal& animal)
        : ContentView(new ListView(new std::vector<ListRange*>{
              new EditablePropertyRange("Név", animal.name),
              new EditablePropertyRange("Faj", animal.species),
              new LinkPropertyRange("Tulajdonos", animal.owner->name, *this),
              new PropertyRange("Cím", animal.owner->address),
          })),
          animal(animal) {}
    void openLink(); // open owner
};

class AnimalsTab : public ContentView, public CreateEntityCallback {
    AppData& appData;
    PageStack& pageStack;

  public:
    AnimalsTab(AppData& appData, PageStack& pageStack)
        : ContentView(new ListView(new std::vector<ListRange*>{/* TODO */})),
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
