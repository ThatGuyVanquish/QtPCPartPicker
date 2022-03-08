cmake_minimum_required(VERSION 3.14)

project(PCPartPicker LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_ALGORITHM_LIBRARY ON)
set(Boost_INCLUDE_DIRS ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Concurrent REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Concurrent REQUIRED)

add_executable(PCPartPicker
    main.cpp
    CPU.h
    CPU.cpp
    amdCPU.h
    amdCPU.cpp
    intelCPU.h
    intelCPU.cpp
    GPU.h
    GPU.cpp
    amdGPU.h
    amdGPU.cpp
    intelGPU.h
    intelGPU.cpp
    nvidiaGPU.h
    nvidiaGPU.cpp
    motherboard.h
    motherboard.cpp
    RAM.h
    RAM.cpp
    cooler.h
    cooler.cpp
    AIO.h
    AIO.cpp
    airCooler.h
    airCooler.cpp
    pcCase.h
    pcCase.cpp
    storage.h
    storage.cpp
    sataSSD.h
    sataSSD.cpp
    hdd.h
    hdd.cpp
    m2SSD.h
    m2SSD.cpp
    dataholder.h
    dataholder.cpp
    compatibility.h
    compatibility.cpp
    fileWriter.h
    fileWriter.cpp
    filereader.h
    filereader.cpp
)


target_link_libraries(PCPartPicker Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Concurrent)
