#include "data.hpp"
#include <algorithm>

OwnerRepository::OwnerRepository(AnimalRepository& animals)
    : animals(animals) {}

Owner* OwnerRepository::createNew() {
    auto owner = new Owner();
    owner->id = getNextId();
    entities[owner->id] = owner;
    return owner;
}

void OwnerRepository::remove(Owner& owner) {
    for (auto pair : owner.animals)
        animals.remove(*pair.second);
    Repository::remove(owner);
}

AnimalRepository::AnimalRepository(TreatmentRepository& treatments)
    : treatments(treatments) {}

void AnimalRepository::load(std::istream& is, const OwnerRepository& owners) {
    Repository<Animal>::load(is);
    for (auto [id, animal] : entities) {
        auto& owner = owners.at(animal->ownerId);
        animal->owner = &owner;
        owner.animals.emplace(id, animal);
    }
}

Animal* AnimalRepository::createNew(Owner& owner) {
    auto animal = new Animal();
    animal->id = getNextId();
    animal->ownerId = owner.id;
    animal->owner = &owner;
    entities[animal->id] = animal;
    owner.animals.emplace(animal->id, animal);
    return animal;
}

void AnimalRepository::remove(Animal& entity) {
    for (auto pair : entity.treatments)
        treatments.remove(*pair.second);
    Owner& owner = *entity.owner;
    owner.animals.erase(entity.id);
    Repository::remove(entity);
}

void TreatmentRepository::load(
    std::istream& is, const AnimalRepository& animals
) {
    Repository<Treatment>::load(is);
    for (auto [id, treatment] : entities) {
        auto& animal = animals.at(treatment->animalId);
        treatment->animal = &animal;
        animal.treatments.emplace(id, treatment);
    }
}

Treatment* TreatmentRepository::createNew(Animal& animal) {
    auto treatment = new Treatment();
    treatment->id = getNextId();
    treatment->animalId = animal.id;
    treatment->animal = &animal;
    entities[treatment->id] = treatment;
    animal.treatments.emplace(treatment->id, treatment);
    return treatment;
}

void TreatmentRepository::remove(Treatment& entity) {
    Animal& animal = *entity.animal;
    animal.treatments.erase(entity.id);
    Repository::remove(entity);
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
