class View {
  public:
    virtual void draw() = 0;
};

class ContentView : public View {
  public:
    virtual void draw() override {}
};

class AnimalsPage : public ContentView {};

int main() {
    auto a = new AnimalsPage();
    a->draw();
}
