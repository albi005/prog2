#include "VaccinationsPage.hpp"
#include "OwnerPage.hpp"
#include "constants.h"

bool VaccinationsRange::isInteractive() const { return !orderedOwners.empty(); }

VaccinationsRange::VaccinationsRange(
    Data& data, std::function<void(Owner&)> openOwner
)
    : data(data), openOwner(openOwner) {}

VaccinationsPage::VaccinationsPage(Data& data, PageStack& pageStack)
    : ContentView(new PaddingView(
          new ListView(new std::vector<ListRange*>{new VaccinationsRange(
              data,
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
    OwnerRepository& owners = data.owners;
    AnimalRepository& animals = data.animals;
    TreatmentRepository& treatments = data.treatments;

    orderedOwners.clear();

    if (owners.empty())
        return;

    // animal id -> last vaccination
    std::unordered_map<size_t, time_t> lastVaccinations(animals.size());
    for (auto [id, animal] : animals)
        lastVaccinations[id] = 0;
    for (auto [id, treatment] : treatments) {
        if (!treatment->wasVaccinated)
            continue;

        Animal* animal = treatment->animal;
        size_t animalId = animal->id;
        if (treatment->date > lastVaccinations[animalId])
            lastVaccinations[animalId] = treatment->date;
    }

    // owner -> the oldest last vaccination (most unvaccinated first)
    std::unordered_map<Owner*, time_t> oldestVaccinations(owners.size());
    currentTime = time(NULL);
    // if the redraw was triggered by a new treatment, its date might equal the
    // current time
    maxTime = currentTime + 1;
    for (auto [i, owner] : owners)
        oldestVaccinations[owner] = maxTime;
    for (auto [animalId, lastVaccination] : lastVaccinations) {
        Animal& animal = animals.at(animalId);
        Owner* owner = animal.owner;
        time_t oldestVaccination = oldestVaccinations[owner];
        if (lastVaccination < oldestVaccination)
            oldestVaccinations[owner] = lastVaccination;
    }

    // sort owners based on oldest vaccination.
    // first owner should have the lowest value.
    for (auto [owner, oldestVaccination] : oldestVaccinations)
        orderedOwners.push_back({oldestVaccination, owner});
    std::sort(orderedOwners.begin(), orderedOwners.end(), [](auto a, auto b) {
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

    for (size_t i = firstIndex; i <= lastIndex; i++) {
        auto [oldestVaccination, o] = orderedOwners[i];
        int y = i - firstIndex;

        size_t days = utils::daysSince(oldestVaccination, currentTime);

        bool selected = selectedIndex == i;
        if (selected) {
            canvas.fill({0, y, canvas.getSize().w - 4, 1}, ON_SURFACE);
        } else
            canvas.draw(surface, surface);

        canvas.setPosition({2, y});
        if (days > 365)
            canvas.draw(selected ? ON_ERROR : ERROR);
        else if (oldestVaccination == maxTime)
            canvas.draw(selected ? surface : ON_SURFACE_VARIANT);
        else
            canvas.draw(selected ? ON_PRIMARY : PRIMARY);
        if (oldestVaccination == 0)
            canvas.draw() << "soha";
        else if (oldestVaccination == maxTime)
            canvas.draw() << "-";
        else
            canvas.draw() << days << " napja";

        int x = 16;
        canvas.setPosition({x, y});
        canvas.draw(selected ? surface : ON_SURFACE)
            << Clip(o->name, maxNameLength);

        x += maxNameLength + 4;

        canvas.setPosition({x, y});
        canvas.draw() << Clip(o->address, 30);
        x += 34;

        canvas.setPosition({x, y});
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
