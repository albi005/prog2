// Rust is just so much better
class View {
    View(const View&) = delete;
    void operator=(const View&) = delete;

  public:
    View() {}
    virtual ~View() {}
};

class ContentView : public View {
};

void f(ContentView c) {}
void g(ContentView& c) {}

int main() {
    ContentView c;
    c = ContentView();
    ContentView a = c;
    f(c);
    g(c);
}

