cmake_minimum_required(VERSION "3.15.2")


project("Cmake_First")

add_executable("${PROJECT_NAME}" "main.cpp" )

install(TARGETS "${PROJECT_NAME}" DESTINATION bin)   #${CMAKE_INSTALL_PREFIX}/bin
install(FILES "main.cpp" DESTINATION src)			#${CMAKE_INSTALL_PREFIX}/src


