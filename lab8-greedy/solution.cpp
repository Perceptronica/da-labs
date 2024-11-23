#include <bits/stdc++.h>

using namespace std;

using vd = vector<double>;
using vi = vector<int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<vd> v(m, vd(n + 2, 0));
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n + 1; ++j) {
            cin >> v[i][j];
        }
        v[i][n + 1] = i + 1;
    }

    vi min_v;
    for (size_t i = 0; i < n; ++i) {
        int min_cost = INT32_MAX;
        int row = INT32_MIN;
        for (size_t j = i; j < m; ++j) {
            if (v[j][i] != 0 && v[j][n] < min_cost) {
                min_cost = static_cast<int>(v[j][n]);
                row = j;
            }
        }
        if (row == INT32_MIN) { 
            cout << "-1\n"; 
            return 0; 
        }
        swap(v[i], v[row]);
        min_v.push_back(v[i][n + 1]);
        for (size_t j = i + 1; j < m; ++j) {
            double pivot = v[j][i] / v[i][i];
            for (size_t p = 1; p < n; ++p) {
                v[j][p] -= v[i][p] * pivot;
            }
        }
    }
    sort(min_v.begin(), min_v.end());
    for (const auto& elem : min_v) {
        cout << elem << " ";
    }
    cout << "\n";
}