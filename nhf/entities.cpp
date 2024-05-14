#include "entities.hpp"

void Owner::serialize(std::ostream& os) const {
    os << id << '\n';
    os << name << '\n';
    os << address << '\n';
    os << contact << '\n';
}

bool Owner::deserialize(std::istream& is) {
    if (!(is >> id))
        return false;
    is.ignore(); // skip newline
    std::getline(is, name);
    std::getline(is, address);
    std::getline(is, contact);
    return true;
}

void Animal::serialize(std::ostream& os) const {
    os << id << '\n';
    os << owner->id << '\n';
    os << name << '\n';
    os << species << '\n';
}

bool Animal::deserialize(std::istream& is) {
    if (!(is >> id))
        return false;
    is >> ownerId;
    is.ignore(); // skip newline
    std::getline(is, name);
    std::getline(is, species);
    return true;
}

void Treatment::serialize(std::ostream& os) const {
    os << id << '\n';
    os << animal->id << '\n';
    os << date << '\n';
    os << wasVaccinated << '\n';
    os << description << '\n';
}

bool Treatment::deserialize(std::istream& is) {
    if (!(is >> id))
        return false;
    is >> animalId >> date >> wasVaccinated;
    is.ignore(); // skip newline
    std::getline(is, description);
    return true;
}
