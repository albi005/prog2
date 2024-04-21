#ifndef LISTVIEW_HPP
#define LISTVIEW_HPP

#include "callback.hpp"
#include "canvas.hpp"
#include "utils.hpp"
#include "view.hpp"
#include <string>
#include <vector>

class ListRange {
  public:
    virtual void onBeforeMeasure() {}
    virtual int getHeight() const { return 1; }
    virtual bool getIsInteractive() const { return false; }
    virtual void draw(
        const ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const = 0;
    virtual void handleInput(char input, size_t selectedIndex) const {}
    virtual ~ListRange() {}
};

class PropertyRange : public ListRange {
    const char* title;
    std::string& value;
    virtual void draw(
        const ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const;

  public:
    PropertyRange(const char* title, std::string& value)
        : title(title), value(value) {}
    virtual ~PropertyRange() {}
};

class EditablePropertyRange : public PropertyRange {
    StringEditor* editor = nullptr;
    virtual bool getIsInteractive() const { return true; }
    virtual void draw(
        const ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const;
    virtual void handleInput(char input, size_t selectedIndex) const;

  public:
    EditablePropertyRange(const char* title, std::string& value)
        : PropertyRange(title, value) {}
    bool handleInput(char input);
    virtual ~EditablePropertyRange();
};

class LinkPropertyRange : public PropertyRange {
    OpenLinkCallback& open;

    virtual bool getIsInteractive() const { return true; }
    virtual void draw(
        const ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const;
    virtual void handleInput(char input, size_t selectedIndex) const;

  public:
    LinkPropertyRange(
        const char* title, std::string& value, OpenLinkCallback& open
    )
        : PropertyRange(title, value), open(open) {}
    bool handleInput(char input);
    virtual ~LinkPropertyRange();
};

class PaddingRange : public ListRange {
    int height;

  public:
    PaddingRange(int height = 1) : height(height) {}
    virtual void draw(
        const ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const = 0;
};

class AddButtonRange : public ListRange {
    CreateEntityCallback& createEntity;
    virtual bool getIsInteractive() const { return true; }
    virtual void draw(
        const ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const;
    virtual void handleInput(char input, size_t selectedIndex) const;

  public:
    AddButtonRange(CreateEntityCallback& createEntity)
        : createEntity(createEntity) {}
};

class ListView : public View {
    size_t selectedItemIndex;
    std::vector<ListRange*>* ranges;

  public:
    ListView(std::vector<ListRange*>* ranges);
    virtual void draw(const ICanvas&);
    virtual bool handleInput(char input);
};

#endif
