#include "AES.h"
#include <thread>
#include <pthread.h>
#include <sched.h>
#include <algorithm>

AES::AES(const AESKeyLength keyLength) {
  switch (keyLength) {
    case AESKeyLength::AES_128:
      this->Nk = 4;
      this->Nr = 10;
      break;
    case AESKeyLength::AES_192:
      this->Nk = 6;
      this->Nr = 12;
      break;
    case AESKeyLength::AES_256:
      this->Nk = 8;
      this->Nr = 14;
      break;
  }
}

unsigned char *AES::EncryptECB(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[]) {
  CheckLength(inLen);
  unsigned char *out = new unsigned char[inLen];
  unsigned char *roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
  KeyExpansion(key, roundKeys);

  unsigned int num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads(num_threads);

  unsigned int blocks_per_thread = inLen / (blockBytesLen * num_threads);

  for (unsigned int i = 0; i < num_threads; i++) {
    threads[i] = std::thread([=, &in, &out, &roundKeys]() {
      // Pin the thread to a specific CPU core
      cpu_set_t cpuset;
      CPU_ZERO(&cpuset);
      CPU_SET(i, &cpuset);
      pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);

      for (unsigned int j = 0; j < blocks_per_thread; j++) {
        unsigned int index = (j * num_threads + i) * blockBytesLen;
        EncryptBlock(in + index, out + index, roundKeys);
      }
    });
  }

  for (auto &thread : threads) {
    thread.join();
  }

  // Handle the remaining blocks if inLen is not a multiple of blockBytesLen * num_threads
  for (unsigned int i = blocks_per_thread * num_threads * blockBytesLen; i < inLen; i += blockBytesLen) {
    EncryptBlock(in + i, out + i, roundKeys);
  }

  delete[] roundKeys;
  return out;
}

unsigned char *AES::DecryptECB(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[]) {
  CheckLength(inLen);
  unsigned char *out = new unsigned char[inLen];
  unsigned char *roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
  KeyExpansion(key, roundKeys);

  unsigned int num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads(num_threads);

  unsigned int blocks_per_thread = inLen / (blockBytesLen * num_threads);

  for (unsigned int i = 0; i < num_threads; i++) {
    threads[i] = std::thread([=, &in, &out, &roundKeys]() {
      // Pin the thread to a specific CPU core
      cpu_set_t cpuset;
      CPU_ZERO(&cpuset);
      CPU_SET(i, &cpuset);
      pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);

      for (unsigned int j = 0; j < blocks_per_thread; j++) {
        unsigned int index = (j * num_threads + i) * blockBytesLen;
        DecryptBlock(in + index, out + index, roundKeys);
      }
    });
  }

  for (auto &thread : threads) {
    thread.join();
  }

  // Handle the remaining blocks if inLen is not a multiple of blockBytesLen * num_threads
  for (unsigned int i = blocks_per_thread * num_threads * blockBytesLen; i < inLen; i += blockBytesLen) {
    DecryptBlock(in + i, out + i, roundKeys);
  }

  delete[] roundKeys;
  return out;
}

unsigned char *AES::EncryptCBC(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[],
                               const unsigned char *iv) {
  CheckLength(inLen);
  unsigned char *out = new unsigned char[inLen];
  unsigned char block[blockBytesLen];
  unsigned char *roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
  KeyExpansion(key, roundKeys);
  memcpy(block, iv, blockBytesLen);
  for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
    XorBlocks(block, in + i, block, blockBytesLen);
    EncryptBlock(block, out + i, roundKeys);
    memcpy(block, out + i, blockBytesLen);
  }

  delete[] roundKeys;

  return out;
}

