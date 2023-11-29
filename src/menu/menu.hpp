#pragma once
#include "function.hpp"

#include <iostream>
#include <concepts>
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
      if(!(std::cin >> t)) {
         std::cin.clear();
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
   
   //                       Label         Delegate
   typedef std::pair<std::string_view, Function<void()>> MenuItem;
   inline MenuItem make_item(const std::string_view& label, Function<void()>&& f) {
      return make_pair(label, std::move(f));
   }
   template<typename T>
   concept is_item_t = std::same_as<T, MenuItem>; 
   
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
      typedef std::vector<MenuItem> ItemList;
      // Usando T&& lo que hacemos es una referencia universal:
      //                      T se convierte en:
      // Lvalue -> Lvalue        T&
      // Rvalue -> Rvalue        T        Aprovechando esto usamos un concepto que solo permite usar tipos T, no T&
      template<is_item_t... T>
      Menu(T&&... items) {
         (m_menus.emplace_back(std::forward<T>(items)),...);
      }
      void loop(const std::string_view& main_title);
   private:
      void safe_execute(char option);
      void menu_principal(const std::string_view& main_title);

      ItemList m_menus;
   };
} // namespace menu