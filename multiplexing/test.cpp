#include <iostream>
#include <chrono>

int main() {
    const long long ITERATIONS = 1000000000; // 1 Billion
    volatile long long dummy = 0; // 'volatile' prevents the compiler from optimizing the loop away

    // --- Benchmark FOR Loop ---
    auto start_for = std::chrono::high_resolution_clock::now();
    for (long long i = 0; i < ITERATIONS; ++i) {
        dummy++;
    }
    auto end_for = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_for = end_for - start_for;


    // --- Reset and Benchmark WHILE Loop ---
    dummy = 0; 
    auto start_while = std::chrono::high_resolution_clock::now();
    long long j = 0;
    while (j < ITERATIONS) {
        dummy++;
        ++j;
    }
    auto end_while = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_while = end_while - start_while;


    // --- Output Results ---
    std::cout << "For loop time:   " << duration_for.count() << " ms\n";
    std::cout << "While loop time: " << duration_while.count() << " ms\n";

    return 0;
}