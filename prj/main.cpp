#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    long n, m, k;
    cin >> n >> m >> k;

    vector<long> min_program;
    for (long i = 0; i < n; ++i) {
        long s;
        cin >> s;
        min_program.push_back(s);
    }

    vector<vector<long>> zalez;
    vector<long> ileKrawedzi;

    for(long i = 0; i < n; ++i) {
        ileKrawedzi.push_back(0);
        zalez.push_back(*new vector<long>);
    }
    for (long i = 0; i < m; ++i) {
        long a, b;
        cin >> a >> b;
        zalez[b - 1].push_back(a - 1);
        ileKrawedzi[a - 1]++;
    }

    priority_queue<std::pair<long, long>, std::vector<pair<long, long>>,
            std::greater<long>> kolejka;

    for (long i = 0; i < n; ++i) {
        if (ileKrawedzi[i] == 0) {
            pair<long, long> wierzch(min_program[i], i);
            kolejka.push(wierzch);
        }
    }

    long minN = 0;
    long counter = 0;

    while (!kolejka.empty() && counter < k) {
        auto min = kolejka.top();
        kolejka.pop();
        counter++;
        minN = max(min_program[min.second], minN);
        for (long v : zalez[min.second]) {
            if (--ileKrawedzi[v] == 0) {
                pair<long, long> w(min_program[v], v);
                kolejka.push(w);
            }
        }
    }

    cout << minN << endl;

    return 0;
}