unsigned char *AES::DecryptCBC(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[],
                               const unsigned char *iv) {
  CheckLength(inLen);
  unsigned char *out = new unsigned char[inLen];
  unsigned char block[blockBytesLen];
  unsigned char *roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
  KeyExpansion(key, roundKeys);
  memcpy(block, iv, blockBytesLen);
  for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
    DecryptBlock(in + i, out + i, roundKeys);
    XorBlocks(block, out + i, out + i, blockBytesLen);
    memcpy(block, in + i, blockBytesLen);
  }

  delete[] roundKeys;

  return out;
}

unsigned char *AES::EncryptCFB(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[],
                               const unsigned char *iv) {
  CheckLength(inLen);
  unsigned char *out = new unsigned char[inLen];
  unsigned char block[blockBytesLen];
  unsigned char encryptedBlock[blockBytesLen];
  unsigned char *roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
  KeyExpansion(key, roundKeys);
  memcpy(block, iv, blockBytesLen);
  for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
    EncryptBlock(block, encryptedBlock, roundKeys);
    XorBlocks(in + i, encryptedBlock, out + i, blockBytesLen);
    memcpy(block, out + i, blockBytesLen);
  }

  delete[] roundKeys;

  return out;
}

unsigned char *AES::DecryptCFB(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[],
                               const unsigned char *iv) {
  CheckLength(inLen);
  unsigned char *out = new unsigned char[inLen];
  unsigned char block[blockBytesLen];
  unsigned char encryptedBlock[blockBytesLen];
  unsigned char *roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
  KeyExpansion(key, roundKeys);
  memcpy(block, iv, blockBytesLen);
  for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
    EncryptBlock(block, encryptedBlock, roundKeys);
    XorBlocks(in + i, encryptedBlock, out + i, blockBytesLen);
    memcpy(block, in + i, blockBytesLen);
  }

  delete[] roundKeys;

  return out;
}

void AES::CheckLength(unsigned int len) {
  if (len % blockBytesLen != 0) {
    throw std::length_error("Plaintext length must be divisible by " +
                            std::to_string(blockBytesLen));
  }
}

void AES::EncryptBlock(const unsigned char in[], unsigned char out[], unsigned char *roundKeys) {
  unsigned char state[4][Nb];

  // Unroll loops for data copying
  std::memcpy(state, in, 4*Nb*sizeof(unsigned char));

  __builtin_prefetch(&state, 0, 0);  // Prefetch the memory location
  AddRoundKey(state, roundKeys);

  for (unsigned int round = 1; round <= Nr - 1; round++) {
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state, roundKeys + round * 4 * Nb);
  }

  SubBytes(state);
  ShiftRows(state);
  AddRoundKey(state, roundKeys + Nr * 4 * Nb);

  // Unroll loops for data copying
  std::memcpy(out, state, 4*Nb*sizeof(unsigned char));
}

void AES::DecryptBlock(const unsigned char in[], unsigned char out[], unsigned char *roundKeys) {
  unsigned char state[4][Nb];

  // Unroll loops for data copying
  std::memcpy(state, in, 4*Nb*sizeof(unsigned char));

  __builtin_prefetch(&state, 0, 0);  // Prefetch the memory location
  AddRoundKey(state, roundKeys + Nr * 4 * Nb);

  for (unsigned int round = Nr - 1; round >= 1; round--) {
    InvSubBytes(state);
    InvShiftRows(state);
    AddRoundKey(state, roundKeys + round * 4 * Nb);
    InvMixColumns(state);
  }

  InvSubBytes(state);
  InvShiftRows(state);
  AddRoundKey(state, roundKeys);

  // Unroll loops for data copying
  std::memcpy(out, state, 4*Nb*sizeof(unsigned char));
}
void AES::SubBytes(unsigned char state[4][Nb]) {
  unsigned int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < Nb; j++) {
      __builtin_prefetch(&state[i][j], 0, 0);  // Prefetch the memory location
      state[i][j] = sbox[state[i][j]];
    }
  }
}

void AES::ShiftRow(unsigned char state[4][Nb], unsigned int i, unsigned int n) {
    __builtin_prefetch(&state[i], 0, 0);  // Prefetch the memory location
    std::rotate(&state[i][0], &state[i][n], &state[i][Nb]);
}

