#ifndef APPVIEW_HPP
#define APPVIEW_HPP

#include "data.hpp"
#include "listview.hpp"
#include "utils.hpp"
#include <functional>

class VaxItemsRange : public ListRange {
    AppData& appData;
    std::function<void(Owner&)> openOwner;

    bool getIsInteractive() const override;
    void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;

  public:
    VaxItemsRange(AppData& appData, std::function<void(Owner&)> openOwner);
};

class VaxTab : public ContentView {
    AppData& appData;
    PageStack& pageStack;

  public:
    VaxTab(AppData& appData, PageStack& pageStack);
};

class OwnersTab : public ContentView {
    AppData& appData;
    PageStack& pageStack;
    std::string searchTerm = "";

  public:
    OwnersTab(AppData& appData, PageStack& pageStack);
};

class TreatmentsRange : public ListRange {
    Animal& animal;
    std::function<void()> deleteTreatment;
    StringEditor* treatmentNameEditor = nullptr;

    bool getIsInteractive() const { return true; }

    void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const;
    virtual bool handleInput(char input, size_t selectedIndex) const;

  public:
    TreatmentsRange(Animal& animal, std::function<void()> deleteTreatment);
};

class AnimalPage : public ContentView {
    Animal& animal;

  public:
    AnimalPage(Animal& animal);
};

class AnimalsTab : public ContentView {
    AppData& appData;
    PageStack& pageStack;

  public:
    AnimalsTab(AppData& appData, PageStack& pageStack);
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
    );
    void draw(ICanvas& canvas) override;
    virtual ~Tabs();
};

class App : public ContentView {
  public:
    explicit App(View* mainView);
};

#endif
