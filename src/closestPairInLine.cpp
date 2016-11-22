#include "closestPairInLine.hpp"
using namespace std;

int x, y;


double getClosestPair() {
    // TODO:get closest in line;
}

std::pair<int, int> getClosestPairInLine(std::vector<int> v, int flag) {
    x = y = 0;
    if (flag == MEDIAN_FLAG) {
        getClosestPair();
    } else if (flag == PIVOT_FLAG) {
        getClosestPair();
    }
    return make_pair(x, y);
}
