#pragma once
#include <condition_variable>
#include <mutex>

class Notification
{
  public:
    Notification(void);
    ~Notification(void);
  public:
    void notify(void);
    void wait(void);
  private:
    std::condition_variable cv;
    std::mutex m;
};
