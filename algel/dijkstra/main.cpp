#include <bits/stdc++.h>

using namespace std;

bool is_inf(int x) { return x >= 69; }

int main() {
    const int N = 4;
    const int s = 0;
    vector<vector<int>> C;
    C.push_back({0, 2, 3, 69});
    C.push_back({2, 0, 3, 5});
    C.push_back({3, 3, 0, 4});
    C.push_back({69, 5, 4, 0});

    vector<bool> KESZ(N, false);
    KESZ[s] = true;

    vector<int> D(N);
    for (size_t i = 0; i < N; i++)
        D[i] = C[s][i];

    while (true) {
        int x = -1, min1 = 69;
        for (size_t i = 0; i < N; i++) {
            if (D[i] < min1) {
                min1 = D[i];
                x = i;
            }
        }
        if (x == -1)
            break;

        for (size_t w = 0; w < N; w++) {
            if (KESZ[w])
                continue;
            if (is_inf(C[x][w]))
                continue;

            D[w] = min(D[w], D[x] + C[x][w]);
        }
    }
}
