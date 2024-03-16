#include <bits/stdc++.h>

using namespace std;
struct Item {
    string key;
    uint64_t value;
};

bool operator<(const Item& lhs, const Item& rhs) {
    return lhs.key < rhs.key;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<Item> v;
    Item curr;

    while (cin >> curr.key >> curr.value) {
        v.push_back(curr);
    }
    auto start = std::chrono::steady_clock::now();
    stable_sort(v.begin(), v.end());
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    /*
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i].key << '\t' << v[i].value << '\n';
    }
    */

    std::cout << "[CPP_SORT] Sorted in " << duration.count() << " microseconds." << std::endl;

    return 0;
}