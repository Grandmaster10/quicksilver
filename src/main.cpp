#include <iostream>
#include <thread>
#include <chrono>
#include <utils/tsc.h>

int main() {
    uint64_t start = utils::rdtsc();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    uint64_t end = utils::rdtsc();

    uint64_t cycles = end - start;
    std::cout << "Number of cycles per second: " << cycles << "\n";
    std::cout << "Clock frequency: " << (cycles/1000000000.0) << " GHz\n";

    return 0;
}
