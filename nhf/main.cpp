#include <cstddef>
#include <cstdint>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

///////////
// MODEL //
///////////
struct Owner;
struct Animal;
struct Treatment;

class Serializable {
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;
};

class Entity : Serializable {
  public:
    size_t id;
    size_t index; // Index in the repository
};

struct Owner {
    std::string name;
    std::string address;
    std::string contact;
    std::vector<Animal> animals;
};

struct Animal {
    Owner* owner;
    std::vector<Treatment> treatments;
    std::string name;
    std::string species;
};

struct Treatment {
    Animal* animal;
    time_t date;
    bool was_rabies_vaccinated;
    std::string description;
};

template <typename TEntity> class Repository {
  protected:
    std::vector<TEntity*> entities;

  public:
    virtual void load(const std::string& fileName);
    virtual void save();
    TEntity& getById(size_t id);
    ~Repository() { save(); }
};

class OwnerRepository : public Repository<Owner> {};
class AnimalRepository : public Repository<Animal> {};
class TreatmentRepository : public Repository<Treatment> {};

struct AppData {
    OwnerRepository owners;
    AnimalRepository animals;
    TreatmentRepository treatments;

    AppData() {}

  public:
    static AppData create() { return AppData(); }
};

//////////
// VIEW //
//////////
typedef uint32_t Color;
struct Size;
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    Point(const Size& size);
};
struct Size {
    int w, h;
    Size(int w, int h) : w(w), h(h) {}
    Size(const Point& point) : w(point.x), h(point.y) {}
};
inline Point::Point(const Size& size) : x(size.w), y(size.h) {}
struct Rect {
    int x, y, w, h;
};

class ICanvas {
  public:
    virtual Size getSize() const = 0;
    virtual void drawText(const std::string& text, Color fg, Color bg) = 0;
    virtual void
        drawText(const std::string& text, Point pos, Color fg, Color bg) = 0;
};

class OstreamCanvas : public ICanvas {
  protected:
    int width, height;

  public:
    bool handleEscapeCode(std::istream&);
    virtual Size getSize() const { return Size(width, height); }
    virtual void drawText(const std::string& text, Color fg, Color bg);
    virtual void
        drawText(const std::string& text, Point pos, Color fg, Color bg);
};

class View {
    View(const View&) {}              // disable copy
    void operator=(const ICanvas&) {} // disable assignment

  protected:
    bool isFocused = false;

  public:
    View() {}
    virtual void draw(const ICanvas&) const = 0;
    virtual bool handleInput(char input);
    virtual void setIsFocused(bool value) { isFocused = value; }
    virtual ~View() {}
};

class ContentView : public View {
  protected:
    View* content;
    ContentView(View* content) : content(content) {}

  public:
    ~ContentView() { delete content; }
};

class PaddedCanvas : public ICanvas {
    int l, t, r, b;
    ICanvas& inner;
    virtual void
        drawText(const std::string& text, Point pos, Color fg, Color bg) {
        ICanvas::drawText(text, Point(pos.x + l, pos.y + t), fg, bg);
    }
    virtual Size getSize() const {
        Size orig = inner.getSize();
        return Size(orig.w - l - r, orig.h - t - b);
    }

  public:
    PaddedCanvas(int l, int t, int r, int b, ICanvas& inner)
        : l(l), t(t), r(r), b(b), inner(inner) {}
    PaddedCanvas(int x, int y, ICanvas& inner)
        : PaddedCanvas(x, y, x, y, inner) {}
};

class Padding : public ContentView {
    virtual void draw(const ICanvas&) const;

  public:
    Padding(View* content) : ContentView(content) {}
};

class ListView : public View {
    size_t selectedItemIndex;

  protected:
    virtual void getItemCount() const = 0;
    virtual void drawItems(
        ICanvas* canvas,
        size_t firstVisibleItemIndex,
        size_t lastVisibleItemIndex
    ) const = 0;
};

class VaxTab : public View {
    ListView* listView;
    VaxTab(OwnerRepository*);
};
class OwnersTab : public View {
    OwnersTab(OwnerRepository*);
};
class AnimalsTab : public View {
    AnimalsTab(AnimalRepository*);
};

class App : public View {
    void draw(const ICanvas&);
    App(AppData* data);
};

int main() {}
