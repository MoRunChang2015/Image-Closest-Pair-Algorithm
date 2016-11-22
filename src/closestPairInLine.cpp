#include "closestPairInLine.hpp"
#include <iostream>
using namespace std;

int x, y;

vector<double> a;

double getClosestPair() {
    // TODO:get closest in line;
}

std::pair<int, int> getClosestPairInLine(std::vector<double> v, int flag) {
    x = y = 0;
    a = move(v);
    cout << a.size() << endl;
    if (flag == MEDIAN_FLAG) {
        getClosestPair();
    } else if (flag == PIVOT_FLAG) {
        getClosestPair();
    }
    return make_pair(x, y);
}
