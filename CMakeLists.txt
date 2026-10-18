cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)
project(homework01)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE Angle)
add_library(Angle src/Angle.cpp include/Angle.hpp)
add_library(Angle-Shared SHARED include/Angle.hpp src/Angle.cpp)
install(
    TARGETS main Angle Angle-Shared
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
       ) 



