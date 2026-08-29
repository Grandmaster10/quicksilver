#pragma once
#include <cstdint>

namespace utils {
    inline uint64_t rdtsc(void) {
        uint32_t lo, hi;
        __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
        return (static_cast<uint64_t>(hi) << 32) | lo;
    }
}