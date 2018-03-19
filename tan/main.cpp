#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
#include <cassert>
using namespace std;

struct City {
    long idx;
    long long price;
    int left_coupons;
    City(long idx, long long price, int lc) : idx(idx), price(price), left_coupons(lc) {};
};

class Compare {
public:
    bool operator() (City first, City sec)
    {
        return first.price > sec.price;
    }
};

int main() {
    long n, bon;
    long con;
    cin >> n >> con >> bon;
    vector<vector<tuple<long, long, bool>>> connections
            (n, vector<tuple<long, long, bool>>());

    for (long i = 0; i < con; ++i) {
        long start, finish;
        long discount, price;
        cin >> start >> finish >> discount >> price;
        tuple<long, long, bool> s1, s2, f1, f2;
        s1 = make_tuple(finish, price, false);
        s2 = make_tuple(finish, price - discount, true);
        connections.at(start).push_back(s1);
        connections.at(start).push_back(s2);
    }

    priority_queue<City, vector<City>, Compare> Q;

    vector<vector<long long>> cities (n, vector<long long>());
    for (auto &c : cities) {
        for (int i = 0; i <= bon; ++i) {
            c.push_back(-1);
        }
    }

    City *home = new City(0, 0, bon);
    Q.push(*home);
    while (!Q.empty()) {
        City c = Q.top();
        Q.pop();
        if (cities.at(c.idx).at(c.left_coupons) == -1 ||
                cities.at(c.idx).at(c.left_coupons) > c.price) {
            cities.at(c.idx).at(c.left_coupons) = c.price;

            for (auto neigh : connections.at(c.idx)) {
                long long new_price = c.price + get<1>(neigh);
                int left_coupons = c.left_coupons - get<2>(neigh);
                if (left_coupons >= 0) {
                    Q.push(City(get<0>(neigh), new_price, left_coupons));
                }
            }
        }
    }

    long long minval = -1;
    for (auto c : cities.at(n - 1)) {
        if (minval == -1 || c < minval) {
            minval = c;
        }
    }
    cout << minval;


    return 0;
}