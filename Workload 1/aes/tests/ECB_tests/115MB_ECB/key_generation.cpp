#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
#include <vector>
#include "../../../src/AES.h"

using namespace std;

int main() {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 255); // define the range

    const int KEY_SIZE = 32;
    unsigned char key[KEY_SIZE];
    // Fill the key with random values
    for(int i = 0; i < KEY_SIZE; ++i) {
         key[i] = distr(gen);
    }

    // Write key to key.txt file
    std::ofstream outputFile("key.txt");
    for(int i = 0; i < KEY_SIZE; ++i) {
        outputFile << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(key[i]) << " ";
    }
    outputFile.close();

    std::cout << "Key saved to key.txt" << std::endl;
}
