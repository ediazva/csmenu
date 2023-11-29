#include <menu/menu.hpp>

void menu_opcion1() {
   menu::titulo("OPCION 1");
}

void menu_opcion2() {
   menu::titulo("OPCION 2");

}

void menu_opcion3() {
   menu::titulo("OPCION 3");

}

int main() {
   menu::Menu main_menu(
      menu::make_item("Opcion 1", menu_opcion1),
      menu::make_item("Opcion 2", menu_opcion2),
      menu::make_item("Opcion 3", menu_opcion3)
   );

   main_menu.loop("MAIN MENU");
 
   return 0;
}