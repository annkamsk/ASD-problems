#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <unordered_map>
#include <map>
#include <list>
using namespace std;

const bool RED = false;
const bool GREEN = true;


struct Edge {
    long from;
    long to;
    int path;
    int col;
};

int main() {
    long n, m;
    scanf("%ld%ld", &n, &m);
    vector<list<pair<long, int>>> visited(n, list<pair<long, int>>());

    for (long i = 0; i < m; ++i) {
        long a, b;
        int c;
        scanf("%ld%ld%d", &a, &b, &c);
        visited[a - 1].push_back(make_pair(b - 1, c));
        visited[b - 1].push_back(make_pair(a - 1, c));
    }

    long howmany[n];
    for (long i = 0; i < n; ++i) {
        howmany[i] = -1;
    }
    queue<Edge> q;
    q.push(Edge{0, 0, 0, 0});
    while (!q.empty()) {
        Edge node = q.front();
        q.pop();

        if (node.path < howmany[node.to] || howmany[node.to] == -1) {
            howmany[node.to] = node.path;
        }

        auto itend = visited.at(node.to).end();
        for (auto it = visited.at(node.to).begin(); it != itend;) {
            if (it->second != node.col || node.to == 0) {
                q.push(Edge{node.to, it->first, node.path + 1, it->second});
                if (++it == itend) {
                    visited.at(node.to).erase(--it);
                    break;
                } else {
                    --it;
                    if (it == visited.at(node.to).begin()) {
                        auto tmp = ++it;
                        visited.at(node.to).erase(--it);
                        it = tmp;
                    } else {
                        auto tmp = ++it;
                        visited.at(node.to).erase(--it);
                        it = tmp;
                    }
                }
            } else {
                ++it;
            }
        }

    }
    bool first = true;
    for (auto h : howmany) {
        if (first) {
            first = false;
        } else {
            printf("%ld\n", h);
        }
    }

    return 0;
}