find_package(PkgConfig REQUIRED)
pkg_check_modules(FMTLIB REQUIRED fmt)

add_library(menu-lib STATIC
   menu/menu.hpp
   menu/menu.cc)
target_include_directories(menu-lib PUBLIC ${PROJECT_SOURCE_DIR}/src ${FMTLIB_INCLUDE_DIRS})
target_link_libraries(menu-lib ${FMTLIB_LIBRARIES})