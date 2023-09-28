// author chagpt
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <functional>

// Define a function to monitor
void myFunction(int id) {
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Print the function ID
    std::cout << "Function " << id << " called" << std::endl;
}

int main() {
    // Number of threads
    const int numThreads = 5;

    // Number of calls to monitor
    const int numCalls = 10;

    // Mutex for synchronization
    std::mutex mtx;

    // Vector to store thread objects
    std::vector<std::thread> threads;

    // Vector to store function call counts
    std::vector<int> callCounts(numThreads, 0);

    // Launch threads
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([i, &mtx, &callCounts, numCalls]() {
            for (int j = 0; j < numCalls; ++j) {
                // Measure time
                auto startTime = std::chrono::high_resolution_clock::now();

                // Call the monitored function
                myFunction(i);

                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

                // Increment call count
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    ++callCounts[i];
                    std::cout << "Thread " << i << ": Call " << callCounts[i] << ", Time: " << duration.count() << " ms" << std::endl;
                }
            }
        });
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    // Print total call counts
    for (int i = 0; i < numThreads; ++i) {
        std::cout << "Function " << i << " was called " << callCounts[i] << " times." << std::endl;
    }

    return 0;
}
