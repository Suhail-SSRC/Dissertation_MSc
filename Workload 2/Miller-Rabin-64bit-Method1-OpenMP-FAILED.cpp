#include <iostream>
#include <ctime>
#include <random>
#include <cstdint>
#include <omp.h>

// Helper function to generate a random number in a specific range
unsigned long long rand_range(unsigned long long min, unsigned long long max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

unsigned long long mod_pow(unsigned long long base, unsigned long long exponent, unsigned long long mod) {
    base %= mod;
    unsigned long long result = 1;
    while (exponent > 0) {
        if (exponent & 1) 
            result = (result * base) % mod;
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return result;
}

bool is_prime(unsigned long long n, int k = 5) {
    if (n == 2 || n == 3)
        return true;
    if (n <= 1 || n % 2 == 0)
        return false;

    unsigned long long s = 0;
    unsigned long long r = n - 1;
    while (r % 2 == 0) {
        s += 1;
        r /= 2;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long long> dis(2, n - 2);
    for (int _ = 0; _ < k; _++) {
        unsigned long long a = dis(gen);
        unsigned long long x = mod_pow(a, r, n);

        if (x != 1 && x != n - 1) {
            unsigned long long j = 1;
            while (j < s && x != n - 1) {
                x = (x * x) % n;
                if (x == 1)
                    return false;
                j += 1;
            }
            if (x != n - 1)
                return false;
        }
    }
    return true;
}

int main() {
    srand(time(0));

    // The number of prime numbers to generate
    const int prime_count = 8;

    // An array to store the generated prime numbers
    unsigned long long primes[prime_count];

    // Generate the prime numbers in parallel
    #pragma omp parallel for
    for (int i = 0; i < prime_count; ++i) {
        // Create a thread-local random number generator
        unsigned int seed = time(0) ^ omp_get_thread_num();
        // Generate a prime number and store it in the array
        do {
            primes[i] = rand_range(1ULL << 63, ~(1ULL << 63));
        } while (!is_prime(primes[i], 64));
    }

    // Print the prime numbers
    for (int i = 0; i < prime_count; ++i) {
        std::cout << "64-bit prime number " << (i + 1) << ": " << primes[i] << "\n";
    }

    return 0;
}
