#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long n, l;
    cin >> n >> l;
    vector<vector<long>> nas;
    vector<pair<long, long>> pairs;

    for (long i = 0; i < n; ++i) {
        nas.emplace_back(vector<long>());
        for (long j = 0; j < l; ++j) {
            long tmp;
            cin >> tmp;
            nas[i].push_back(tmp);
        }
    }

    for (long i = 0; i < n; ++i) {
        for (long j = 0; j < l; ++j) {
            pairs.emplace_back(make_pair(nas[i][j], j));
        }
    }

    long max = 1;
    long len = 1;
    sort(pairs.begin(), pairs.end());

    long curr = pairs[0].first;
    for (long i = 1; i < n * l; ++i) {
        if (pairs[i].first == curr && pairs[i].second == pairs[i - 1].second + 1) {
            ++len;
        } else if (pairs[i].first == curr && pairs[i].second == pairs[i - 1].second) {

        } else if (pairs[i].first == curr) {
            max = max > len ? max : len;
            len = 1;
        } else {
            curr = pairs[i].first;
            max = max > len ? max : len;
            len = 1;
        }
    }
    max = max > len ? max : len;

    cout << max;

    return 0;
}