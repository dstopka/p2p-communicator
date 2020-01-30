cmake_minimum_required(VERSION 3.5)

project(oop_2019_komunikator_p2p LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
        src/Controller.cpp
        src/Server.cpp
        src/Conversation.cpp
        src/Connection.cpp
        src/Database.cpp
        src/Message.cpp
        src/File.cpp
)

set(HEADERS
        include/Controller.hpp
        include/Server.hpp
        include/Conversation.hpp
        include/Connection.hpp
        include/Database.hpp
        include/Message.hpp
        include/File.hpp
)

set( RESOURCES
        qml.qrc
)
# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Core Quick Network Sql REQUIRED)


if(ANDROID)
        add_library(oop_2019_komunikator_p2p SHARED
                ${SOURCES}
                ${HEADERS}
                ${RESOURCES}
        )
else()
        add_library(oop_2019_komunikator_p2p_lib ${HEADERS} ${SOURCES})
        target_include_directories(oop_2019_komunikator_p2p_lib PUBLIC include)

        add_executable(oop_2019_komunikator_p2p src/main.cpp
         ${RESOURCES}
         )
        #target_link_libraries(oop_2019_komunikator_p2p oop_2019_komunikator_p2p_lib)
endif()


target_compile_definitions(oop_2019_komunikator_p2p_lib
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(oop_2019_komunikator_p2p_lib
        PRIVATE Qt5::Core Qt5::Quick Qt5::Network Qt5::Sql)

target_compile_definitions(oop_2019_komunikator_p2p
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(oop_2019_komunikator_p2p
        PRIVATE Qt5::Core Qt5::Quick Qt5::Network Qt5::Sql
        oop_2019_komunikator_p2p_lib)



#add_subdirectory(test)
