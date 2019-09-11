#include "Waitable.hpp"

Waitable::Waitable(void) {}

Waitable::~Waitable(void) {}

void Waitable::notify(void)
{
  cv.notify_all();
}

void Waitable::wait(void)
{
  std::unique_lock<std::mutex> lock(m);
  cv.wait(lock);
}
