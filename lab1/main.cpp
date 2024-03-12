#include <bits/stdc++.h>

using namespace std;

using Item = pair<string, uint64_t>;
// основание системы 
const int RADIX = 16;

int to_int(char c) {
    if (48 <= c && c <= 57) {
        return c - 48;
    } else if (97 <= c && c <= 102) {
        return c - 97 + 10;
    }
    return 0;
}

void CountingSort(vector<Item>& data, int i) {
    vector<Item> aux(data.size());
    vector<int> count(RADIX, 0);
    
    for (Item& it : data) {
        string t = it.first;
        int digit = i < t.length() ? to_int(t[i]) : 0;
        count[digit]++;
    }

    for (size_t j = 1; j < RADIX; ++j) {
        count[j] += count[j - 1];
    }

    for (size_t j = data.size() - 1; j >= 0; --j) {
        string t = data[j].first;
        int digit = i < t.length() ? to_int(t[i]) : 0;
        aux[count[digit] - 1] = data[j];
        count[digit]--;
    }
    data = aux;
}

void RadixSort(vector<Item>& data) {
    int maxLength = 32;
    for (int i = maxLength - 1; i >= 0; --i) {
        CountingSort(data, i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<Item> v;
    Item curr;
    while (cin >> curr.first >> curr.second) {
        v.push_back(curr);
    }
    RadixSort(v);
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i].first << '\t' << v[i].second << '\n';
    }
}