#if RUNTEST || CPORTA
#include "App.hpp"
#include "OstreamCanvas.hpp"
#include "constants.hpp"
#include "data.hpp"
#include "gtest_lite.h"
#include <sstream>

class Scenario {
    View* view;
    std::stringstream output;
    std::stringstream input;
    OstreamCanvas canvas;
    std::string lastFrame;

  public:
    Scenario(View* view) : view(view), canvas(output) {
        // set screen size to 90 columns by 20 rows
        std::stringstream tmp(CSI "20;90R");
        canvas.updateScreenSize(tmp);
    }

    template <class T> Scenario& operator<<(T t) {
        input.clear();
        input << t;
        return *this;
    }

  private:
    void updateLastFrame() {
        if (!input.eof()) {
            while (true) {
                view->draw(canvas);
                char c = input.get();
                if (input.eof())
                    break;
                view->handleInput(c);
            }
            output.clear();            // reset status bits
            output.str(std::string()); // clear buffer
            input.str(std::string());
            view->draw(canvas);
            lastFrame = output.str();
        }
    }

  public:
    bool isVisible(const char* text) {
        updateLastFrame();
        return lastFrame.find(text) != std::string::npos;
    }

    // print the current frame to stdout
    void print(std::ostream& os = std::cout) {
        updateLastFrame();
        // clear screen so that the next line will be the first visible line
        os << CSI "2J";
        // print frame
        os << lastFrame;
        // move to next line and reset style
        os << CSI "21;1H" CSI "m";
        os.flush();
    }

    Scenario(const Scenario&) = delete;
    Scenario& operator=(const Scenario&) = delete;

    ~Scenario() { delete view; }
};

std::ostream& operator<<(std::ostream& os, Scenario& scenario) {
    scenario.print(os);
    return os;
}

/// @brief Tests whether text is visible. If not, prints the current frame to
/// stdout
#define EXPECT_VISIBLE(scenario, text)                                         \
    gtest_lite::test.expect(                                                   \
        scenario.isVisible(text),                                              \
        __FILE__,                                                              \
        __LINE__,                                                              \
        "EXPECT_VISIBLE(" #text ")"                                            \
    ) << scenario;

/// @brief Tests whether text is not visible. If it is, prints the current frame
/// to stdout
#define EXPECT_NOT_VISIBLE(scenario, text)                                     \
    gtest_lite::test.expect(                                                   \
        !scenario.isVisible(text),                                             \
        __FILE__,                                                              \
        __LINE__,                                                              \
        "EXPECT_VISIBLE(" #text ")"                                            \
    ) << scenario;

int main() {
    GTINIT(std::cin);

    TEST(Scenario, EditTreatmentDescription) {
        Data data = Data("owners", "animals", "treatments");
        Scenario s(App::create(data));

        // switch to OwnersPage, go down, switch to AnimalsPage, go down, switch
        // to VaccinationsPage
        s << KEY_TAB << "jjjjjjj" << KEY_TAB << "jjjjjjjjj" << KEY_TAB;

        // open first owner, go down to an animal, open, select a treatment
        s << KEY_ENTER << "jjjj" << KEY_ENTER << KEY_ENTER << "jjjj"
          << KEY_ENTER << "jjj";

        // edit treatment description then revert changes
        s << KEY_ENTER << "még valami";
        EXPECT_VISIBLE(s, "még valami");
        s << KEY_ESCAPE;
        EXPECT_NOT_VISIBLE(s, "még valami");

        // edit treatment description then save
        s << KEY_ENTER << "inkább ez";
        EXPECT_VISIBLE(s, "inkább ez");
        s << KEY_ENTER;
        EXPECT_VISIBLE(s, "inkább ez");

        // close all pages
        s << "qqq";

        EXPECT_FALSE(s.isVisible("Tulajdonosok"));
    }
    END GTEND(std::cerr);
}
#endif