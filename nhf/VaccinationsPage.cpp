#include "VaccinationsPage.hpp"
#include "OwnerPage.hpp"
#include "constants.h"
#include <limits>

bool VaccinationsRange::isInteractive() const { return !orderedOwners.empty(); }

VaccinationsRange::VaccinationsRange(
    OwnerRepository& owners, std::function<void(Owner&)> openOwner
)
    : owners(owners), openOwner(openOwner) {}

VaccinationsPage::VaccinationsPage(Data& data, PageStack& pageStack)
    : ContentView(new PaddingView(
          new ListView(new std::vector<ListRange*>{new VaccinationsRange(
              data.owners,
              [&pageStack, &data](Owner& owner) {
                  pageStack.push(new OwnerPage(owner, data, pageStack));
              }
          )}),
          0,
          1,
          0,
          0
      )),
      data(data), pageStack(pageStack) {}

void VaccinationsRange::onBeforeMeasure() {
    orderedOwners.clear();

    if (owners.empty())
        return;

    for (const auto& ownerPair : owners) {
        auto owner = ownerPair.second;
        time_t oldestVaccination = std::numeric_limits<time_t>::max();
        for (auto animal : owner->animals) {
            time_t lastVaccination = 0;
            for (auto treatment : animal->treatments) {
                if (treatment->wasVaccinated &&
                    treatment->date > lastVaccination)
                    lastVaccination = treatment->date;
            }

            if (lastVaccination < oldestVaccination)
                oldestVaccination = lastVaccination;
        }

        orderedOwners.push_back({oldestVaccination, owner});
    }

    // sort owners based on oldest vaccination.
    // first owner should have the animal that needs to be vaccinated the most
    std::sort(orderedOwners.begin(), orderedOwners.end(), [](auto& a, auto& b) {
        return a.first < b.first;
    });
}

size_t VaccinationsRange::getHeight() const {
    if (orderedOwners.empty())
        return 1;
    return orderedOwners.size();
}

void VaccinationsRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const {
    const Color surface = canvas.getSurfaceColor();

    if (orderedOwners.empty()) {
        canvas.draw({2, 0}, ON_SURFACE_VARIANT, surface)
            << "Még nincs tulajdonos felvéve";
        return;
    }

    size_t maxNameLength = 20; // TODO: make dynamic
    time_t currentTime = time(nullptr);

    for (size_t i = firstIndex; i <= lastIndex; i++) {
        auto [oldestVaccination, o] = orderedOwners[i];
        int y = i - firstIndex;

        size_t days = utils::daysSince(oldestVaccination, currentTime);

        bool selected = selectedIndex == i;
        if (selected) {
            canvas.fill({0, y, canvas.getSize().w - 4, 1}, ON_SURFACE);
        } else
            canvas.draw(surface, surface);

        canvas.draw({2, y});
        if (o->animals.empty())
            canvas.draw(selected ? surface : ON_SURFACE_VARIANT) << '-';
        else if (oldestVaccination == 0) // no vaccinations found
            canvas.draw(selected ? ON_ERROR : ERROR) << "nem volt";
        else {
            if (days > 365)
                canvas.draw(selected ? ON_ERROR : ERROR);
            else
                canvas.draw(selected ? ON_PRIMARY : PRIMARY);
            canvas.draw() << days << " napja";
        }

        int x = 16;
        canvas.draw({x, y});
        canvas.draw(selected ? surface : ON_SURFACE)
            << Clip(o->name, maxNameLength);

        x += maxNameLength + 4;

        canvas.draw({x, y});
        canvas.draw() << Clip(o->address, 30);
        x += 34;

        canvas.draw({x, y});
        canvas.draw() << Clip(o->contact, 15);
    }
}

bool VaccinationsRange::handleInput(char input, size_t selectedIndex) {
    if (input == KEY_ENTER) {
        openOwner(*orderedOwners[selectedIndex].second);
        return true;
    }
    return false;
}
