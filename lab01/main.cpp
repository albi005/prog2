#include <iostream>
#include "fuggvenyeim.h"
#include <iomanip>

using namespace std;

int main() {
    double an[] = { 3, 2, 1 }; // együtthatók: a0=3, a1=2, a3=1      
    double res[] = { 3, 6, 11, 18, 27, 38, 51 };
    int hibak = 0;
    for (int i = 0; i < 7; i++) {
        const double Z = 3.141e2;
        double x = i / Z - 1;
        x++;
        x = x * Z;
        double fx = polinom(x, an, 2);
        if (!almostEQ(res[i], fx)) {    // Helyes ez így? 
           cout << "Hibas: " << setprecision(20) << res[i] << "!=" << fx << endl;
           hibak++;
        }
    }
    if (hibak == 0)
        cout << "Nem volt elteres" << endl;
}

