if(MENU_TEST)
   set(BENCHMARK_DOWNLOAD_DEPENDENCIES off CACHE STRING "")
   set(BENCHMARK_ENABLE_TESTING off CACHE STRING "")

   add_subdirectory(./benchmark)
endif()