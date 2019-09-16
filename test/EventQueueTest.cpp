#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "EventQueue.hpp"
#include "Notification.hpp"

TEST(EventQueue, timeout) 
{
  Notification w;
  EventQueue a;
  GDestroyNotify MarkDone = [](gpointer data) {
    Notification* w = static_cast<Notification*>(data);
    w->notify();
  };
  GSourceFunc Action = [](gpointer data) -> gboolean {
    std::cout << "BAM!" << std::endl;
    return FALSE;
  };

  uint32_t id = a.addTimeout(Action, 5000, &w, MarkDone);

  w.wait();

  EXPECT_TRUE(true);
}
