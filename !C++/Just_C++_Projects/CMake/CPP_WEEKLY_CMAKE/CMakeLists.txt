cmake_minimum_required(VERSION "3.15.2")

project("")

if(MSVC)
add_compile_options(/W4)
else()
add_compile_options(-Wall -Wextra -Wpedantic)	#warnings etc.
endif()


add_executable(intro main.cpp)
target_compile_features(intro PRIVATE cxx_lambda_init_captures)  #specifically need CPP lambda


