cmake_minimum_required(VERSION 3.10)
project(MiniLog C CXX)

# 设置运行库一致（防止链接冲突）
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# 标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(third_party/googletest)
add_subdirectory(src)
add_subdirectory(test)
