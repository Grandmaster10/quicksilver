#pragma once
#include <atomic>
#include <cstddef>
#include <array>

template<typename T, size_t Size>

class SPSCQueue {
    static_assert((Size & (Size-1)) == 0, "Size of queue must be a power of 2"); // To use bitmasking instead of relying on slow mod

    alignas(64) std::array<T, Size> buffer;
    alignas(64) std::atomic<size_t> head{0};
    alignas(64) std::atomic<size_t> tail{0};

public:
    // WRITE - Tail, READ - Head
    bool push(const T& data) {
        const size_t curr_tl = tail.load(std::memory_order_relaxed);    // get write location
        const size_t write_idx = (curr_tl) & (Size - 1);

        if((curr_tl - head.load(std::memory_order_acquire)) == Size) return false; // Check if the buffer is full

        buffer[write_idx] = data;
        tail.store(curr_tl+1, std::memory_order_release);
        return true;
    }

    bool pop(T& data) {
        const size_t curr_h = head.load(std::memory_order_relaxed);  // get read location
        const size_t read_idx = (curr_h) & (Size - 1);
        if(curr_h == tail.load(std::memory_order_acquire)) return false;    // Check if buffer is empty

        data = buffer[read_idx];
        head.store(curr_h+1, std::memory_order_release);

        return true;
    }
};