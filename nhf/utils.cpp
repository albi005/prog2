#include "utils.hpp"
#include "constants.h"
#include <functional>

StringEditor::StringEditor(std::string& s) : value(s), oldValue(s) {}

bool StringEditor::handleInput(char input) {
    switch (input) {
        case KEY_ENTER:
            return true;
        case KEY_BACKSPACE:
            if (value.empty())
                return false;
            while (utils::isContinuationByte(value[value.size() - 1]))
                value.pop_back();
            value.pop_back();
            return false;
        case KEY_ESCAPE:
            value = oldValue;
            return true;
        default: {
            /*TODO: handle funny business*/
            value.push_back(input);
            return false;
        }
    }
}

StringEditor::~StringEditor() = default;

/// @brief Ensures index is less than count
void utils::clampIndex(size_t& index, size_t count) {
    if (index >= count)
        index = count - 1;
}

bool utils::isContinuationByte(char c) {
    return (c & 0b11000000) == 0b10000000;
}

int utils::daysSince(time_t date, time_t now) {
    return (now - date) / (60 * 60 * 24);
}
