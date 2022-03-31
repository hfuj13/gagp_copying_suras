cmake_minimum_required(VERSION 3.18)
project(cgaframework CXX)
#add_definitions("-g -O2 -Wall -std=c++17")
add_definitions("-g -Wall -Wno-sign-compare -std=c++17")
add_executable(ga
cgaframe.cpp
frame/FrSubject.cpp
Creator.cpp
frame/FrSubjView.cpp
frame/FrRandom.cpp
)

include_directories(
.
${PROJECT_SOURCE_DIR}/frame
)

#target_compile_options(ga PUBLIC -Wall -Werror -Wpedantic -Wno-error=unknown-pragmas)
#target_compile_features(ga PUBLIC cxx_std_17)
