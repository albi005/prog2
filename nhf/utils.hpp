#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

class StringEditor {
    std::string* oldValue = nullptr;

  public:
    StringEditor(const std::string& s) { oldValue = new std::string(s); }
    bool handleInput(char input); // returns true when done editing
    ~StringEditor();
};

#endif
