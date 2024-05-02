#pragma once

#include "entities.hpp"
#include <cstddef>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename TEntity> class Repository {
  protected:
    std::unordered_map<size_t, TEntity*> entities;

    size_t getNextId() const {
        size_t maxId = 0;
        for (std::pair<size_t, TEntity*> kv : entities)
            if (kv.first > maxId)
                maxId = kv.first;
        return maxId + 1;
    }

    void load(std::istream& is) {
        if (entities.size() > 0)
            throw std::runtime_error("load called on non-empty repository");
        while (is.good()) {
            TEntity* entity = new TEntity();
            entity->deserialize(is);
            entities[entity->id] = entity;
        }
    }

  public:
    virtual void save(std::ostream& os) const {
        for (std::pair<size_t, TEntity*> kv : entities)
            kv.second->serialize(os);
    }

    TEntity* tryGetById(size_t id) const { /*TODO*/ throw; }

    auto begin() const { return entities.begin(); }

    auto end() const { return entities.end(); }

    ~Repository() {
        for (std::pair<size_t, TEntity*> kv : entities)
            delete kv.second;
    }
};

class AnimalRepository;
class TreatmentRepository;

class OwnerRepository : public Repository<Owner> {
    AnimalRepository& animals; // needed by destructor

  public:
    OwnerRepository(AnimalRepository& animals);
    using Repository<Owner>::load;
    Owner* createNew();
};

class AnimalRepository : public Repository<Animal> {
    TreatmentRepository& treatments; // needed by destructor

  public:
    AnimalRepository(TreatmentRepository& treatments);
    void load(std::istream& is, const OwnerRepository& owners);
    Animal* createNew(Owner& owner);
};

class TreatmentRepository : public Repository<Treatment> {
  public:
    void load(std::istream& is, const AnimalRepository& animals);
    Treatment* createNew(Animal& animal);
};

struct Data {
    TreatmentRepository treatments;
    AnimalRepository animals;
    OwnerRepository owners;

  private:
    void load(
        std::istream& ownersStream,
        std::istream& animalsStream,
        std::istream& treatmentsStream
    );

    Data();

  public:
    Data(
        std::istream& ownersStream,
        std::istream& animalsStream,
        std::istream& treatmentsStream
    );

    Data(
        const char* ownersFile,
        const char* animalsFile,
        const char* treatmentsFile
    );

    void save(
        std::ostream& ownersStream,
        std::ostream& animalsStream,
        std::ostream& treatmentsStream
    );

    void save(
        const char* ownersFile,
        const char* animalsFile,
        const char* treatmentsFile
    );
};
