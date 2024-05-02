#pragma once

#include "Canvas.hpp"
#include "View.hpp"
#include "utils.hpp"
#include <functional>
#include <string>
#include <vector>

class ListRange {
  public:
    virtual void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const = 0;

    virtual void onBeforeMeasure();
    virtual int getHeight() const;
    virtual bool getIsInteractive() const;
    virtual bool handleInput(char input, size_t selectedIndex) const;

    virtual ~ListRange();
};

class PropertyRange : public ListRange {
    const char* title;
    std::string& value;

    virtual void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;

  public:
    PropertyRange(const char* title, std::string& value);
    virtual ~PropertyRange();
};

class EditablePropertyRange : public PropertyRange {
    StringEditor* editor = nullptr;

    virtual void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;

    virtual bool getIsInteractive() const override;
    virtual bool handleInput(char input, size_t selectedIndex) const override;

  public:
    EditablePropertyRange(const char* title, std::string& value);
    virtual ~EditablePropertyRange();
};

class LinkPropertyRange : public PropertyRange {
    std::function<void()> open;

    virtual bool getIsInteractive() const override;

    virtual void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;

    bool handleInput(char input, size_t selectedIndex) const override;

  public:
    LinkPropertyRange(
        const char* title, std::string& value, std::function<void()> open
    );

    virtual ~LinkPropertyRange() override;
};

class PaddingRange final : public ListRange {
    int height;

  public:
    PaddingRange(int height = 1);

    void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;

    int getHeight() const override;
};

class AddButtonRange : public ListRange {
    std::function<void()> createEntity;

    virtual void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;

    virtual bool getIsInteractive() const override;
    virtual bool handleInput(char input, size_t selectedIndex) const override;

  public:
    AddButtonRange(std::function<void()> createEntity);
};

class ListView : public View {
    size_t selectedItemIndex;
    std::vector<ListRange*>* ranges;

  public:
    ListView(std::vector<ListRange*>* ranges);
    virtual void draw(ICanvas& canvas) override;
    virtual bool handleInput(char input) override;
};
