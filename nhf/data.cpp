#include "data.hpp"

Entity::Entity(size_t id) : id(id) {}

void Owner::serialize(std::ostream& os) const { /* BEGIN TODO */ }

void Owner::deserialize(std::istream& is) {}

void Animal::serialize(std::ostream& os) const {}

void Animal::deserialize(std::istream& is) {}

void Treatment::serialize(std::ostream& os) const {}

void Treatment::deserialize(std::istream& is) { /* END TODO */ }

AnimalRepository::AnimalRepository(TreatmentRepository& treatments)
    : treatments(treatments) {}

OwnerRepository::OwnerRepository(AnimalRepository& animals)
    : animals(animals) {}

void AppData::load(
    std::istream& ownersStream,
    std::istream& animalsStream,
    std::istream& treatmentsStream
) {
    treatments.load(treatmentsStream);
    animals.load(animalsStream);
    owners.load(ownersStream);
}

AppData::AppData() : treatments(), animals(treatments), owners(animals) {}

AppData::AppData(
    std::istream& ownersStream,
    std::istream& animalsStream,
    std::istream& treatmentsStream
)
    : AppData() {
    load(ownersStream, animalsStream, treatmentsStream);
}

AppData::AppData(
    const char* ownersFile, const char* animalsFile, const char* treatmentsFile
)
    : AppData() {
    std::ifstream ownersStream(ownersFile, std::ifstream::in);
    std::ifstream animalsStream(animalsFile, std::ifstream::in);
    std::ifstream treatmentsStream(treatmentsFile, std::ifstream::in);
    load(ownersStream, animalsStream, treatmentsStream);
}

void AppData::save(
    std::ostream& ownersStream,
    std::ostream& animalsStream,
    std::ostream& treatmentsStream
) {
    treatments.save(treatmentsStream);
    animals.save(animalsStream);
    owners.save(ownersStream);
}

// TODO: test saving to a new file
void AppData::save(
    const char* ownersFile, const char* animalsFile, const char* treatmentsFile
) {
    std::ofstream ownersStream(ownersFile);
    std::ofstream animalsStream(animalsFile);
    std::ofstream treatmentsStream(treatmentsFile);
    save(ownersStream, animalsStream, treatmentsStream);
}
