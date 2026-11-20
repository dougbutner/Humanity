add_contract(fractal.perm fractal.perm ${CMAKE_CURRENT_SOURCE_DIR}/src/fractal_perms.cpp)

target_include_directories(fractal.perm PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_options(fractal.perm PUBLIC -Oz)

set_target_properties(fractal.perm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
