#include "entities.hpp"

void Owner::serialize(std::ostream& os) const {
    os << id << '\n';
    os << name << '\n';
    os << address << '\n';
    os << contact << '\n';
}

void Owner::deserialize(std::istream& is) {
    is >> id;
    std::getline(is, name);
    std::getline(is, address);
    std::getline(is, contact);
}

void Animal::serialize(std::ostream& os) const {
    os << id << '\n';
    os << ownerId << '\n';
    os << name << '\n';
    os << species << '\n';
}

void Animal::deserialize(std::istream& is) {
    is >> id >> ownerId;
    std::getline(is, name);
    std::getline(is, species);
}

void Treatment::serialize(std::ostream& os) const {
    os << id << '\n';
    os << animalId << '\n';
    os << description << '\n';
    os << date << '\n';
    os << was_rabies_vaccinated << '\n';
}

void Treatment::deserialize(std::istream& is) {
    is >> id >> animalId;
    std::getline(is, description);
    is >> date >> was_rabies_vaccinated;
}
