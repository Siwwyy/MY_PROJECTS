cmake_minimum_required(VERSION "3.15.2")


project("")

add_executable("${PROJECT_NAME}" "main.cpp" )

install(TARGETS "${PROJECT_NAME}" DESTINATION bin)   #${CMAKE_INSTALL_PREFIX}/bin
install(FILES "main.cpp" DESTINATION src)			 #${CMAKE_INSTALL_PREFIX}/src

include(CTest)

add_test("first_app_test" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")

add_test("second_app_test" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}" "somekindofparameter")