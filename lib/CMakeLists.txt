configure_file(CMakeLists.txt.in
        spdlog-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/lib/spdlog-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/lib/spdlog-download )

# C++ 14 version
set(CMAKE_CXX_STANDARD 14)
