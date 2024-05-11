#include "utils.hpp"
#include <functional>

StringEditor::StringEditor(const std::string& s) {
    oldValue = new std::string(s);
}

bool StringEditor::handleInput(char input) { /*TODO*/ throw; }

StringEditor::~StringEditor() { /*TODO*/ }

/// @brief Ensures index is less than count
void utils::clampIndex(size_t& index, size_t count) {
    if (index >= count)
        index = count - 1;
}
