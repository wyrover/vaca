# Vaca - Visual Application Components Abstraction
# Copyright (c) 2005-2010 David Capello
# All rights reserved.

# Fix to compile gtest with VC11 (2012)
if (MSVC_VERSION EQUAL 1700)
  add_definitions(-D_VARIADIC_MAX=10)
endif()

include_directories(.)
add_library(gtest STATIC gtest/gtest-all.cc)
add_library(gtest_main STATIC gtest/gtest_main.cc)
target_link_libraries(gtest_main gtest)

function(add_vaca_test name)
  add_executable(${name} ${name}.cpp)

  set_target_properties(${name} PROPERTIES
    COMPILE_FLAGS "${common_flags}")

  target_link_libraries(${name} gtest_main Vaca ${win32_libs})
endfunction(add_vaca_test)

add_vaca_test(test_bind)
add_vaca_test(test_handle)
add_vaca_test(test_image)
add_vaca_test(test_menu)
add_vaca_test(test_pen)
add_vaca_test(test_point)
add_vaca_test(test_rect)
add_vaca_test(test_region)
add_vaca_test(test_sharedptr)
add_vaca_test(test_signal)
add_vaca_test(test_size)
add_vaca_test(test_string)
add_vaca_test(test_tab)
add_vaca_test(test_thread)
add_vaca_test(test_widget)

# After building the last test
add_custom_command(TARGET test_widget
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/run_all.sh ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Copying run_all.sh to tests binary directory")
