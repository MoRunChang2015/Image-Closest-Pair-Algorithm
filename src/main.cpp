#include <cmath>
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

const int TRY_TIME = 100;

using namespace std;

int WIDTH = 28;
int HEIGHT = 28;

int d, n;
string path;
cmdline::parser p;
short **s;
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
    // -m command
    p.add("median", 'm', "using median as the pivot.");
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

const string ASSCII_CHAR = " .-+*?X%$#@";

char getCharByGray(int x) {
    double temp = static_cast<double>(x) / 255.0 *
                  static_cast<double>(ASSCII_CHAR.length());
    return ASSCII_CHAR[round(temp)];
}

void printImage(int x) {
    for (int i = 1; i <= HEIGHT; i++) {
        for (int j = 1; j <= WIDTH; j++)
            cout << getCharByGray(s[x][(i - 1) * 28 + j]);
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
        cout << "Get candidate closest pair <" << p.first << " , " << p.second
             << ">." << endl;
        if (temp < ans || ans < 0) {
            ans = temp;
            cpx = p.first;
            cpy = p.second;
        }
    }
}

void createBuffer() {
    s = new short *[n + 3];
    for (int i = 0; i < n + 3; i++) {
        s[i] = new short[d + 3];
        memset(s[i], 0, d + 3);
    }
}

void deleteBuffer() {
    for (int i = 0; i < n + 3; i++) {
        delete[] s[i];
    }
}

int main(int argc, char *argv[]) {
    setCmdParser();

    p.parse_check(argc, argv);
    // get arguments
    n = p.get<int>("number");
    d = p.get<int>("dimensions");
    path = p.get<string>("file");

    WIDTH = HEIGHT = sqrt(d);

    createBuffer();

    readDataset(n, d, path);
    cout << "finish read dataset from file" << endl;

    srand(time(NULL));
    ans = -1;
    // startTimer
    Timer timer;
    timer.startTimer();

    if (p.exist("median")) {
        cout << "using median as the pivot." << endl;
        findClosestPair(MEDIAN_FLAG);
    } else {
        cout << "pick a pivot randomly." << endl;
        findClosestPair(PIVOT_FLAG);
    }
    // findClosestPair(MEDIAN_FLAG);
    timer.stopTimer();

    cout << "Closest Pair is Image No." << cpx << " and Image No." << cpy
         << endl;
    cout << "Image No." << cpx << endl;
    printImage(cpx);
    cout << "Image No." << cpy << endl;
    printImage(cpy);
    timer.printTime();

    deleteBuffer();

    return 0;
}
