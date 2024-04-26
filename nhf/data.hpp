#ifndef DATA_HPP
#define DATA_HPP

#include <cstddef>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <utility>
#include <vector>

class Serializable {
  public:
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;
    virtual ~Serializable() = default;
};

class Entity : public Serializable {
    size_t id;

  public:
    Entity(const Entity&) = delete; // disable copying
    void operator=(const Entity&) = delete;
    Entity(size_t id);
    virtual ~Entity() override = default;
};

struct Animal;
struct Treatment;

struct Owner final : public Entity {
    std::string name;
    std::string address;
    std::string contact;
    std::vector<Animal*> animals;

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

  public:
    ~Owner() override = default;
};

struct Animal final : public Entity {
    Owner* owner;
    std::string name;
    std::string species;
    std::vector<Treatment*> treatments;

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

  public:
    ~Animal() override = default;
};

struct Treatment final : public Entity {
    Animal* animal;
    time_t date;
    bool was_rabies_vaccinated;
    std::string description;

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

  public:
    ~Treatment() override = default;
};

template <typename TEntity> class Repository {
  protected:
    std::unordered_map<size_t, TEntity*> entities;

  public:
    virtual void load(std::istream& is) { /*TODO*/ }

    virtual void save(std::ostream& os) { /*TODO*/ }

    bool contains(size_t id) { /*TODO*/ throw; }

    TEntity& getById(size_t id) { /*TODO*/ throw; }

    ~Repository() {
        for (std::pair<size_t, TEntity*> kv : entities)
            delete kv.second;
    }
};

class TreatmentRepository : public Repository<Treatment> {};

class AnimalRepository : public Repository<Animal> {
    TreatmentRepository& treatments;

  public:
    AnimalRepository(TreatmentRepository& treatments);
};

class OwnerRepository : public Repository<Owner> {
    AnimalRepository& animals;

  public:
    OwnerRepository(AnimalRepository& animals);
};

struct AppData {
    TreatmentRepository treatments;
    AnimalRepository animals;
    OwnerRepository owners;

  private:
    void load(
        std::istream& ownersStream,
        std::istream& animalsStream,
        std::istream& treatmentsStream
    );

    AppData();

  public:
    AppData(
        std::istream& ownersStream,
        std::istream& animalsStream,
        std::istream& treatmentsStream
    );

    AppData(
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

#endif
