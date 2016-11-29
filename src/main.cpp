#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>
#include "closestPairInLine.hpp"
#include "cmdline.h"
#include "timer.hpp"
#define WIDTH 28
#define HEIGHT 28
#define TRY_TIME 100
using namespace std;
int d, n;
string path;
cmdline::parser p;
short s[60020][800] = {0};
double ans;
int cpx, cpy;
vector<double> line;
vector<pair<double, int>> pos;

void setCmdParser() {
    // -n command
    p.add<int>("number", 'n', "the number of images", true, 0);
    // -d command
    p.add<int>("dimensions", 'd', "the dimensions of images", true, 0);
    // -f command
    p.add<string>("file", 'f', "the path to dataset", true, "");
}

void readDataset(int n, int d, string path) {
    ifstream input(path);
    if (!input.is_open()) {
        cout << "input file doesn't exist!" << endl;
        exit(0);
    }
    for (int w = 1; w <= n; w++) {
        int i, j;
        input >> i;
        for (j = 1; j <= d; j++) input >> s[i][j];
    }
}

void printImage(int x) {
    for (int i = 1; i <= HEIGHT; i++) {
        for (int j = 1; j <= WIDTH; j++)
            if (s[x][(i - 1) * 28 + j] == 0)
                cout << '*';
            else
                cout << ' ';
        cout << '\n';
    }
}

double getStandardNormalDistribution() {
    const double epsilon = numeric_limits<double>::min();
    const double twoPi = 2.0 * 3.14159265358979323846;
    double x, y, flag;
    do {
        x = rand() * (1.0 / RAND_MAX);
        y = rand() * (1.0 / RAND_MAX);
        flag = rand() * (1.0 / RAND_MAX);
    } while (x <= epsilon);
    if (flag > 0)
        return sqrt(-2.0 * log(x)) * cos(twoPi * y);
    else
        return sqrt(-2.0 * log(x)) * sin(twoPi * y);
}

void getRandomLine(int d) {
    line.clear();
    for (int i = 1; i <= d; i++) {
        line.push_back(getStandardNormalDistribution());
    }
}

double euclideanDistance(int x, int y, int d) {
    double ans = 0;
    for (int i = 1; i <= d; i++) {
        ans = ans + (s[x][i] - s[y][i]) * (s[x][i] - s[y][i]);
    }
    return ans;
}

void findClosestPair(int flag) {
    for (int k = 1; k <= TRY_TIME; k++) {
        cout << "Trying the " << k << "th times" << endl;
        getRandomLine(d);
        pos.clear();
        for (int i = 1; i <= n; i++) {
            double temp = 0;
            for (int j = 1; j <= d; j++) temp = temp + s[i][j] * line[j - 1];
            pos.push_back(make_pair(temp, i));
        }
        pair<int, int> p = getClosestPairInLine(n, flag);
        double temp = euclideanDistance(p.first, p.second, d);
        cout << "Get candidate closest pair <" << p.first <<  " , "  << p.second << ">." << endl;
        if (temp < ans || ans < 0) {
            ans = temp;
            cpx = p.first;
            cpy = p.second;
        }
    }
}

int main(int argc, char* argv[]) {
    setCmdParser();

    p.parse_check(argc, argv);
    // get arguments
    n = p.get<int>("number");
    d = p.get<int>("dimensions");
    path = p.get<string>("file");

    readDataset(n, d, path);
    cout << "finish read dataset from file" << endl;

    srand(time(NULL));
    ans = -1;
    // startTimer
    Timer timer;
    timer.startTimer();
    findClosestPair(PIVOT_FLAG);
    //findClosestPair(MEDIAN_FLAG);
    timer.stopTimer();

    cout << "Closest Pair is Image No." << cpx << " and Image No." << cpy
         << endl;
    cout << "Image No." << cpx << endl;
    printImage(cpx);
    cout << "Image No." << cpy << endl;
    printImage(cpy);
    timer.printTime();
    return 0;
}
