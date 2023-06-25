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

    const int KEY_SIZE = 16;
    unsigned char key[KEY_SIZE];
    // Fill the key with random values
    for(int i = 0; i < KEY_SIZE; ++i) {
         key[i] = distr(gen);
    }

    // Generate a random IV
    unsigned char iv[16];
    for(int i = 0; i < 16 ; ++i) {
         iv[i] = distr(gen);
    }

    // Read the content of SE_array.txt into plain vector
    std::ifstream inputFile("SE2_array.txt");
    std::vector<unsigned char> plain;
    int value;
    while(inputFile >> std::hex >> value){
        plain.push_back(value);
    }

    // AES works on block size of 16 bytes (128 bits)
    const int AES_BLOCK_SIZE = 16;
    size_t remainder = plain.size() % AES_BLOCK_SIZE;
    if (remainder != 0) {
        plain.resize(plain.size() + AES_BLOCK_SIZE - remainder, 0);  // adding zero padding
    }

    const size_t PLAIN_SIZE = plain.size();

    std::cout << "Key: ";
    for(int i = 0; i < KEY_SIZE; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(key[i]) << " ";
    }
    std::cout << std::endl;

    AES aes(AESKeyLength::AES_128);
    unsigned char* c = aes.EncryptCBC(plain.data(), PLAIN_SIZE, key, iv);
    unsigned char *innew = aes.DecryptCBC(c, PLAIN_SIZE, key, iv);

    if(memcmp(innew, plain.data(), PLAIN_SIZE) == 0) {
        std::cout << "Encryption was successful and the result matches the expected output." << std::endl;
    } else {
        std::cout << "Encryption failed or the result does not match the expected output." << std::endl;
    }

    delete[] c;
    delete[] innew;
    return 0;
}
