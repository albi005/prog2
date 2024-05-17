#pragma once

#include "AnimalsPage.hpp"
#include "ListView.hpp"
#include "OwnersPage.hpp"
#include "VaccinationsPage.hpp"
#include "data.hpp"
#include "utils.hpp"
#include <functional>

/// @brief A View that draws a tab bar at the top of the screen and the
/// currently selected tab. Use the tab key ↹ to switch between tabs.
class Tabs final : public View {
  public:
    class Tab {
        View& view;
        const char* title;

      public:
        explicit Tab(View& view, const char* title);
        View& getView();
        const char* getTitle();
    };

  private:
    size_t selectedIndex = 0;
    // owned
    std::vector<Tab>& tabs;

  public:
    Tabs(std::vector<Tab>* tabs);
    void draw(ICanvas& canvas) override;
    bool handleInput(char input) override;
    ~Tabs();
};

class App final : public ContentView {
    App(PageStack* pageStack);

  public:
    /// @brief Allocates an App instance and initializes it with the initial
    /// View hierarchy
    static App* create(Data& data);
};