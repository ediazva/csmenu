// https://vittorioromeo.info/index/blog/passing_functions_to_functions.html

#pragma once
#include <concepts>
#include <type_traits>
#include <utility>

namespace menu {
   template<typename Signature>
   class Function {};

   template<typename R, typename... Args>
   class Function<R(Args...)> {
      typedef R(*callback_t)(const void*, Args&&...);
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
      Function(R(*fn)(Args...)) {
         using pointer_t = R(*)(Args...);

         ::new (get_memory()) pointer_t(fn);

         m_callback = [](const void* ptr, Args&&... args) {
            auto func = *static_cast<const pointer_t*>(ptr);
            return func(std::forward<Args>(args)...);
         };
      }

      template<typename Fn> requires std::same_as<std::invoke_result_t<Fn, Args...>, R>
      explicit Function(Fn& fn) {
         using pointer_t = void*;

         ::new (get_memory()) pointer_t(&fn);

         m_callback = [](const void* _ptr, Args&&... args) {
            auto ptr = *static_cast<const pointer_t*>(_ptr);
            auto& func = *static_cast<Fn*>(ptr);
            return static_cast<R>(func(std::forward<Args>(args)...));
         };
      }

      R operator()(Args&&... args) const {
         return m_callback(get_memory(), std::forward<Args>(args)...);
      }
   };   
} // namespace menu