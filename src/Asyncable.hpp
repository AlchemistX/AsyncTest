#pragma once
#include <memory>
#include <thread>
#include <string>
#include <glib.h>

class Asyncable
{
  public:
    Asyncable(void);
    ~Asyncable(void);
  public:
    uint32_t remTask(uint32_t id);
    uint32_t addIdle(GSourceFunc f, gpointer data, GDestroyNotify notify);
    uint32_t addTimeout(GSourceFunc f, uint32_t interval,  gpointer data,
        GDestroyNotify notify);

  private:
    uint32_t addEventSource(GSource *s, GSourceFunc f, gpointer data,
        GDestroyNotify notify);
    uint32_t remEventSource(uint32_t id);
    void handleError(const std::system_error &e);

  private:
    GMainLoop *loop_{nullptr};
    std::shared_ptr<std::thread> loopThread_;
    std::string errMessage_;
    int errCode_{0};
};