void AES::ShiftRows(unsigned char state[4][Nb]) {
  ShiftRow(state, 1, 1);
  ShiftRow(state, 2, 2);
  ShiftRow(state, 3, 3);
}

unsigned char AES::xtime(unsigned char b)  // multiply on x
{
  return (b << 1) ^ (((b >> 7) & 1) * 0x1b);
}

void AES::MixColumns(unsigned char state[4][Nb]) {
  unsigned char temp_state[4][Nb];
  
  // Copy the state to temp_state and prefetch
  for (size_t i = 0; i < 4; ++i) {
    std::memcpy(temp_state[i], state[i], 4);
    __builtin_prefetch(temp_state[i], 1, 3);
  }

  // clear the original state
  for (size_t i = 0; i < 4; ++i) {
    memset(state[i], 0, 4);
  }

  // Perform matrix multiplication and accumulate the result in state
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      for (size_t k = 0; k < 4; ++k) {
        unsigned char multiplier = CMDS[i][k];
        unsigned char element = temp_state[k][j];
        if (multiplier == 1)
          state[i][j] ^= element;
        else
          state[i][j] ^= GF_MUL_TABLE[multiplier][element];
      }
      // Prefetch for the next iteration
      if (j < 3) __builtin_prefetch(&temp_state[i][j+1], 0, 3);
    }
  }
}
void AES::AddRoundKey(unsigned char state[4][Nb], unsigned char *key) {
  for (unsigned int i = 0; i < 4; i++) {
    for (unsigned int j = 0; j < Nb; j++) {
      __builtin_prefetch(&state[i][j], 0, 0);  // Prefetch the memory location
      state[i][j] ^= key[i + 4 * j];
    }
  }
}

void AES::SubWord(unsigned char *a) {
  for (int i = 0; i < 4; i++) {
    a[i] = sbox[a[i]];
  }
}

void AES::RotWord(unsigned char *a) {
  unsigned char c = a[0];
  a[0] = a[1];
  a[1] = a[2];
  a[2] = a[3];
  a[3] = c;
}

void AES::XorWords(unsigned char *a, unsigned char *b, unsigned char *c) {
  int i;
  for (i = 0; i < 4; i++) {
    c[i] = a[i] ^ b[i];
  }
}

void AES::Rcon(unsigned char *a, unsigned int n) {
  unsigned int i;
  unsigned char c = 1;
  for (i = 0; i < n - 1; i++) {
    c = xtime(c);
  }

  a[0] = c;
  a[1] = a[2] = a[3] = 0;
}

void AES::KeyExpansion(const unsigned char key[], unsigned char w[]) {
  unsigned char temp[4];
  unsigned char rcon[4];

  unsigned int i = 0;
  while (i < 4 * Nk) {
    w[i] = key[i];
    i++;
  }

  i = 4 * Nk;
  while (i < 4 * Nb * (Nr + 1)) {
    temp[0] = w[i - 4 + 0];
    temp[1] = w[i - 4 + 1];
    temp[2] = w[i - 4 + 2];
    temp[3] = w[i - 4 + 3];

    if (i / 4 % Nk == 0) {
      RotWord(temp);
      SubWord(temp);
      Rcon(rcon, i / (Nk * 4));
      XorWords(temp, rcon, temp);
    } else if (Nk > 6 && i / 4 % Nk == 4) {
      SubWord(temp);
    }

    w[i + 0] = w[i - 4 * Nk] ^ temp[0];
    w[i + 1] = w[i + 1 - 4 * Nk] ^ temp[1];
    w[i + 2] = w[i + 2 - 4 * Nk] ^ temp[2];
    w[i + 3] = w[i + 3 - 4 * Nk] ^ temp[3];
    i += 4;
  }
}

void AES::InvSubBytes(unsigned char state[4][Nb]) {
  unsigned int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < Nb; j++) {
      state[i][j] = inv_sbox[state[i][j]];
    }
  }
}

