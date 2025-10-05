# CMakeList.txt : CMake project for QuackEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

#turn off RTTI
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/GR->$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-fno-rtti>)

project(QuackEngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)          # request C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # require it
set(CMAKE_CXX_EXTENSIONS OFF)       # optional: disable compiler-specific extensions

project (QuackEngine)

find_package(glm CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(imgui CONFIG REQUIRED)


file(GLOB_RECURSE SOURCES "SourceCode/*.cpp" "SourceCode/*.h")


# Add source to this project's executable.
add_executable (QuackEngine ${SOURCES})

target_link_libraries(QuackEngine PRIVATE
  glm::glm  
  SDL3::SDL3
  glad::glad
  OpenGL::GL
  imgui::imgui)