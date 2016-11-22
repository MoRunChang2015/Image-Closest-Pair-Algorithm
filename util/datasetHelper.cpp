#include <endian.h>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
const string DATASET_PATH = "data/train-images.idx3-ubyte";
const string OUTPUT_FILE = "data/Mnist.ds";
const string OUTPUT_PATH = "data/images/";

int main() {
    uint32_t number;
    uint8_t pixel;
    int n, width, height;
    ifstream dataset(DATASET_PATH, ios::binary);
    ofstream Mnist(OUTPUT_FILE);
    if (dataset.is_open() && Mnist.is_open()) {
        dataset.read((char*)&number, sizeof(uint32_t));
        cout << "Magic number is " << be32toh(number) << " ." << endl; // magic number 2051

        dataset.read((char*)&number, sizeof(uint32_t));
        n = be32toh(number);
        cout << "There are " << n << " images." << endl; // the number of images

        dataset.read((char*)&number, sizeof(uint32_t));
        height = be32toh(number);
        cout << "Height is " << height << " pixels." << endl;

        dataset.read((char*)&number, sizeof(uint32_t));
        width = be32toh(number);
        cout << "Width is " << width << " pixels." << endl;

        for (int w = 1; w <= n; w++) {
            stringstream ss;
            ss << w;
            ofstream output(OUTPUT_PATH + ss.str() + ".txt");
            if (!output.is_open()) {
                cout << "Can't open output file!" << endl;
                return 0;
            }
            Mnist << w;
            for (int i = 1; i <= height; i++) {
                for (int j = 1; j <= width; j++) {
                    dataset.read((char*)&pixel, sizeof(pixel));
                    uint8_t t = 1;
                    int ans = 0;
                    for (int k = 1; k <= 8; k++) {
                        if ((pixel & t) == 1) ans = ans + 1;
                        ans == ans << 1;
                        t = t << 1;
                    }
                    if (ans == 1) {
                        cout << "#";
                        output << 1;
                        Mnist << " " << 1;
                    } else {
                        cout << " ";
                        output << 0;
                        Mnist << " " << 0;
                    }
                }
                cout << endl;
                output << "\n";
                Mnist << "\n";
            }
            output.close();
        }
        dataset.close();
        Mnist.close();
    } else {
        cout << "Dataset doesn't exist!" << endl;
    }
    return 0;
}
