#include "menu.hpp"

using namespace std;

namespace menu {
   void titulo(const string_view& title) {
      ECHO_HIGHLIGHT("{0:*<{1}}\n*{0: <5}{2}{0: <5}*\n{0:*<{1}}\n", "", title.size()+12, title);
   }

   void limpiar() {
      (void)system("clear");
   }

   void ignorar_linea() {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
   }

   static void pausar() {
      ECHO_INFO("[!] Presiona alguna tecla para volver...\n");
      ignorar_linea();
      std::getchar();
   }

   Menu::Menu(initializer_list<menu_t> menus) :
      m_menus{menus.begin(), menus.end()} {}

   void Menu::loop(const string_view& main_title) {
      char opcion{};
      const char exit_option = 'a' + m_menus.size();
      while(true) {
         menu_principal(main_title);
         ECHO_INFO("[?] Opción: ");
         if(safe_cin(opcion)) {
            if(opcion == exit_option)
               break;
               
            safe_execute(opcion);
         }
      }
   }
   
   void Menu::safe_execute(char option) {
      const int ioption = option - 'a';

      if(ioption >= 0 && ioption < m_menus.size()) {
         limpiar();
         m_menus.at(ioption).second();
         pausar();
      }
   }

   void Menu::menu_principal(const string_view& main_title) {
      limpiar();
      titulo(main_title);
      int i = 0;
      for(; i < m_menus.size(); ++i)
         ECHO("{}) {}\n", (char)('a'+i), m_menus[i].first);
   
      ECHO("{}) Salir.\n", (char)('a'+i));
   }
} // namespace menu