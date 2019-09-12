#include "Notification.hpp"

Notification::Notification(void) {}

Notification::~Notification(void) {}

void Notification::notify(void)
{
  cv.notify_all();
}

void Notification::wait(void)
{
  std::unique_lock<std::mutex> lock(m);
  cv.wait(lock);
}
