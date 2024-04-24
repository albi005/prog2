// Rust is just so much better
class View {
    View(const View&) = delete;
    void operator=(const View&) = delete;

  public:
    View() {}
    virtual ~View() {}
};
class ContentView : public View {};
void f(ContentView c) {}
void g(ContentView& c) {}

class OtherView {
  public:
    OtherView() {}
};
class OtherContentView : public OtherView {};
void h(OtherContentView c) {}
void i(OtherContentView& c) {}

int main() {
    {
        ContentView c;
        c = ContentView();
        ContentView a = c;
        f(c);
        g(c);
    }

    {
        OtherContentView c;
        c = OtherContentView();
        OtherContentView a = c;
        h(c);
        i(c);
    }
}
