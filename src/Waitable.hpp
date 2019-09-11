#pragma once
#include <condition_variable>
#include <mutex>

class Waitable
{
  public:
    Waitable(void);
    ~Waitable(void);
  public:
    void notify(void);
    void wait(void);
  private:
    std::condition_variable cv;
    std::mutex m;
};
