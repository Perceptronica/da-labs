#include <bits/stdc++.h>

using namespace std;
const uint32_t MAXN = 1e5 + 1;
array<bool, MAXN> visited;
vector<vector<uint32_t>> answer;
vector<vector<uint32_t>> g(MAXN, vector<uint32_t>(0)); 

void dfs(uint32_t v, int32_t c) {
    visited[v] = true;
    for (uint32_t u : g[v]) {
        if(!visited[u]) {
            dfs(u, c);
        }
    }
    answer[c].push_back(v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    uint32_t n, m;
    cin >> n >> m;
    uint32_t a, b;
    for (uint32_t i = 0; i < m; ++i) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int32_t num = -1;
    for (uint32_t v = 1; v <= n; ++v) {
        if (!visited[v]) {
            answer.push_back({});
            dfs(v, ++num);
        }
    }
    for (auto& v : answer) {
        sort(v.begin(), v.end());
        for (const auto& u: v) {
            cout << u << ' ';
        }
        cout << '\n';
    }
}