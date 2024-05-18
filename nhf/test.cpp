#undef MEMTRACE // messes with explicitly deleting functions
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
    explicit Scenario(View* view) : view(view), canvas(output) {
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

    // print the current frame to a character stream
    void print(std::ostream& os = std::cout) {
        updateLastFrame();
        // clear screen so that the next line will be the first visible line
        os << CSI "2J";

        // print frame
#ifdef CPORTA
        // I give up. Cporta is broken.
        // This works:
        for (size_t i = 0; i < lastFrame.size(); i++) {
            char c = lastFrame[i];
            os.put(c);
        }
#else
        // But this causes an illegal system call (retval -31):
        os << lastFrame;
#endif

        // move to the next line and reset style
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
    ) << scenario

/// @brief Tests whether text is not visible. If it is, prints the current frame
/// to stdout
#define EXPECT_NOT_VISIBLE(scenario, text)                                     \
    gtest_lite::test.expect(                                                   \
        !scenario.isVisible(text),                                             \
        __FILE__,                                                              \
        __LINE__,                                                              \
        "EXPECT_VISIBLE(" #text ")"                                            \
    ) << scenario

int main() {
    GTINIT(std::cin);

    TEST(Scenario, Navigation) {
        // read test data from files
        Data data = Data("owners", "animals", "treatments");
        Scenario s(App::create(data));

        s << KEY_ENTER; // open owner
        EXPECT_VISIBLE(s, "Elérhetőség:");
        s << "jjjj" << KEY_ENTER; // select and open animal
        EXPECT_VISIBLE(s, "Faj:");
        s << "qq"; // go back to vaccinations
        EXPECT_NOT_VISIBLE(s, "Faj:");
        EXPECT_NOT_VISIBLE(s, "Elérhetőség:");
        s << KEY_TAB; // switch to OwnersPage
        EXPECT_VISIBLE(s, "+ Hozzáadás");
        s << "jj" << KEY_ENTER; // open owner
        EXPECT_VISIBLE(s, "Elérhetőség:");
        s << "q"; // go back to OwnersPage
        EXPECT_NOT_VISIBLE(s, "Elérhetőség:");
        s << KEY_TAB; // switch to AnimalsPage
        EXPECT_VISIBLE(s, "Keresés:");
        s << "j" << KEY_ENTER; // open animal
        EXPECT_VISIBLE(s, "Faj:");
        s << "jj" << KEY_ENTER; // open owner
        EXPECT_VISIBLE(s, "Elérhetőség:");
        s << "k" << KEY_ENTER; // open last animal
        EXPECT_VISIBLE(s, "Faj:");
        EXPECT_VISIBLE(s, "Oltások"); // tab titles are always visible
        s << "qqqq";                  // quit
        EXPECT_NOT_VISIBLE(s, "Oltások");
    }
    END TEST(Scenario, EditTreatmentDescription) {
        Data data = Data("owners", "animals", "treatments");
        Scenario s(App::create(data));

        // open first owner, go down to an animal, open, select a treatment
        s << KEY_ENTER << "jjjj" << KEY_ENTER << KEY_ENTER << "jjjj"
          << KEY_ENTER << "jjj";

        // edit treatment description then revert changes
        s << KEY_ENTER << "még valami";
        EXPECT_VISIBLE(s, "még valami");
        s << KEY_ESCAPE;
        EXPECT_NOT_VISIBLE(s, "még valami");

        // edit treatment description then save
        s << KEY_ENTER << "x" << KEY_BACKSPACE
          << KEY_BACKSPACE; // test backspace
        s << "inkább ez";
        EXPECT_VISIBLE(s, "inkább ez");
        EXPECT_NOT_VISIBLE(s, "x");
        s << KEY_ENTER;
        EXPECT_VISIBLE(s, "inkább ez");

        // close all pages
        s << "qqq";

        EXPECT_NOT_VISIBLE(s, "Tulajdonosok");
    }
    END TEST(Scenario, CreateAndPersist) {
        Data data = Data();
        Scenario s(App::create(data));

        // switch to OwnersPage, add an owner
        s << KEY_TAB << "j" << KEY_ENTER;
        EXPECT_VISIBLE(s, "Még nem lett állat felvéve");

        // fill out owner details
        s << KEY_ENTER << "Jon Arbuckle" << KEY_ENTER;
        EXPECT_VISIBLE(s, "Jon Arbuckle");
        s << "j" << KEY_ENTER << "Valahol" << KEY_ENTER;
        EXPECT_VISIBLE(s, "Valahol");
        s << "j" << KEY_ENTER << "john@example.com" << KEY_ENTER;
        EXPECT_VISIBLE(s, "john@example.com");

        // add an animal
        s << "j" << KEY_ENTER;
        EXPECT_VISIBLE(s, "Még nem lett kezelés felvéve");

        // fill out animal details
        s << KEY_ENTER << "Garfield" << KEY_ENTER << "j" << KEY_ENTER
          << "Macska" << KEY_ENTER;

        // add a treatment
        s << "j" << KEY_ENTER;
        EXPECT_NOT_VISIBLE(s, "Még nem lett kezelés felvéve");

        // fill out treatment details and mark vaccination
        s << "j" << KEY_ENTER << "Veszettség elleni oltás" << KEY_ENTER << ' ';
        EXPECT_VISIBLE(s, "Veszettség elleni oltás");
        EXPECT_VISIBLE(s, "💉");

        std::stringstream owners, animals, treatments;
        data.save(owners, animals, treatments);

        Data data2 = Data(owners, animals, treatments);
        Scenario s2(App::create(data2));

        s2 << KEY_ENTER;
        EXPECT_VISIBLE(s2, "Garfield");

        s2 << "jjjj" << KEY_ENTER;
        EXPECT_VISIBLE(s2, "Garfield");
        EXPECT_VISIBLE(s2, "Veszettség elleni oltás");
        EXPECT_VISIBLE(s2, "💉");
    }
    END TEST(Scenario, Search) {
        Data data = Data();
        Scenario s(App::create(data));
        Owner& owner = *data.owners.createNew();
        owner.name = "Jon Arbuckle";
        Animal& animal = *data.animals.createNew(owner);
        animal.name = "Garfield";

        s << KEY_TAB << KEY_ENTER << "Jo";
        EXPECT_VISIBLE(s, "Jo");
        EXPECT_VISIBLE(s, "n Arbuckle");
        s << "h";
        EXPECT_NOT_VISIBLE(s, "Arbuckle");
        EXPECT_VISIBLE(s, "Nincs találat");
        s << KEY_ESCAPE;
        EXPECT_VISIBLE(s, "Jon Arbuckle");

        s << KEY_TAB << KEY_ENTER << "Ga";
        EXPECT_VISIBLE(s, "Ga");
        EXPECT_VISIBLE(s, "rfield");
        s << "h";
        EXPECT_NOT_VISIBLE(s, "rfield");
        EXPECT_VISIBLE(s, "Nincs találat");
        s << KEY_ESCAPE;
        EXPECT_VISIBLE(s, "Garfield");
    }
    END TEST(Scenario, DeleteFirstAndLastItem) {
        // load sample data
        Data data = Data("owners", "animals", "treatments");
        Scenario s(App::create(data));
        std::vector<std::string> orderedNames(data.owners.size());
        std::transform(
            data.owners.begin(),
            data.owners.end(),
            orderedNames.begin(),
            [](auto& pair) { return pair.second->name; }
        );
        std::sort(orderedNames.begin(), orderedNames.end());

        s << KEY_TAB; // select owners page
        s << "G";     // select last owner
        EXPECT_VISIBLE(s, orderedNames[orderedNames.size() - 1].c_str());
        s << "D"; // delete
        EXPECT_NOT_VISIBLE(s, orderedNames[orderedNames.size() - 1].c_str());
        EXPECT_VISIBLE(s, orderedNames[orderedNames.size() - 2].c_str());
        s << "D"; // delete
        EXPECT_NOT_VISIBLE(s, orderedNames[orderedNames.size() - 2].c_str());
        s << "gjj"; // select first owner
        EXPECT_VISIBLE(s, orderedNames[0].c_str());
        s << "D"; // delete
        EXPECT_NOT_VISIBLE(s, orderedNames[0].c_str());
    }
    END TEST(Exceptions, ListRange) {
        std::string value;
        PropertyRange propertyRange("Title", value);
        EXPECT_FALSE(propertyRange.isInteractive());
        EXPECT_THROW(propertyRange.handleInput('a', 0), std::logic_error&);

        struct UnimplementedRange : ListRange {
            void draw(ICanvas&, size_t, size_t, size_t) const override {}

            bool isInteractive() const override { return true; }
        } unimplementedRange;

        EXPECT_TRUE(unimplementedRange.isInteractive());
        EXPECT_THROW(unimplementedRange.handleInput('a', 0), std::runtime_error&);
    }
    END TEST(Exceptions, View) {
        struct NonInteractiveView : View {
            void draw(ICanvas& canvas) override {}
        } view;

        EXPECT_THROW(view.handleInput('a'), std::runtime_error&);
    }
    END TEST(Exceptions, NonEmptyRepository) {
        Data data;
        data.owners.createNew();
        std::stringstream ss;
        EXPECT_THROW(data.owners.load(ss), std::runtime_error&);
    }
    END GTEND(std::cerr);
}
#endif