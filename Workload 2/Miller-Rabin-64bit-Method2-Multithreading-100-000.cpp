#include <iostream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <vector>

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
unsigned long long generate_prime_candidate() {
    // Initialize a number p
    unsigned long long p;
    // Generate two random numbers and shift the first one to the left by 32 bits
    unsigned long long upper = static_cast<unsigned long long>(rand()) << 32;
    unsigned long long lower = rand();
    // Bitwise OR operation to combine the two random numbers into one
    p = upper | lower;
    // If p is even, increment it by 1 to make it odd (since all primes except 2 are odd)
    if (p % 2 == 0) ++p;
    return p;
}

// generate_prime_number generates a prime number by repeatedly generating prime candidates and checking if they are prime
unsigned long long generate_prime_number() {
    // Initialize a number p as 4 (which is not a prime number)
    unsigned long long p = 4;
    std::cout << "Generating prime number...\n";
    // While loop runs as long as p is not a prime number
    while (!is_prime(p, 16))
        // Generate a new prime candidate
        p = generate_prime_candidate();
    // Return the prime number
    return p;
}

// Thread function to generate a prime number and store it in the given reference
void generate_prime_number_thread(unsigned long long& result) {
    // Initialize a number p as 4 (which is not a prime number)
    unsigned long long p = 4;
    // While loop runs as long as p is not a prime number
    while (!is_prime(p, 16))
        // Generate a new prime candidate
        p = generate_prime_candidate();
    // Store the prime number in the result
    result = p;
}

int main() {
    // Seed the random number generator with the current time
    srand(time(0));

    // Create a vector to store the prime numbers
    std::vector<unsigned long long> primes(100000);
    // Create a vector to store the threads
    std::vector<std::thread> threads;

    // Start 8 threads to generate prime numbers
    for (int i = 0; i < 100000; ++i){
        threads.push_back(std::thread(generate_prime_number_thread, std::ref(primes[i])));
    }

    // Wait for all threads to finish
    for (auto& t : threads){
        t.join();
    }

    // Print the prime numbers
    for (const auto& p : primes){
        std::cout << p << "\n";
    }

    return 0;
}

/*
int main() {
    // Seed the random number generator with the current time
    srand(time(0));
    // Generate and print 8 prime numbers
    for (int i = 0; i < 8; ++i){
        std::cout << generate_prime_number() << "\n";
    }
    return 0;
}*/
