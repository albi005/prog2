#pragma once

#include "Canvas.hpp"
#include "View.hpp"
#include "utils.hpp"
#include <functional>
#include <string>
#include <vector>

/// @brief Represents one or more lines drawn by a ListView.
class ListRange {
  public:
    /// Draws the ListRange onto an ICanvas
    /// @param firstIndex The index of the first visible line. Should be drawn
    /// at Y=0 on the canvas
    /// @param lastIndex The index of the last visible line
    /// @param selectedIndex The index of the currently selected line
    virtual void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const = 0;

    // Called before getHeight and draw. Can be used to calculate and cache
    // all the data needed to efficiently draw this ListRange.
    virtual void onBeforeMeasure();

    /// @returns The number of lines this ListRange takes up.
    virtual size_t getHeight() const;

    /// @returns Whether this ListRange can be selected and interacted with
    /// @remarks If false, handleInput is never called
    virtual bool isInteractive() const;

    virtual bool handleInput(char input, size_t selectedIndex);

    virtual ~ListRange();
};

// ListRange that draws a title and a value. Takes up a single line
class PropertyRange : public ListRange {
  protected:
    const char* title;
    std::string& value;

  public:
    PropertyRange(const char* title, std::string& value);
    virtual void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;
    virtual ~PropertyRange();
};

/// @brief PropertyRange that allows editing its value.
/// @details To edit, select this ListRange and press Enter.
/// Pressed keys are appended to the target string, while backspace can be used
/// to delete characters from the back. Press Enter to save. Press Escape
/// to cancel.
class EditablePropertyRange : public PropertyRange {
    StringEditor* editor = nullptr;

    virtual void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;

    virtual bool isInteractive() const override;
    virtual bool handleInput(char input, size_t selectedIndex) override;

  public:
    EditablePropertyRange(const char* title, std::string& value);
    virtual ~EditablePropertyRange();
};

/// @brief PropertyRange that can execute a function when selected. Used to link
/// to another page.
class LinkPropertyRange : public PropertyRange {
    std::function<void()> open;

    virtual bool isInteractive() const override;

    virtual void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;

    bool handleInput(char input, size_t selectedIndex) override;

  public:
    LinkPropertyRange(
        const char* title, std::string& value, std::function<void()> open
    );

    virtual ~LinkPropertyRange() override;
};

// ListRange that draws empty lines
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

    size_t getHeight() const override;
};

/// @brief ListRange that draws a + button. When selected and Enter is pressed,
/// calls createEntity
class AddButtonRange : public ListRange {
    std::function<void()> createEntity;

    virtual void draw(
        ICanvas& canvas,
        size_t firstIndex,
        size_t lastIndex,
        size_t selectedIndex
    ) const override;

    virtual bool isInteractive() const override;
    virtual bool handleInput(char input, size_t selectedIndex) override;

  public:
    AddButtonRange(std::function<void()> createEntity);
};

/// @brief A scrollable list. Draws ListRange s.
/// @details When drawing, it first measures the height of its children,
/// then calls draw on each child that is visible.
/// When handling input, it calls handleInput on the selected ListRange, passing
/// in the index of the selected item inside the ListRange.
class ListView final : public View {
    size_t selectedItemIndex = 0;
    std::vector<ListRange*>* ranges;

    /// @brief sum of the heights of the ranges
    size_t listHeight;

    /// @brief number of lines scrolled off-screen from the top
    size_t scroll = 0;

    /// @brief number of selectable lines
    /// @details set in draw() and used in handleInput()
    size_t interactiveCount;

    /// @brief pointer to the range that contains the currently selected line
    /// @details set in draw() and used in handleInput()
    ListRange* selectedRange = nullptr;

    /// @brief index of the selected line inside selectedRange
    /// @details set in draw() and used in handleInput()
    size_t selectedIndexInRange;

    /// @brief index of the line that is selected
    /// including non-interactive lines
    size_t selectedLineIndex;

  public:
    ListView(std::vector<ListRange*>* ranges);
    virtual void draw(ICanvas& canvas) override;
    virtual bool handleInput(char input) override;
    ~ListView() override;

  private:
    /// @brief Sets interactiveCount, selectedRange and selectedIndexInRange and
    void updateSelectionAndMeasure();

  public:
    struct ScrollBounds {
        size_t min, max;
    };

  public:
    // pure function to make it easier to reason about
    __attribute__((const)) static ScrollBounds calculateScrollBounds(
        size_t selectedLineIndex, size_t listHeight, size_t availableHeight
    );
};
