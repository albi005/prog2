#pragma once

#include <iostream>
#include <vector>

struct Serializable {
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;
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

    std::vector<Animal*> animals;

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

  public:
    ~Owner() override = default;
};

struct Treatment;

struct Animal final : public Entity {
    size_t ownerId;
    std::string name;
    std::string species;

    Owner* owner;
    std::vector<Treatment*> treatments;

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

  public:
    ~Animal() override = default;
};

struct Treatment final : public Entity {
    size_t animalId;
    time_t date;
    bool was_rabies_vaccinated;
    std::string description;

    Animal* animal;

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

  public:
    ~Treatment() override = default;
};
