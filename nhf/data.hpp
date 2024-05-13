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
        while (true) {
            TEntity* entity = new TEntity();
            if (!entity->deserialize(is)) {
                delete entity;
                break;
            }
            entities[entity->id] = entity;
        }
    }

  public:
    Repository() = default;

    virtual void save(std::ostream& os) const {
        for (std::pair<size_t, TEntity*> kv : entities)
            kv.second->serialize(os);
    }

    bool empty() const { return entities.empty(); }

    size_t size() const { return entities.size(); }

    TEntity& at(size_t id) const { return *entities.at(id); }

    auto begin() const { return entities.begin(); }

    auto end() const { return entities.end(); }

    virtual void remove(TEntity& entity) {
        entities.erase(entity.id);
        delete &entity;
    }

    // disable copying
    Repository(const Repository&) = delete;
    void operator=(const Repository&) = delete;

    ~Repository() {
        for (std::pair<size_t, TEntity*> kv : entities)
            delete kv.second;
    }
};

class AnimalRepository;
class TreatmentRepository;

class OwnerRepository final : public Repository<Owner> {
    AnimalRepository& animals; // needed by destructor

  public:
    OwnerRepository(AnimalRepository& animals);
    using Repository<Owner>::load;
    Owner* createNew();
    void remove(Owner& owner) override;
};

class AnimalRepository final : public Repository<Animal> {
    TreatmentRepository& treatments; // needed by destructor

  public:
    AnimalRepository(TreatmentRepository& treatments);
    void load(std::istream& is, const OwnerRepository& owners);
    Animal* createNew(Owner& owner);
    void remove(Animal& entity) override;
};

class TreatmentRepository final : public Repository<Treatment> {
  public:
    void load(std::istream& is, const AnimalRepository& animals);
    Treatment* createNew(Animal& animal);
    void remove(Treatment& entity) override;
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

    // disable copying // rust fixes this // i hate this language
    // why is this not the default
    Data(const Data&) = delete;
    void operator=(const Data&) = delete;
};
