#include "Asyncable.hpp"
#include "Utility.hpp"
#include <unistd.h>

Asyncable::Asyncable(void)
{
  GMainContext *c = g_main_context_new();
  loop_           = g_main_loop_new(c, FALSE);
  g_main_context_unref(c);

  try {
    loopThread_ = std::make_shared<std::thread>(
        [&]() {g_main_loop_run(loop_);});
  } catch (const std::system_error &e) {
    handleError(e);
  }
  while(!g_main_loop_is_running(loop_));
  return;
}

Asyncable::~Asyncable(void)
{
  g_main_loop_quit(loop_);
  if (loopThread_->joinable()) {
    try {
      loopThread_->join();
    } catch (const std::system_error &e) {
      handleError(e);
    }
  }
  g_main_loop_unref(loop_);
  return;
}

uint32_t Asyncable::remTask(uint32_t id)
{
  return remEventSource(id);
}

uint32_t Asyncable::addIdle(GSourceFunc f, gpointer data, GDestroyNotify notify)
{
  return addEventSource(g_idle_source_new(), f, data, notify);
}

uint32_t Asyncable::addTimeout(GSourceFunc f, uint32_t interval,  gpointer data,
    GDestroyNotify notify)
{
  return addEventSource(g_timeout_source_new(interval), f, data, notify);
}

uint32_t Asyncable::addEventSource(GSource *s, GSourceFunc f, gpointer data,
    GDestroyNotify notify)
{
  g_source_set_callback(s, f, data, notify);
  g_source_attach(s, g_main_loop_get_context(loop_));

  uint32_t id = g_source_get_id(s);
  g_source_unref(s);

  return id;
}

uint32_t Asyncable::remEventSource(uint32_t id)
{
  GSource *s = g_main_context_find_source_by_id(g_main_loop_get_context(loop_), id);
  if (s != nullptr)
    g_source_destroy(s);
  return 0;
}

void Asyncable::handleError(const std::system_error &e)
{
  errMessage_ = string_format("Caught a system_error with code %d meaning %s",
      e.code().value(), e.what());
  errCode_ = e.code().value();
}
