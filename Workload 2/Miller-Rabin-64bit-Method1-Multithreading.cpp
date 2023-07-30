#include <iostream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <vector>
// #include <pthread.h>

// safe_square_mod_n calculates (x * x) % n without causing overflow
unsigned long long safe_square_mod_n(unsigned long long x, unsigned long long n) {
    // Initialize the result
    unsigned long long result = 0;
    // Modulo operation to avoid overflow
    x = x % n;
    // Add x to the result x times, performing modulo operation each time to avoid overflow
    for (unsigned long long i = 0; i < x; ++i) {
        result = (result + x) % n;
    }
    return result;
}

// mod_mul performs modular multiplication, which is the multiplication of two numbers followed by taking the modulus
unsigned long long mod_mul(unsigned long long a, unsigned long long b, unsigned long long mod) {
    // Initialize the result
    unsigned long long result = 0;
    // While loop runs as long as b is greater than 0
    while (b > 0) {
        // If b is odd, add a to the result (mod mod)
        if (b % 2 == 1)
            result = (result + a) % mod;
        // Multiply a by 2 (mod mod)
        a = (a * 2) % mod;
        // Divide b by 2
        b /= 2;
    }
    return result;
}

// mod_pow performs modular exponentiation, which is the operation of raising a number to a power, followed by taking the modulus
unsigned long long mod_pow(unsigned long long base, unsigned long long exponent, unsigned long long mod) {
    // Modulo operation to avoid overflow
    base %= mod;
    // Initialize the result as 1
    unsigned long long result = 1;
    // While loop runs as long as the exponent is greater than 0
    while (exponent > 0) {
        // If the exponent is odd, multiply the result by base (mod mod)
        if (exponent & 1) 
            result = mod_mul(result, base, mod);
        // Square the base (mod mod)
        base = mod_mul(base, base, mod);
        // Divide the exponent by 2
        exponent >>= 1;
    }
    return result;
}

// is_prime uses the Miller-Rabin primality test to check if a given number n is prime
bool is_prime(unsigned long long n, int k = 128) {
    // Special cases: 2 and 3 are prime, numbers less than 2 or even are not prime
    if (n == 2 || n == 3)
        return true;
    if (n <= 1 || n % 2 == 0)
        return false;
    // Decompose (n - 1) into 2^s * r
    unsigned long long s = 0;
    unsigned long long r = n - 1;
    while (r % 2 == 0) {
        s += 1;
        r /= 2;
    }
    // Witness loop: try k times
    for (int _ = 0; _ < k; _++) {
        // Pick a random number a in the range [2, n-4]
        unsigned long long a = 2 + rand() % (n - 4);
        // Compute x = (a^r) mod n using the binary exponentiation algorithm
        unsigned long long x = mod_pow(a, r, n);
        // If x is not 1 and x is not n-1, then n is composite
        if (x != 1 && x != n - 1) {
            // Repeat s times
            unsigned long long j = 1;
            while (j < s && x != n - 1) {
                // Square x mod n
                x = mod_mul(x, x, n);
                // If x is 1, then n is composite
                if (x == 1)
                    return false;
                j += 1;
            }
            // If x is not n - 1, then n is composite
            if (x != n - 1)
                return false;
        }
    }
    // If no base a has been found that proves that n is composite after k iterations, assume that n is probably prime
    return true;
}

// generate_prime_candidate generates a random number which is potentially a prime
unsigned long long generate_prime_candidate(size_t bits) {
    // Handle the 1-bit and 2-bit cases separately
    if (bits == 1) {
        return 2;  // The only 1-bit prime number is 2
    } else if (bits == 2) {
        return rand() % 2 ? 2 : 3;  // The 2-bit prime numbers are 2 and 3
    }

    // Initialize a number p
    unsigned long long p = 0;

    // Generate a random number with the specified bit count
    for (size_t i = 0; i < bits; ++i) {
        p = (p << 1) | (rand() % 2);
    }

    // Set the high bit to ensure the correct bit count
    p |= 1ULL << (bits - 1);

    // If p is even, increment it by 1 to make it odd (since all primes except 2 are odd)
    if (p % 2 == 0) ++p;

    return p;
}
/* // Thread function to generate a prime number and store it in the given reference
void generate_prime_number_thread(unsigned long long& result, size_t bits, int rounds, int core_id) {
    // Apply CPU pinning
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    
    if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset)) {
        perror("Error calling pthread_setaffinity_np: ");
    }
    
    // Initialize a number p as 0
    unsigned long long p = 0;
    do {
        // Generate a new prime candidate
        p = generate_prime_candidate(bits);
    } while (!is_prime(p, rounds));
    // Store the prime number in the result
    result = p;
}

int main() {
    // Seed the random number generator with the current time
    srand(time(0));

    // The bit count is 64
    size_t bits = 64;

    // The number of rounds for the Miller-Rabin test
    int rounds = bits / 4;

    // Create a vector to store the prime numbers
    std::vector<unsigned long long> primes(8);
    // Create a vector to store the threads
    std::vector<std::thread> threads;

    // Start 8 threads to generate prime numbers
    for (int i = 0; i < 8; ++i) {
        threads.push_back(std::thread(generate_prime_number_thread, std::ref(primes[i]), bits, rounds, i));
    }

    // Wait for all threads to finish
    for (auto& t : threads){
        t.join();
    }

    // Print the prime numbers
    for (int i = 0; i < 8; ++i){
        std::cout << "64-bit prime number " << (i + 1) << ": " << primes[i] << "\n";
    }

    return 0;
}*/

// Thread function to generate a prime number and store it in the given reference
void generate_prime_number_thread(unsigned long long& result, size_t bits, int rounds) {
    // Initialize a number p as 0
    unsigned long long p = 0;
    do {
        // Generate a new prime candidate
        p = generate_prime_candidate(bits);
    } while (!is_prime(p, rounds));
    // Store the prime number in the result
    result = p;
}

int main() {
    // Seed the random number generator with the current time
    srand(time(0));

    // The bit count is 64
    size_t bits = 64;

    // The number of rounds for the Miller-Rabin test
    int rounds = bits / 4;

    // Create a vector to store the prime numbers
    std::vector<unsigned long long> primes(6);
    // Create a vector to store the threads
    std::vector<std::thread> threads;

    // Start 8 threads to generate prime numbers
    for (int i = 0; i < 6; ++i) {
        threads.push_back(std::thread(generate_prime_number_thread, std::ref(primes[i]), bits, rounds));
    }

    // Wait for all threads to finish
    for (auto& t : threads){
        t.join();
    }

    // Print the prime numbers
    for (int i = 0; i < 8; ++i){
        std::cout << "64-bit prime number " << (i + 1) << ": " << primes[i] << "\n";
    }

    return 0;
}
