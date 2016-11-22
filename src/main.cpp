#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <limits>
#include "cmdline.h"
#include "closestPairInLine.hpp"
#define WIDTH 28
#define HEIGHT 28
using namespace std;
int d, n;
string path;
cmdline::parser p;
short s[60020][800] = {0};
double ans;
int cpx, cpy;

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
        for (j = 1; j <= d; j++)
            input >> s[i][j];
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
    const double twoPi = 2.0*3.14159265358979323846;
    double x, y, flag;
    do {
        x = rand() * (1.0 / RAND_MAX);
        y = rand() * (1.0 / RAND_MAX);
        flag = rand() * (1.0 / RAND_MAX);
    } while (x <= epsilon);
    if (flag > 0.5)
        return sqrt(-2.0 * log(x)) * cos(twoPi * y);
    else
        return sqrt(-2.0 * log(x)) * sin(twoPi * y);
}

void findClosestPair(int flag) {
    cpx = 1;
    cpy = 2;
}

int main(int argc, char* argv[]) {
    setCmdParser();

    p.parse_check(argc, argv);
    // get arguments
    n = p.get<int>("number");
    d = p.get<int>("dimensions");
    path = p.get<string>("file");

    readDataset(n, d, path);

    srand(time(NULL));
    findClosestPair(MEDIAN_FLAG);

    cout << "Closest Pair is Image No." << cpx << " and Image No." << cpy << endl;
    cout << "Image No." << cpx << endl;
    printImage(cpx);
    cout << "Image No." << cpy << endl;
    printImage(cpy);
    return 0;
}
