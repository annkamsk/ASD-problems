#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long n, m;
    cin >> n >> m;
    vector<long> taken;
    for (long i = 0; i < n; ++i) {
        long tmp;
        cin >> tmp;
        taken.push_back(tmp);
    }

    vector<vector<long>> sas(n, vector<long>());
    for (long i = 0; i < m; ++i) {
        long a, b;
        cin >> a >> b;
        if (!taken[a - 1]) sas.at(a - 1).push_back(b - 1);
        if (!taken[b - 1]) sas.at(b - 1).push_back(a - 1);
    }
    stack<long> s;
    s.push(0);
    vector<long> good;
    vector<bool> vis(n, false);

    while (!s.empty()) {
        long node = s.top();
        s.pop();
        if (!vis[node]) {
            vis[node] = true;
            good.push_back(node);
            if (!sas[node].empty()) {
                for (auto n : sas[node]) {
                    if (!vis[n]) {
                        s.push(n);
                    }
                }
            }
        }
    }
    sort(good.begin(), good.end());
    for (auto k : good) {
        if (taken[k]) cout <<k+1 <<endl;
    }

    return 0;
}