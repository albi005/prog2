// http://cs.bme.hu/algel/gyak24/mintazh_2024_feladatsor.pdf - 7. feladat

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> in{1, 4, 3, 2, 3, 4, 2};
    vector<int> best_sum(in.size(), 0);

    best_sum[0] = in[0];
    best_sum[1] = best_sum[0] * in[1];
    for (size_t i = 2; i < in.size(); i++) {
        int mul = best_sum[i - 2] + in[i - 1] * in[i];
        int nomul = best_sum[i - 1] + in[i];
        best_sum[i] = max(mul, nomul);
    }
    cout << best_sum[in.size() - 1] << "\n";
}
