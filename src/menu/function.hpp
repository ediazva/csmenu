// https://vittorioromeo.info/index/blog/passing_functions_to_functions.html

#pragma once
#include <new>
#include <concepts>
#include <type_traits>
#include <utility>

#include "priv/exception.hpp"

namespace menu {
   template<typename Signature>
   class Function {};

   template<typename R, typename... Args>
   class Function<R(Args...)> {
      typedef R(*callback_t)(const void*, Args...);
      typedef std::aligned_union_t<8, void*, R(*)(Args...)> storage_t;
      
      storage_t m_storage;
      callback_t m_callback;

      void* get_memory() {
         return &m_storage;
      }
      const void* get_memory() const {
         return &m_storage;
      }
   public:
      Function() :
         m_callback{nullptr} {}

      Function(Function&& o) {
         swap(o);
      }

      Function(R(*fn)(Args...)) {
         using pointer_t = R(*)(Args...);

         ::new (get_memory()) pointer_t(fn);

         m_callback = [](const void* ptr, Args... args) {
            auto func = *static_cast<const pointer_t*>(ptr);
            return func(std::forward<Args>(args)...);
         };
      }

      template<typename Fn> requires std::same_as<std::invoke_result_t<Fn, Args...>, R>
      explicit Function(Fn& fn) {
         using pointer_t = void*;

         ::new (get_memory()) pointer_t(&fn);

         m_callback = [](const void* _ptr, Args... args) {
            auto ptr = *static_cast<const pointer_t*>(_ptr);
            auto& func = *static_cast<Fn*>(ptr);
            return static_cast<R>(func(std::forward<Args>(args)...));
         };
      }

      Function(const Function&) = delete;

      void swap(Function& o) {
         m_callback = std::exchange(o.m_callback, nullptr);
         m_storage = o.m_storage;
      }
      bool isEmpty() const {return m_callback == nullptr;}

      R operator()(Args... args) const {
         if(isEmpty())
            THROW_EXCEPTION("funcptr is null");
         return m_callback(get_memory(), std::forward<Args>(args)...);
      }

      Function& operator=(Function&& o) {
         if(this == &o)
            return *this;
         
         swap(o);

         return *this;
      }
      Function& operator=(const Function&) = delete;
   };   
} // namespace menu