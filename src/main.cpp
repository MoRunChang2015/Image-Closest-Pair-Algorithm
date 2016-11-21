#include <iostream>
#include <string>
#include "cmdline.h"
using namespace std;
int d, n;
string path;
cmdline::parser p;

void setCmdParser() {
    // -n command
    p.add<int>("number", 'n', "the number of images", true, 0);
    // -d command
    p.add<int>("dimensions", 'd', "the dimensions of images", true, 0);
    // -f command
    p.add<string>("file", 'f', "the path to dataset", true, "");
}

int main(int argc, char* argv[]) {
    setCmdParser();

    p.parse_check(argc, argv);

    n = p.get<int>("number");
    d = p.get<int>("dimensions");
    path = p.get<string>("file");

    cout << n << endl;
    cout << d << endl;
    cout << path << endl;

    return 0;
}
