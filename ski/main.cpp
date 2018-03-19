#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long n, m;
    cin >> n >> m;
    vector<vector<long>> sas(n, vector<long>());
    for (long i = 0; i < m; ++i) {
        long a, b;
        cin >> a >> b;
        sas.at(a - 1).push_back(b - 1);
        sas.at(b - 1).push_back(a - 1);
    }
    bool possible = true;
    vector<bool> visited(n, false);
    vector<int> in(n, 0);
    queue<long> q;
    for (long i = 0; i < n && possible; ++i) {
        if (in.at(i) == 0) {
            q.push(i);
            possible = true;
            while (!q.empty() && possible) {
                long node = q.front();
                q.pop();
                if (!visited.at(node)) {
                    visited.at(node) = true;
                    if (in.at(node) == 0) {
                        in.at(node) = -1;
                    }
                    int vec = in.at(node) * -1;
                    for (auto m : sas.at(node)) {
                        if (in.at(m) == 0) {
                            in.at(m) = vec;
                        } else if (in.at(m) != vec) {
                            possible = false;
                            break;
                        }
                        if (!visited.at(m)) q.push(m);
                    }
                }
            }
        }
    }
    cout << (possible ? "TAK" : "NIE");
    return 0;
}