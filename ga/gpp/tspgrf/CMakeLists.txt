cmake_minimum_required(VERSION 3.18)
project(tspgrf CXX)
#add_definitions("-g -O2 -Wall -std=c++17")
add_definitions("-g -Wall -Wno-sign-compare -std=c++17")
add_executable(ga
Creator.cpp
TspApp.cpp
ViewTsp.cpp
cgaframe.cpp
frame/FrSubject.cpp
frame/FrRandom.cpp
frame/FrSubjView.cpp
)

include_directories(
.
${PROJECT_SOURCE_DIR}/frame
)

#target_compile_options(ga PUBLIC -Wall -Werror -Wpedantic -Wno-error=unknown-pragmas)
#target_compile_features(ga PUBLIC cxx_std_17)
