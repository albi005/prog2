#include "ListView.hpp"

void ListRange::onBeforeMeasure() {}

int ListRange::getHeight() const { return 1; }

bool ListRange::getIsInteractive() const { return false; }

bool ListRange::handleInput(char input, size_t selectedIndex) const {
    /*TODO*/
    throw;
}

ListRange::~ListRange() {}

PropertyRange::PropertyRange(const char* title, std::string& value)
    : title(title), value(value) {}

void PropertyRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const { /*TODO*/ }

PropertyRange::~PropertyRange() {}

bool EditablePropertyRange::getIsInteractive() const { return true; }

void EditablePropertyRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const { /*TODO*/ }

bool EditablePropertyRange::handleInput(char input, size_t selectedIndex)
    const {
    /*TODO*/
    throw;
}

EditablePropertyRange::EditablePropertyRange(
    const char* title, std::string& value
)
    : PropertyRange(title, value) {}

EditablePropertyRange::~EditablePropertyRange() { /*TODO*/ }

bool LinkPropertyRange::getIsInteractive() const { return true; }

void LinkPropertyRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const { /*TODO*/ }

bool LinkPropertyRange::handleInput(char input, size_t selectedIndex) const {
    /*TODO*/
    throw;
}

LinkPropertyRange::LinkPropertyRange(
    const char* title, std::string& value, std::function<void()> open
)
    : PropertyRange(title, value), open(open) {}

LinkPropertyRange::~LinkPropertyRange() {}

PaddingRange::PaddingRange(int height) : height(height) {}

void PaddingRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const {}

int PaddingRange::getHeight() const { return height; }

bool AddButtonRange::getIsInteractive() const { return true; }

void AddButtonRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const { /*TODO*/ }

bool AddButtonRange::handleInput(char input, size_t selectedIndex) const {
    /*TODO*/
    throw;
}

AddButtonRange::AddButtonRange(std::function<void()> createEntity)
    : createEntity(createEntity) {}

ListView::ListView(std::vector<ListRange*>* ranges) { /*TODO*/ }

void ListView::draw(ICanvas& canvas) { /*TODO*/ }

bool ListView::handleInput(char input) { /*TODO*/ throw; }
