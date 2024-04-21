#ifndef DATA_HPP
#define DATA_HPP

#include <cstddef>
#include <istream>
#include <vector>
struct Owner;
struct Animal;
struct Treatment;

class Serializable {
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;
};

class Entity : Serializable {
  public:
    size_t id;
    size_t index; // Index in the repository
};

struct Owner {
    std::string name;
    std::string address;
    std::string contact;
    std::vector<Animal> animals;
};

struct Animal {
    Owner* owner;
    std::vector<Treatment> treatments;
    std::string name;
    std::string species;
};

struct Treatment {
    Animal* animal;
    time_t date;
    bool was_rabies_vaccinated;
    std::string description;
};

template <typename TEntity> class Repository {
  protected:
    std::vector<TEntity*> entities;

  public:
    virtual void load(const std::string& fileName);
    virtual void save();
    TEntity& getById(size_t id);
    ~Repository() { save(); }
};

class OwnerRepository : public Repository<Owner> {};
class AnimalRepository : public Repository<Animal> {};
class TreatmentRepository : public Repository<Treatment> {};

struct AppData {
    OwnerRepository owners;
    AnimalRepository animals;
    TreatmentRepository treatments;

    AppData() {}

  public:
    static AppData create() { return AppData(); }
};

#endif
