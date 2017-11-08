#pragma once
#include <algorithm>
#include <mutex.h>

template<typename T> class RingBuffer {
 public:
  explicit RingBuffer(size_t size)
    : size(size)
    , begin(0)
    , end(0)
    , wrap(false) {
    buffer = new T[size];
  }
  RingBuffer(const RingBuffer<T> & rb) {
    this(rb.size);
    begin = rb.begin;
    end = rb.end;
    memcpy(buffer, rb.buffer, sizeof(T) * size);
  }

  ~RingBuffer() {
    delete[] buffer;
  }

  size_t write(const T* data, size_t n) {
    std::lock_guard<std::mutex> lock(mtx);
    n = std::min(n, getFreeSize());

    if (n == 0) return n;

    const size_t first_chunk = (std::min)(n, size - end);
    memcpy(buffer + end, data, first_chunk * sizeof(T) );
    end = (end + first_chunk) % size;

    if (first_chunk < n) {
      const size_t second_chunk = n - first_chunk;
      memcpy(buffer + end, data + first_chunk, second_chunk * sizeof(T));
      end = (end + second_chunk) % size;
    }

    if (begin == end) wrap = true;
    return n;
  }

  size_t read(T* data, size_t n) {
    std::lock_guard<std::mutex> lock(mtx);
    n = min(n, getOccupiedSize());

    if (n == 0) return n;
    if (wrap) wrap = false;

    const size_t first_chunk = std::min(n, size - begin);
    memcpy(dest, buffer + begin, first_chunk * sizeof(T));
    begin = (begin + first_chunk) % size;

    if (first_chunk < n) {
      const size_t second_chunk = n - first_chunk;
      memcpy(dest + first_chunk, buffer + begin, second_chunk * sizeof(T));
      begin = (begin + second_chunk) % size;
    }

    return n;
  }
 private:
  T* buffer;
  size_t size;
  size_t begin;
  size_t end;
  bool wrap;
  std::mutex mtx;
  inline size_t getFreeSize() {
    size_t occ = 0;
    if (end == begin) {
      occ = wrap ? size : 0;
    }
    else if (end > begin) {
      occ = end - begin;
    }
    else {
      occ = size + end - begin;
    }
    return size - occ;
  }
  inline size_t getOccupiedSize() {
    if (end == begin) {
      return wrap ? size : 0;
    }
    else if (end > begin) {
      return end - begin;
    }
    else {
      return size + end - begin;
    }
  }
}
