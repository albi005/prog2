#include "data.hpp"

OwnerRepository::OwnerRepository(AnimalRepository& animals)
    : animals(animals) {}

Owner* OwnerRepository::createNew() {
    auto owner = new Owner();
    owner->id = getNextId();
    entities[owner->id] = owner;
    return owner;
}

AnimalRepository::AnimalRepository(TreatmentRepository& treatments)
    : treatments(treatments) {}

void AnimalRepository::load(std::istream& is, const OwnerRepository& owners) {
    Repository<Animal>::load(is);
    for (auto [id, animal] : entities) {
        std::ignore = id;
        auto& owner = owners.at(animal->ownerId);
        animal->owner = &owner;
        owner.animals.push_back(animal);
    }
}

Animal* AnimalRepository::createNew(Owner& owner) {
    auto animal = new Animal();
    animal->id = getNextId();
    animal->ownerId = owner.id;
    animal->owner = &owner;
    entities[animal->id] = animal;
    owner.animals.push_back(animal);
    return animal;
}

void TreatmentRepository::load(
    std::istream& is, const AnimalRepository& animals
) {
    Repository<Treatment>::load(is);
    for (auto [id, treatment] : entities) {
        std::ignore = id;
        auto& animal = animals.at(treatment->animalId);
        treatment->animal = &animal;
        animal.treatments.push_back(treatment);
    }
}

Treatment* TreatmentRepository::createNew(Animal& animal) {
    auto treatment = new Treatment();
    treatment->id = getNextId();
    treatment->animalId = animal.id;
    treatment->animal = &animal;
    entities[treatment->id] = treatment;
    animal.treatments.push_back(treatment);
    return treatment;
}

void Data::load(
    std::istream& ownersStream,
    std::istream& animalsStream,
    std::istream& treatmentsStream
) {
    owners.load(ownersStream);
    animals.load(animalsStream, owners);
    treatments.load(treatmentsStream, animals);
}

Data::Data() : treatments(), animals(treatments), owners(animals) {}

Data::Data(
    std::istream& ownersStream,
    std::istream& animalsStream,
    std::istream& treatmentsStream
)
    : Data() {
    load(ownersStream, animalsStream, treatmentsStream);
}

Data::Data(
    const char* ownersFile, const char* animalsFile, const char* treatmentsFile
)
    : Data() {
    std::ifstream ownersStream(ownersFile);
    std::ifstream animalsStream(animalsFile);
    std::ifstream treatmentsStream(treatmentsFile);
    load(ownersStream, animalsStream, treatmentsStream);
}

void Data::save(
    std::ostream& ownersStream,
    std::ostream& animalsStream,
    std::ostream& treatmentsStream
) {
    treatments.save(treatmentsStream);
    animals.save(animalsStream);
    owners.save(ownersStream);
}

// TODO: test saving to a new file
void Data::save(
    const char* ownersFile, const char* animalsFile, const char* treatmentsFile
) {
    std::ofstream ownersStream(ownersFile);
    std::ofstream animalsStream(animalsFile);
    std::ofstream treatmentsStream(treatmentsFile);
    save(ownersStream, animalsStream, treatmentsStream);
}
