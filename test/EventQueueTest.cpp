#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "EventQueue.hpp"
#include "Notification.hpp"

class EventQueueTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
      MarkDone = [](gpointer data) {
        Param *p = static_cast<Param*>(data);
        p->done = true;
        p->n.notify();
      };

      Action = [](gpointer data) {
        Param *p = static_cast<Param*>(data);
        if (p->f)
          return p->f(data);
        else
          return FALSE;
      };
    }

    void TearDown() override
    {
    }

    void Wait(void)
    {
      p.n.wait();
    }

    struct Param
    {
      Notification n;
      GSourceFunc f{nullptr};
      bool done{false};
    } p;
    EventQueue e;
    GDestroyNotify MarkDone{nullptr};
    GSourceFunc Action{nullptr};
};

TEST_F(EventQueueTest, Construct)
{
  EventQueue e;
}

TEST_F(EventQueueTest, IdleEvent) 
{
  uint32_t id = e.addIdle(Action, &p, MarkDone);
  Wait();

  EXPECT_TRUE(id != 0);
  EXPECT_TRUE(p.done);
}

TEST_F(EventQueueTest, TimeoutEvent) 
{
  uint32_t id = e.addTimeout(Action, 5000, &p, MarkDone);
  Wait();

  EXPECT_TRUE(id != 0);
  EXPECT_TRUE(p.done);
}
