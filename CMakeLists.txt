cmake_minimum_required(VERSION 3.10.0)
project(mqtt VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Hier zijn de juiste paden ('src/' en 'include/') toegevoegd aan jouw bestandenlijst
add_executable(mqtt 
    main.cpp
    src/mqttHandler.cpp
    include/mqttHandler.h
    src/digitalSwitch.cpp
    include/digitalSwitch.h
    src/DHT11Sensor.cpp
    include/DHT11Sensor.h
    )

find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIOD REQUIRED IMPORTED_TARGET libgpiod>=2.0)

find_package(PahoMqttCpp REQUIRED)

# Zorg dat CMake ook de 'include' map scant voor headers
target_include_directories(mqtt PRIVATE
    ${GPIOD_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(mqtt PRIVATE
    PahoMqttCpp::paho-mqttpp3
    PkgConfig::GPIOD
)