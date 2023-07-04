#include <iostream>
#include <vector>
#include "../src/AES.h"
#include <iostream>
#include <iomanip>
#include <random>
using namespace std;

const unsigned int BLOCK_BYTES_LENGTH = 16 * sizeof(unsigned char);


int main() {
  /*AES aes(AESKeyLength::AES_128);
  unsigned char plain[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                           0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
  unsigned char key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                         0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
  unsigned char right[] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
                           0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};
  unsigned char *out = aes.EncryptECB(plain, BLOCK_BYTES_LENGTH, key);

  if(memcmp(right, out, BLOCK_BYTES_LENGTH) == 0) {
    std::cout << "Encryption was successful and the result matches the expected output." << std::endl;
  } else {
    std::cout << "Encryption failed or the result does not match the expected output." << std::endl;
  }

  delete[] out;

  return 0;*/
    std::random_device rd;  // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 255); // define the range

    unsigned char plain[16];
    unsigned char key[16];
    //unsigned char right[16];
    //unsigned int plainLen = sizeof(plain);
    const unsigned int BLOCK_BYTES_LENGTH = 16 * sizeof(unsigned char);

    //unsigned char plain[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    //                       0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    //unsigned char key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    //                     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    //unsigned char right[] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
    //                       0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};

    // fill plain[] and key[] with random values
    for(int i = 0; i < 16; ++i) {
        plain[i] = distr(gen);
        key[i] = distr(gen);
    }

    // print plain[] and key[] in hexadecimal
    std::cout << "Plaintext: ";
    for(int i = 0; i < 16; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(plain[i]) << " ";
    }
    std::cout << std::endl;

    std::cout << "Key: ";
    for(int i = 0; i < 16; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(key[i]) << " ";
    }
    std::cout << std::endl;

    AES aes(AESKeyLength::AES_128);
    unsigned char* c = aes.EncryptECB(plain, BLOCK_BYTES_LENGTH, key);

    /*if(memcmp(right, c, BLOCK_BYTES_LENGTH) == 0) {
        std::cout << "Encryption was successful and the result matches the expected output." << std::endl;
    } else {
        std::cout << "Encryption failed or the result does not match the expected output." << std::endl;
    }*/


    std::cout << "Ciphertext: ";
    for(size_t i = 0; i < BLOCK_BYTES_LENGTH; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c[i]) << " ";
    }
    std::cout << std::endl;

    delete[] c;

    return 0;
}

