#include <ringbuffer.h>

template<typename T>
class Productor {
  public:
    Productor(RingBuffer<T> rb) :
      ringbuffer_(rb) {
        shall_stop_ = true;
      }

    virtual bool Product() = 0;

    virtual void Start() {
      shall_stop_ = false;
      while(!shall_stop_) {
        Product();
      };
    }

    virtual void Stop() {
      shall_stop_ = true;
    }

    RingBuffer<T>& ringbuffer_;
  private:
    bool shall_stop_;
};
