#include <iterator>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

class Serializable {
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;
};

class Entity : Serializable {};

typedef uint32_t Color;
struct Point {
    int x, y;
};
struct Rect {
    int x, y, w, h;
};
class Canvas {
  protected:
    int width, height;

  public:
    virtual void
        drawText(const std::string& text, Point pos, Color fg, Color bg);
    virtual Point getSize() const { return Point{width, height}; }
};
class View {
    void operator=(const Canvas&) {} // disable assignment

  public:
    virtual void draw(const Canvas&) const = 0;
    virtual bool handleInput(char input);
    virtual ~View() {}
};
class ContentView : public View {
  protected:
    View* content;
    ContentView(View* content) : content(content) {}

  public:
    ~ContentView() { delete content; }
};
class PaddedCanvas : public Canvas {
    int l, t, r, b;
    virtual void
        drawText(const std::string& text, Point pos, Color fg, Color bg) {
        Canvas::drawText(text, Point{pos.x + l, pos.y + t}, fg, bg);
    }
    virtual Point getSize() const {
        return Point{width - l - r, height - t - b};
    }
};
class Padding : public ContentView {
    virtual void draw(const Canvas&) const;

  public:
    Padding(View* content) : ContentView(content) {}
};
class App : public View {
    void draw(const Canvas&);
};

struct Owner;
struct Animal;
struct Treatment;

struct Treatment {
    size_t id;
    size_t index; // Index in the main Treatments array
    Animal& animal;
    time_t date;
    bool was_rabies_vaccinated;

    std::string description;
};

struct Owner {
    size_t id;
    size_t index; // Index in the main Owners array
    std::string name;
    std::string address;
    std::string contact;
    std::vector<Animal> animals;
};

struct Animal {
    size_t id;
    size_t index; // Index in the main Animals array
    Owner& owner;
    std::vector<Treatment> treatments;
    std::string name;
    std::string species;
};

template <typename T> class Repository {
  protected:
    std::vector<T*> entities;

  public:
    virtual void load(const std::string& fileName);
    virtual void save();
    T& getById(size_t id);
    ~Repository() { save(); }
};

class OwnerRepository : Repository<Owner> {
};

struct AppData {
    std::vector<Owner> owners;
    std::vector<Animal> animals;
    std::vector<Treatment> treatments;
};

int main() {}
