set(GOOGLETEST ../googletest)

include_directories(${GOOGLETEST}/googletest/include ..)
link_directories(${GOOGLETEST}/build/lib)

set(TEST_HEADERS include/TestIncludes.h)
set(TEST_SOURCES src/ConnectionTest.cpp src/setup.cpp src/utils.cpp src/ControllerTest.cpp)

add_executable(oop_2019_komunikator_p2p_test ${TEST_HEADERS} ${TEST_SOURCES})
target_include_directories(oop_2019_komunikator_p2p_test PUBLIC include)
target_link_libraries(oop_2019_komunikator_p2p_test oop_2019_komunikator_p2p_lib gtest pthread Qt5::Core Qt5::Quick Qt5::Network Qt5::Test)

