#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "EventQueue.hpp"
#include "Notification.hpp"

class EventQueueTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
      p.f = [](gpointer data) {
        Param *p = static_cast<Param*>(data);
        p->count++;
        return FALSE;
      };

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
      uint32_t count{0};
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

TEST_F(EventQueueTest, MultiIdleEvent) 
{
  uint32_t id1 = e.addIdle(Action, &p, NULL);
  uint32_t id2 = e.addIdle(Action, &p, NULL);
  uint32_t id3 = e.addIdle(Action, &p, NULL);
  uint32_t id4 = e.addIdle(Action, &p, NULL);
  uint32_t id5 = e.addIdle(Action, &p, MarkDone);
  Wait();

  EXPECT_TRUE(p.count == 5);
  EXPECT_TRUE(id1 && id2 && id3 && id4 && id5);
  EXPECT_TRUE(p.done);
}

TEST_F(EventQueueTest, TimeoutEvent) 
{
  uint32_t id = e.addTimeout(Action, 5000, &p, MarkDone);
  Wait();

  EXPECT_TRUE(id != 0);
  EXPECT_TRUE(p.done);
}

TEST_F(EventQueueTest, MultiTimeoutEvent) 
{
  uint32_t id1 = e.addTimeout(Action, 1000, &p, NULL);
  uint32_t id2 = e.addTimeout(Action, 1100, &p, NULL);
  uint32_t id3 = e.addTimeout(Action, 1200, &p, NULL);
  uint32_t id4 = e.addTimeout(Action, 1300, &p, NULL);
  uint32_t id5 = e.addTimeout(Action, 1400, &p, MarkDone);
  Wait();

  EXPECT_TRUE(p.count == 5);
  EXPECT_TRUE(id1 && id2 && id3 && id4 && id5);
  EXPECT_TRUE(p.done);
}
