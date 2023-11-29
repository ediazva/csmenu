#pragma once
#include <stdexcept>

// #define THROW_EXCEPTION(msg) throw std::runtime_error(__PRETTY_FUNCTION__ " -> " msg)
namespace menu::priv {
   inline void throw_exception(const char* func_name, const char* msg) {
      char buf[128];
      snprintf(buf, 128, "%s -> %s", func_name, msg);
      throw std::runtime_error(buf);
   }
} // namespace menu::priv

#define THROW_EXCEPTION(msg) menu::priv::throw_exception(__PRETTY_FUNCTION__, msg)