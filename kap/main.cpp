#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

struct Punkt {
    long idx;
    long long x;
    long long y;
    long long d;
    Punkt(long idx, long long x, long long y, long long d) :
            idx(idx), x(x), y(y), d(d) {}
};

class Compare {
public:
    bool operator() (Punkt first, Punkt sec)
    {
        return first.d > sec.d;
    }
};

bool compareX(Punkt a, Punkt b) {
    return a.x < b.x;
}

bool compareY(Punkt a, Punkt b) {
    return a.y < b.y;
}

bool compareNr(Punkt a, Punkt b) { return a.idx < b.idx; }

void make_graph(vector<Punkt> &punkty, vector<vector<Punkt>> &sas,
                int n, bool compare(Punkt a, Punkt b)) {
    sort(punkty.begin(), punkty.end(), compare);
    Punkt &north = punkty.at(1);
    sas.at(punkty.at(0).idx).push_back(north);
    Punkt &south = punkty.at(n - 2);
    sas.at(punkty.at(n - 1).idx).push_back(south);

    for (long i = 1; i < n - 1; ++i) {
        Punkt &south = punkty.at(i - 1);
        sas.at(punkty.at(i).idx).emplace_back(south);
        Punkt &north = punkty.at(i + 1);
        sas.at(punkty.at(i).idx).emplace_back(north);
    }
}
int main() {
    long n;
    cin >> n;
    vector<Punkt> punkty;
    for (long i = 0; i < n; ++i) {
        long long x, y;
        cin >> x >> y;
        punkty.push_back(Punkt(i, x, y, LLONG_MAX));
    }
    vector<vector<Punkt>> sas(n, vector<Punkt>());
    Punkt &start = punkty.at(0);
    Punkt &finish = punkty.at(n - 1);

    make_graph(punkty, sas, n, compareX);
    make_graph(punkty, sas, n, compareY);

    sort(punkty.begin(), punkty.end(), compareNr);
    punkty.at(0).d = 0;

    priority_queue<Punkt, vector<Punkt>, Compare> Q;
    Q.push(start);

    while (!Q.empty()) {
        Punkt p = Q.top();
        Q.pop();

        for (int i = 0; i < sas.at(p.idx).size(); ++i) {
            Punkt &s = punkty.at(sas.at(p.idx).at(i).idx);
             long long odl_x = abs(p.x - s.x);
             long long odl_y = abs(p.y - s.y);
             long long odl = min(odl_x, odl_y);
             if (s.d > p.d + odl) {
                 s.d = p.d + odl;
                 Q.push(s);
             }
        }
    }

    cout << punkty.at(n - 1).d <<endl;

    return 0;
}