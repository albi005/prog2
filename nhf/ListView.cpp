#include "ListView.hpp"
#include "constants.h"

void ListRange::onBeforeMeasure() {}

int ListRange::getHeight() const { return 1; }

bool ListRange::isInteractive() const { return false; }

bool ListRange::handleInput(char input, size_t selectedIndex) {
    /* TODO: throw an exception */
    return false;
}

ListRange::~ListRange() {}

PropertyRange::PropertyRange(const char* title, std::string& value)
    : title(title), value(value) {}

void PropertyRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const {
    canvas.draw({0, 0}, ON_SURFACE_VARIANT, canvas.getSurfaceColor())
        << title << ": " << value;
}

PropertyRange::~PropertyRange() {}

bool EditablePropertyRange::isInteractive() const { return true; }

void EditablePropertyRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const {
    bool isSelected = selectedIndex == 0;
    bool isEditing = editor != nullptr;

    Color surface = canvas.getSurfaceColor();

    canvas.draw({0, 0}, ON_SURFACE_VARIANT, surface) << title << ": ";

    if (isSelected) {
        if (isEditing)
            canvas.draw(ON_PRIMARY, PRIMARY);
        else
            canvas.draw(surface, ON_SURFACE);
    } else {
        canvas.draw(ON_SURFACE, surface);
    }
    canvas.draw() << (value.empty() ? " " : value);
}

bool EditablePropertyRange::handleInput(char input, size_t selectedIndex) {
    // if editing
    if (editor != nullptr) {
        bool finished = editor->handleInput(input);
        if (finished) {
            delete editor;
            editor = nullptr;
        }
        return true;
    }

    if (input == KEY_ENTER) {
        editor = new StringEditor(value);
        return true;
    }

    return false;
}

EditablePropertyRange::EditablePropertyRange(
    const char* title, std::string& value
)
    : PropertyRange(title, value) {}

EditablePropertyRange::~EditablePropertyRange() = default;

bool LinkPropertyRange::isInteractive() const { return true; }

void LinkPropertyRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const {
    Color surface = canvas.getSurfaceColor();
    canvas.draw({0, 0}, ON_SURFACE_VARIANT, surface) << title << ": ";

    bool isSelected = selectedIndex == 0;
    if (isSelected) {
        canvas.draw(ON_PRIMARY, PRIMARY) << value;
    } else {
        canvas.draw(ON_SURFACE_VARIANT, surface) << value;
    }
}

bool LinkPropertyRange::handleInput(char input, size_t selectedIndex) {
    if (input == KEY_ENTER) {
        open();
        return true;
    }
    return false;
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

bool AddButtonRange::isInteractive() const { return true; }

void AddButtonRange::draw(
    ICanvas& canvas, size_t firstIndex, size_t lastIndex, size_t selectedIndex
) const {
    bool selected = selectedIndex == 0;
    Color fg = selected ? ON_PRIMARY : PRIMARY;
    Color bg = selected ? PRIMARY : ON_PRIMARY;
    canvas.draw({2, 0}, fg, bg) << " + Hozzáadás ";
}

bool AddButtonRange::handleInput(char input, size_t selectedIndex) {
    if (input == KEY_ENTER) {
        createEntity();
        return true;
    }
    return false;
}

AddButtonRange::AddButtonRange(std::function<void()> createEntity)
    : createEntity(createEntity) {}

ListView::ListView(std::vector<ListRange*>* ranges) : ranges(ranges) {}

void ListView::updateSelectionAndMeasure() {
    interactiveCount = 0;
    selectedRange = nullptr;
    selectedIndexInRange = 0;
    selectedLineIndex = 0;
    listHeight = 0; // number of lines so far
    for (auto range : *ranges) {
        range->onBeforeMeasure();

        size_t lineCountBefore = listHeight; // line count above this range
        listHeight += range->getHeight();

        if (!range->isInteractive())
            continue;

        size_t height = range->getHeight();
        if (height == 0)
            continue;
        size_t firstIndex = interactiveCount;
        interactiveCount += height;

        // Find the selected range:

        // already found, finish counting lines
        if (selectedItemIndex < firstIndex)
            continue;

        // Store the last interactive line until we reach the selected one.
        // If the last item is deleted this gives us the last interactive
        // line
        selectedRange = range;
        selectedIndexInRange = height - 1;

        // this is the one
        if (selectedItemIndex >= firstIndex) {
            selectedIndexInRange = selectedItemIndex - firstIndex;
        }

        selectedLineIndex = lineCountBefore + selectedIndexInRange;
    }
}

void ListView::draw(ICanvas& canvas) {
    updateSelectionAndMeasure();

    size_t availableHeight = canvas.getSize().h;
    auto [minScroll, maxScroll] =
        calculateScrollBounds(selectedLineIndex, listHeight, availableHeight);
    scroll = std::clamp(scroll, minScroll, maxScroll);

    size_t firstVisibleLine = scroll + 1; // 1-based
    size_t lastVisibleLine = scroll + availableHeight;

    size_t lineCount = 0; // number of lines before the current range
    for (auto range : *ranges) {
        size_t height = range->getHeight();
        size_t linesBefore = lineCount;
        lineCount += height;
        size_t firstLine = linesBefore + 1; // 1-based
        size_t lastLine = lineCount;

        if (lastLine < firstVisibleLine || firstLine > lastVisibleLine)
            continue;

        size_t firstVisibleLineOfRange = std::max(firstVisibleLine, firstLine);
        size_t lastVisibleLineOfRange = std::min(lastVisibleLine, lastLine);
        size_t padTop = firstVisibleLineOfRange - firstVisibleLine;
        size_t padBottom = lastVisibleLine - lastVisibleLineOfRange;
        PaddedCanvas paddedCanvas(0, padTop, 0, padBottom, canvas);

        // index of the first visible line *inside* the range.
        // tells the range which index to start drawing from
        size_t firstIndex = std::max(firstVisibleLine, firstLine) - firstLine;
        size_t lastIndex = std::min(lastVisibleLine, lastLine) - firstLine;

        // index of the selected line *inside* the range.
        // tells the range which line is selected
        size_t selectedIndex =
            selectedRange == range ? selectedIndexInRange : range->getHeight();

        range->draw(paddedCanvas, firstIndex, lastIndex, selectedIndex);
    }
}

bool ListView::handleInput(char input) {
    if (this->interactiveCount == 0)
        return false;

    if (selectedRange != nullptr)
        if (selectedRange->handleInput(input, selectedIndexInRange))
            return true;

    switch (input) {
        case KEY_DOWN:
        case 'j':
            selectedItemIndex = (selectedItemIndex + 1) % interactiveCount;
            return true;
        case KEY_UP:
        case 'k':
            selectedItemIndex =
                (selectedItemIndex - 1 + interactiveCount) % interactiveCount;
            return true;
    }

    return false;
}

ListView::ScrollBounds ListView::calculateScrollBounds(
    size_t selectedLineIndex, size_t listHeight, size_t availableHeight
) {
    // https://neovim.io/doc/user/options.html#'scrolloff'
    // number of lines to keep above and below the cursor visible when
    // possible. disallow scrolling if the list fits on the screen
    const size_t scrollOff = 8;

    std::ignore = selectedLineIndex + listHeight + scrollOff + availableHeight;

    /*TODO: scroll bounds calculation*/
    return {0, 0};
}