void AES::InvMixColumns(unsigned char state[4][Nb]) {
  unsigned char temp_state[4][Nb];

  for (size_t i = 0; i < 4; ++i) {
    memset(temp_state[i], 0, 4);
  }

  for (size_t i = 0; i < 4; ++i) {
    for (size_t k = 0; k < 4; ++k) {
      for (size_t j = 0; j < 4; ++j) {
        temp_state[i][j] ^= GF_MUL_TABLE[INV_CMDS[i][k]][state[k][j]];
      }
    }
  }

  for (size_t i = 0; i < 4; ++i) {
    memcpy(state[i], temp_state[i], 4);
  }
}

void AES::InvShiftRows(unsigned char state[4][Nb]) {
  ShiftRow(state, 1, Nb - 1);
  ShiftRow(state, 2, Nb - 2);
  ShiftRow(state, 3, Nb - 3);
}

void AES::XorBlocks(const unsigned char *a, const unsigned char *b,
                    unsigned char *c, unsigned int len) {
  for (unsigned int i = 0; i < len; i++) {
    c[i] = a[i] ^ b[i];
  }
}

void AES::printHexArray(unsigned char a[], unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    printf("%02x ", a[i]);
  }
}

void AES::printHexVector(std::vector<unsigned char> a) {
  for (unsigned int i = 0; i < a.size(); i++) {
    printf("%02x ", a[i]);
  }
}

std::vector<unsigned char> AES::ArrayToVector(unsigned char *a,
                                              unsigned int len) {
  std::vector<unsigned char> v(a, a + len * sizeof(unsigned char));
  return v;
}

unsigned char *AES::VectorToArray(std::vector<unsigned char> &a) {
  return a.data();
}

std::vector<unsigned char> AES::EncryptECB(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key) {
  unsigned char *out = EncryptECB(VectorToArray(in), (unsigned int)in.size(),
                                  VectorToArray(key));
  std::vector<unsigned char> v = ArrayToVector(out, in.size());
  delete[] out;
  return v;
}

std::vector<unsigned char> AES::DecryptECB(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key) {
  unsigned char *out = DecryptECB(VectorToArray(in), (unsigned int)in.size(),
                                  VectorToArray(key));
  std::vector<unsigned char> v = ArrayToVector(out, (unsigned int)in.size());
  delete[] out;
  return v;
}

std::vector<unsigned char> AES::EncryptCBC(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key,
                                           std::vector<unsigned char> iv) {
  unsigned char *out = EncryptCBC(VectorToArray(in), (unsigned int)in.size(),
                                  VectorToArray(key), VectorToArray(iv));
  std::vector<unsigned char> v = ArrayToVector(out, in.size());
  delete[] out;
  return v;
}

std::vector<unsigned char> AES::DecryptCBC(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key,
                                           std::vector<unsigned char> iv) {
  unsigned char *out = DecryptCBC(VectorToArray(in), (unsigned int)in.size(),
                                  VectorToArray(key), VectorToArray(iv));
  std::vector<unsigned char> v = ArrayToVector(out, (unsigned int)in.size());
  delete[] out;
  return v;
}

std::vector<unsigned char> AES::EncryptCFB(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key,
                                           std::vector<unsigned char> iv) {
  unsigned char *out = EncryptCFB(VectorToArray(in), (unsigned int)in.size(),
                                  VectorToArray(key), VectorToArray(iv));
  std::vector<unsigned char> v = ArrayToVector(out, in.size());
  delete[] out;
  return v;
}

std::vector<unsigned char> AES::DecryptCFB(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key,
                                           std::vector<unsigned char> iv) {
  unsigned char *out = DecryptCFB(VectorToArray(in), (unsigned int)in.size(),
                                  VectorToArray(key), VectorToArray(iv));
  std::vector<unsigned char> v = ArrayToVector(out, (unsigned int)in.size());
  delete[] out;
  return v;
}