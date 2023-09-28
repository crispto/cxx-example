#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <functional>
#include <memory>
#include <atomic>

// Shared counter accessed by all threads
std::shared_ptr<std::atomic<int64_t>> sharedCounter = std::make_shared<std::atomic<int64_t>>(0);

// Define a function to monitor
void myFunction(int id) {
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Increment the shared counter atomically
    sharedCounter->fetch_add(1, std::memory_order_relaxed);

    // Print the function ID
    std::cout << "Function " << id << " called" << std::endl;
}

int main() {
    // Number of threads
    const int numThreads = 5;

    // Number of calls to monitor
    const int numCalls = 10;

    // Mutex for synchronization (not needed for atomic operations)
    std::mutex mtx;

    // Vector to store thread objects
    std::vector<std::thread> threads;

    // Launch threads
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([i, numCalls]() {
            for (int j = 0; j < numCalls; ++j) {
                // Measure time
                auto startTime = std::chrono::high_resolution_clock::now();

                // Call the monitored function
                myFunction(i);

                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

                // Output shared counter value and time
                std::cout << "Thread " << i << ": Shared Counter: " << sharedCounter->load(std::memory_order_relaxed)
                          << ", Time: " << duration.count() << " ms" << std::endl;
            }
        });
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    // Print the final shared counter value
    std::cout << "Final Shared Counter Value: " << sharedCounter->load(std::memory_order_relaxed) << std::endl;

    return 0;
}
