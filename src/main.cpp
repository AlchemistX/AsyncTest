#include <iostream>
#include "EventQueue.hpp"
#include "Notification.hpp"

int main(void)
{
  Notification n;
  EventQueue e;
  GDestroyNotify MarkDone = [](gpointer data) {
        Notification* w = static_cast<Notification*>(data);
        w->notify();
      };
  GSourceFunc Action = [](gpointer data) -> gboolean {
        std::cout << "BAM!" << std::endl;
        return FALSE;
      };

  uint32_t id = e.addTimeout(Action, 5000, &n, MarkDone);
  
  n.wait();
  
  return 0;
}
