#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

struct Serializable {
    virtual void serialize(std::ostream& os) const = 0;

    /// @returns whether the deserialization was successful
    virtual bool deserialize(std::istream& is) = 0;

    virtual ~Serializable() = default;
};

struct Entity : public Serializable {
    size_t id;

    Entity() = default;
    Entity(const Entity&) = delete; // disable copying
    void operator=(const Entity&) = delete;
    virtual ~Entity() override = default;
};

struct Animal;

struct Owner final : public Entity {
    std::string name;
    std::string address;
    std::string contact;

    std::unordered_map<size_t, Animal*> animals;

    void serialize(std::ostream& os) const override;
    bool deserialize(std::istream& is) override;

  public:
    ~Owner() override = default;
};

struct Treatment;

struct Animal final : public Entity {
    size_t ownerId;
    std::string name;
    std::string species;

    Owner* owner;
    std::unordered_map<size_t, Treatment*> treatments;

    void serialize(std::ostream& os) const override;
    bool deserialize(std::istream& is) override;

  public:
    ~Animal() override = default;
};

struct Treatment final : public Entity {
    size_t animalId;
    time_t date;
    bool wasVaccinated;
    std::string description;

    Animal* animal;

    void serialize(std::ostream& os) const override;
    bool deserialize(std::istream& is) override;

  public:
    ~Treatment() override = default;
};
