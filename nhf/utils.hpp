#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

/// @brief Helper class for editing a string
/// @details To edit, call handleInput with the pressed key.
/// Pressed keys are appended to the target string, while backspace can be used
/// to delete characters from the back. Press Enter to save. Press Escape
/// to cancel.
class StringEditor {
    std::string& value;
    std::string oldValue = nullptr;

  public:
    StringEditor(std::string& s);
    bool handleInput(char input); // returns true when done editing
    ~StringEditor();
};

namespace utils {
    void clampIndex(size_t& index, size_t count);

    /// @brief Whether c is a UTF-8 continuation byte
    /// @see https://en.wikipedia.org/wiki/UTF-8#Encoding
    bool isContinuationByte(char c);
} // namespace utils

#endif
