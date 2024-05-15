#include "OwnersPage.hpp"
#include "OwnerPage.hpp"
#include "constants.hpp"

void OwnersRange::onBeforeMeasure() {
    filteredOwners.clear();

    if (data.owners.empty())
        return;

    for (auto [id, owner] : data.owners) {
        std::ignore = id;
        if (searchTerm.empty()) {
            filteredOwners.push_back({owner, 0});
        } else {
            size_t index = owner->name.find(searchTerm);
            if (index != std::string::npos)
                filteredOwners.push_back({owner, index});
        }
    }

    std::sort(filteredOwners.begin(), filteredOwners.end(), [](auto a, auto b) {
        return a.first->name < b.first->name;
    });
}

bool OwnersRange::isInteractive() const { return !filteredOwners.empty(); }

size_t OwnersRange::getHeight() const {
    if (filteredOwners.empty())
        return 1;
    return filteredOwners.size();
}

void OwnersRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const {
    if (filteredOwners.empty()) {
        canvas.draw({2, 0}, ON_SURFACE_VARIANT, canvas.getSurfaceColor())
            << (searchTerm.empty() ? "Még nem lett felvéve tulajdonos"
                                   : "Nincs találat");
        return;
    }

    for (size_t i = firstIndex; i <= lastIndex; i++) {
        int y = i - firstIndex;
        auto [owner, startIndex] = filteredOwners[i];
        auto& name = owner->name;
        bool selected = selectedIndex == i;

        if (selected)
            canvas.fill({0, y, canvas.getSize().w, 1}, ON_SURFACE);

        Color textColor = selected ? SURFACE : ON_SURFACE;
        Color surfaceColor = selected ? ON_SURFACE : canvas.getSurfaceColor();

        canvas.draw({2, y});
        if (searchTerm.empty())
            canvas.draw(textColor, surfaceColor) << Clip(name, 20);
        else
            SearchedString(
                name,
                startIndex,
                searchTerm.size(),
                20,
                textColor,
                OUTLINE,
                surfaceColor
            )
                .draw(canvas);

        canvas.draw({26, y}, textColor, surfaceColor)
            << Clip(owner->address, 34);
        canvas.draw({64, y}) << Clip(owner->contact, 25);
    }
}

bool OwnersRange::handleInput(char input, size_t selectedIndex) {
    switch (input) {
        case KEY_ENTER:
            openOwner(*filteredOwners[selectedIndex].first);
            return true;
        case 'D':
            data.owners.remove(*filteredOwners[selectedIndex].first);
            return true;
    }
    return false;
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
