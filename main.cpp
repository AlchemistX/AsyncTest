#include <iostream>
#include "Asyncable.hpp"
#include "Waitable.hpp"

int main(void)
{
  Waitable w;
  Asyncable a;
  GDestroyNotify MarkDone = [](gpointer data) {
        Waitable* w = static_cast<Waitable*>(data);
        w->notify();
      };
  GSourceFunc Action = [](gpointer data) -> gboolean {
        std::cout << "BAM!" << std::endl;
        return FALSE;
      };

  uint32_t id = a.addTimeout(Action, 5000, &w, MarkDone);
  
  w.wait();
  
  return 0;
}
