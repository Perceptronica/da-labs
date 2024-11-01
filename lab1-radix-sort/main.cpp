#include <bits/stdc++.h>

using namespace std;

const int MD5 = 16;

struct Item {
    string key;
    uint64_t val;
};

int to_int(char c) {
    if (48 <= c && c <= 57) {
        return c - 48;
    } else if (97 <= c && c <= 102) {
        return c - 97 + 10;
    } else {
        return 0;
    }
}

void CountingSort(vector<Item>& A, vector<Item>& B, int pos) {
    vector<int> count(MD5, 0);
    for (size_t i = 0; i < A.size(); ++i) {
        ++count[to_int(A[i].key[pos])];
    }

    for (size_t i = 1; i < MD5; ++i) {
        count[i] += count[i - 1];
    }
    
    for (int i = static_cast<int>(A.size()) - 1; i >= 0; --i) {
        size_t p = count[to_int(A[i].key[pos])] - 1;
        B[p] = A[i];
        --count[to_int(A[i].key[pos])];
    }
    
}

void RadixSort(vector<Item>& A, vector<Item>& B) {
    int maxLength = 32;
    for (int i = maxLength - 1; i >= 0; i--) {
        CountingSort(A, B, i);
        A.swap(B);
    }
    if (maxLength % 2 == 0) {
        A.swap(B);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<Item> v;
    Item curr;

    while (cin >> curr.key >> curr.val) {
        v.push_back(curr);
    }

    vector<Item> result(v.size());

    RadixSort(v, result);

    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i].key << '\t' << result[i].val << '\n';
    }
    return 0;
}

