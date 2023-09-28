#pragma once
#include <iostream>
#include <vector>
#include <string_view>
#include <fmt/format.h>
#include <fmt/color.h>

#define ECHO_HIGHLIGHT(...) fmt::print(fmt::fg(fmt::color::yellow), __VA_ARGS__)
#define ECHO_INFO(...) fmt::print(fmt::fg(fmt::color::dark_cyan), __VA_ARGS__)
#define ECHO_ERROR(...) fmt::print(fmt::fg(fmt::color::red), "[x] " __VA_ARGS__)
#define ECHO(...) fmt::print(__VA_ARGS__)

namespace menu {
   void titulo(const std::string_view& title);
   void limpiar();
   void ignorar_linea();
   template<typename T> requires requires (T t) {std::cin >> t;}
   bool safe_cin(T& t) {
      if(!(cin >> t)) {
         cin.clear();
         return false;
      }

      return true;
   }

   template<typename T, typename... Args> requires requires (T t) {menu::safe_cin(t);}
   T force_input(const std::string_view& format, Args&&... args) {
      T t;
      while(true) {
         ECHO_INFO(format, std::forward<Args>(args)...);
         if(!safe_cin(t))
            ECHO_ERROR("Ingrese un valor valido.\n"), ignorar_linea();
         else
            break;
      }

      return t;
   }
   
   /*
         *****************************
         *           TITULO          *
         *****************************
         a) Opción 1
         b) Opción 2
         c) Opcion 3
         d) Opción 4
         e) Salir.
   */

   class Menu {
   public:
      //             Label       Delegate
      typedef std::pair<std::string_view, std::function<void()>> menu_t;
      typedef std::vector<menu_t> menulist_t;
      Menu(std::initializer_list<menu_t> menus);
      void loop(const std::string_view& main_title);
   private:
      void safe_execute(char option);
      void menu_principal(const std::string_view& main_title);

      menulist_t m_menus;
   };
} // namespace menu