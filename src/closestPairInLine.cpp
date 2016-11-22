#include "closestPairInLine.hpp"
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
using namespace std;
#define INF 1e9

extern vector<double> pos;

double getPivotRandomly(int l, int r) {
    int index = rand() % (r - l) + l;
    return pos[index];
}

double getPivotMedian(int l, int r) {
    // TODO: get median from l to r
    return pos[l];
}

pair<double, pair<int, int>> minPair(pair<double, pair<int, int>> x,
                                     pair<double, pair<int, int>> y) {
    if (x.first > y.first)
        return y;
    else
        return x;
}

pair<double, pair<int, int>> getClosestPair(
    int l, int r, function<double(int, int)> getPivot) {
    if (l >= r) return make_pair(INF, make_pair(0, 0));
    if (r - l == 1) return make_pair(INF, make_pair(l, l + 1));
    if (r - l == 2) {
        if (pos[l] > pos[r]) {
            double temp = pos[l];
            pos[l] = pos[r];
            pos[r] = temp;
        }
        return make_pair(abs(pos[l] - pos[r]), make_pair(l, l + 1));
    }
    double p = getPivot(l, r);
    int i = l;
    int j = r - 1;
    double temp;
    while (i <= j) {
        while (pos[i] < p) i++;
        while (pos[j] > p) j--;
        if (i <= j) {
            temp = pos[i];
            pos[i] = pos[j];
            pos[j] = temp;
            i++;
            j--;
        }
    }
    auto left = getClosestPair(l, i, getPivot);
    auto right = getClosestPair(i, r, getPivot);
    pair<double, pair<int, int>> mid;
    if (i != l && i != r) {
        mid = make_pair(abs(pos[i] - pos[i - 1]), make_pair(i - 1, i));
    } else {
        mid = make_pair(INF, make_pair(0, 0));
    }
    return minPair(left, minPair(mid, right));
}

std::pair<int, int> getClosestPairInLine(int n, int flag) {
    int x, y;
    if (flag == MEDIAN_FLAG) {
        auto p = getClosestPair(0, n, getPivotMedian);
        x = p.second.first + 1;
        y = p.second.second + 1;
    } else if (flag == PIVOT_FLAG) {
        auto p = getClosestPair(0, n, getPivotRandomly);
        x = p.second.first + 1;
        y = p.second.second + 1;
    }
    return make_pair(x, y);
}
