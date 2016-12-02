#include "closestPairInLine.hpp"
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
using namespace std;
const double INF = 1e9;

extern vector<pair<double, int>> pos;

double getPivotRandomly(int l, int r) {
    int index = rand() % (r - l) + l;
    return pos[index].first;
}

double getMedian(int l, int r, int k) {
    if (l >= r) return pos[l].first;
    double mid = pos[(l + r) / 2].first;
    int i = l, j = r;
    while (i < j) {
        while (pos[i].first < mid) i++;
        while (pos[j].first > mid) j--;
        if (i <= j) {
            auto temp = pos[i];
            pos[i] = pos[j];
            pos[j] = temp;
            i++;
            j--;
        }
    }
    if (i - l >= k && j - l + 1 < k)
        return mid;
    else if (j - l + 1 < k)
        return getMedian(i, r, k - (i - 1));
    else
        return getMedian(l, j + 1, k);
}

double getPivotMedian(int l, int r) {
    return getMedian(l, r - 1, (r - l + 1) / 2);
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
        if (pos[l].first > pos[r].first) {
            auto temp = pos[l];
            pos[l] = pos[r];
            pos[r] = temp;
        }
        return make_pair(abs(pos[l].first - pos[l + 1].first),
                         make_pair(pos[l].second, pos[l + 1].second));
    }
    double p = getPivot(l, r);
    int i = l;
    int j = r - 1;
    while (i <= j) {
        while (pos[i].first < p) i++;
        while (pos[j].first > p) j--;
        if (i <= j) {
            auto temp = pos[i];
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
        mid = make_pair(abs(pos[i].first - pos[i - 1].first),
                        make_pair(pos[i - 1].second, pos[i].second));
    } else {
        mid = make_pair(INF, make_pair(0, 0));
    }
    return minPair(left, minPair(mid, right));
}

std::pair<int, int> getClosestPairInLine(int n, int flag) {
    int x, y;
    if (flag == MEDIAN_FLAG) {
        auto p = getClosestPair(0, n, getPivotMedian);
        x = p.second.first;
        y = p.second.second;
    } else if (flag == PIVOT_FLAG) {
        auto p = getClosestPair(0, n, getPivotRandomly);
        x = p.second.first;
        y = p.second.second;
    }
    return make_pair(x, y);
}
