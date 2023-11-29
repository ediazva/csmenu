#include <menu/function.hpp>
#include <cstdio>

#define EXECUTE(foo) do {\
   printf("Executing %s...\n", #foo); \
   foo; \
} while(0)

void a() {
   puts("Holaaaa");
}

int main() {
   menu::Function<void()> foo(a);
   menu::Function<void()> bar;
   // menu::Function<void()> bar = foo;         Esto debe provocar un error 
   bar = std::move(foo);
   EXECUTE(bar());
   // EXECUTE(foo());         ERROR

   return 0;
}