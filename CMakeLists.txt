cmake_minimum_required(VERSION 4.0)
project(ftxui_experiments_proj)

# FTXUI
include(FetchContent)
 
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v7.0.1  # Replace with a version, tag, or commit hash
)
 
FetchContent_MakeAvailable(ftxui)

add_executable(ftxui_experiments code/main.cpp)
target_link_libraries(ftxui_experiments
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)