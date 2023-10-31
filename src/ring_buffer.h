#ifndef FASTCAT_RING_BUFFER_H_
#define FASTCAT_RING_BUFFER_H_

#include <iostream>
#include <stdexcept>
#include <vector>

namespace fastcat 
{
template <typename T>
class RingBuffer
{
  std::vector<T> buffer_;
  size_t         index_ = 0;
  size_t         num_received_ = 0;

 public:
  RingBuffer(size_t buffer_size = 10) { buffer_.resize(buffer_size); }

  T load(void) { return buffer_[index_ % buffer_.size()]; }

  T load(size_t delay)
  {
    if (delay > buffer_.size()) {
      throw std::runtime_error("Delay is greater than allocated buffer size");
    }
    return buffer_[(index_ - delay) % buffer_.size()];
  }

  void store(const T& value) { 
    buffer_[(++index_) % buffer_.size()] = value; 
    num_received_++;
  }

  void clear() {
    num_received_ = 0;
  }

  size_t get_num_received() {
    return num_received_;
  }

  size_t size() {
    return buffer_.size();
  }
};
}

#endif
