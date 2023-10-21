#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <random>
const int num_samples = 10000000; // Number of random samples

bool isPrime(int number)
{
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

bool isPrimedouble(int number)
{
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number * 5; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

bool isPrimeTripple(int number)
{
    if (number <= 1) {
        return false;
    }

    for (int i = 2; i * i <= number * 10; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int parent1()
{
    // Start timing
    int prime_count = 0;
    for (int i = 0; i < 1000000; ++i) {
        if (isPrime(i)) {
            prime_count++;
        }
        if (isPrimedouble(i)) {
            prime_count++;
        }
        if (isPrimeTripple(i)) {
            prime_count++;
        }
    }
    std::cout << "primer count is " << prime_count << std::endl;
    return 0;
}

int parent2()
{
    // Start timing
    int prime_count = 0;
    for (int i = 0; i < 1000000; ++i) {
        if (isPrime(i)) {
            prime_count++;
        }
        if (isPrimedouble(i)) {
            prime_count++;
        }
        if (isPrimeTripple(i)) {
            prime_count++;
        }
    }
    std::cout << "primer count is " << prime_count << std::endl;
    return 0;
}
int main()
{
    for (int i = 0; i < 3; i++) {
        parent1();
    }
    for (int i = 0; i < 7; i++) {
        parent2();
    }
}
