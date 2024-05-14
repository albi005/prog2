#include "AnimalPage.hpp"
#include "OwnerPage.hpp"
#include "constants.h"

void TreatmentsRange::onBeforeMeasure() {
    treatments.clear();
    treatments.reserve(animal.treatments.size());
    for (const auto& treatmentPair : animal.treatments)
        treatments.push_back(treatmentPair.second);
    std::sort(
        treatments.begin(),
        treatments.end(),
        [](Treatment* a, Treatment* b) { return a->date > b->date; }
    );
}

TreatmentsRange::TreatmentsRange(
    Animal& animal, std::function<void(Treatment&)> deleteTreatment
)
    : animal(animal), deleteTreatment(deleteTreatment) {}

bool TreatmentsRange::isInteractive() const {
    return !animal.treatments.empty();
}

size_t TreatmentsRange::getHeight() const {
    if (animal.treatments.empty())
        return 1;
    return animal.treatments.size();
}

void TreatmentsRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const {
    if (animal.treatments.empty()) {
        canvas.draw({2, 0}, ON_SURFACE_VARIANT, canvas.getSurfaceColor())
            << "Még nem lett kezelés felvéve";
        return;
    }

    bool isEditing = treatmentNameEditor != nullptr;
    time_t now = time(nullptr);

    for (size_t i = firstIndex; i <= lastIndex; i++) {
        Treatment& treatment = *treatments[i];
        int y = i - firstIndex;
        bool isSelected = i == selectedIndex;
        bool highlight = isSelected && !isEditing;
        Color textColor = highlight ? SURFACE : ON_SURFACE;
        Color textVariant = highlight ? SURFACE : ON_SURFACE_VARIANT;
        Color surfaceColor = highlight ? ON_SURFACE : canvas.getSurfaceColor();
        int days = utils::daysSince(treatment.date, now);

        if (highlight)
            canvas.fill({0, y, canvas.getSize().w, 1}, surfaceColor);

        if (treatment.wasVaccinated)
            canvas.draw({0, y}, textColor, surfaceColor) << "💉";
        canvas.draw({2, y}, textVariant, surfaceColor) << days << " napja";

        canvas.draw({15, y}, textColor, surfaceColor);
        canvas.draw() << treatment.description;
        if (isEditing && isSelected)
            canvas.draw(ON_SURFACE, ON_SURFACE) << ' ';
    }
}

bool TreatmentsRange::handleInput(char input, size_t selectedIndex) {
    bool editing = treatmentNameEditor != nullptr;
    if (editing) {
        bool finished = treatmentNameEditor->handleInput(input);
        if (finished) {
            delete treatmentNameEditor;
            treatmentNameEditor = nullptr;
        }
        return true;
    }

    if (input == KEY_ENTER) {
        treatmentNameEditor =
            new StringEditor(treatments[selectedIndex]->description);
        return true;
    } else if (input == 'D') {
        deleteTreatment(*treatments[selectedIndex]);
        return true;
    } else if (input == ' ') {
        treatments[selectedIndex]->wasVaccinated =
            !treatments[selectedIndex]->wasVaccinated;
        return true;
    }

    return false;
}

AnimalPage::AnimalPage(Animal& animal, Data& data, PageStack& pageStack)
    : ContentView(new PaddingView(
          new ListView(new std::vector<ListRange*>{
              new EditablePropertyRange("Név", animal.name),
              new EditablePropertyRange("Faj", animal.species),
              pageStack.size() < 2
                  ? new LinkPropertyRange(
                        "Tulajdonos",
                        animal.owner->name,
                        [&pageStack, &animal, &data]() {
                            pageStack.push(
                                new OwnerPage(*animal.owner, data, pageStack)
                            );
                        }
                    )
                  : new PropertyRange("Tulajdonos", animal.owner->name),
              new PropertyRange("Cím", animal.owner->address),
              new PaddingRange(),
              new AddButtonRange([&data, &animal]() {
                  data.treatments.createNew(animal);
              }),
              new TreatmentsRange(
                  animal,
                  [&data](Treatment& treatment) {
                      data.treatments.remove(treatment);
                  }
              )
          }),
          3,
          1
      )),
      animal(animal) {}