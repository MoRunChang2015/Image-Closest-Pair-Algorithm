#include "closestPairInLine.hpp"
#include <iostream>
using namespace std;

int x, y;

extern vector<double> pos;

double getClosestPair() {
    // TODO:get closest in line;
}

std::pair<int, int> getClosestPairInLine(int flag) {
    x = y = 0;
    cout << pos.size() << endl;
    if (flag == MEDIAN_FLAG) {
        getClosestPair();
    } else if (flag == PIVOT_FLAG) {
        getClosestPair();
    }
    return make_pair(x, y);
}
