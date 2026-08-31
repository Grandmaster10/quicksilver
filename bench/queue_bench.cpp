#include <iostream>
#include <thread>
#include "../src/utils/tsc.h"
#include "../src/scq/spsc_queue.h"

int main() {
    SPSCQueue<int, 1024*1024> sq;
    std::cout << "SPSC Benchmark\n";

    uint64_t start = utils::rdtsc();
    std::thread producer([&] () {
        for(int i = 0; i<10000000; i++) {
            while(!sq.push(i));
        }
    });

    std::thread consumer([&] () {
        int val;
        for(int i = 0; i<10000000; i++) {
            while(!sq.pop(val));
        }
    });

    producer.join();
    consumer.join();

    uint64_t end = utils::rdtsc();
    uint64_t total = end - start;

    std::cout << "Total cycles: " << total << "\n";
    return 0;
}