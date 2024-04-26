#include <iostream>

using namespace std;

// ESC[y,xR
void aaa() {
    if (cin.peek() != '\e')
        return;
    cin.get();
    // if (cin.peek() != '')
}

int main() {
    cout << cin.get() << cin.get();
    cin.unget();
    cin.unget();
    cout << cin.get() << cin.get();
}
