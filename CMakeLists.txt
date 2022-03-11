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
find_package(Qt6 REQUIRED COMPONENTS Test)

add_executable(PCPartPicker
    main.cpp
    # PC Part classes
    include/PC_Parts/CPU/cpu.h
    src/PC_Parts/CPU/cpu.cpp
    include/PC_Parts/CPU/amdcpu.h
    src/PC_Parts/CPU/amdcpu.cpp
    include/PC_Parts/CPU/intelcpu.h
    src/PC_Parts/CPU/intelcpu.cpp
    include/PC_Parts/GPU/gpu.h
    src/PC_Parts/GPU/gpu.cpp
    include/PC_Parts/GPU/amdgpu.h
    src/PC_Parts/GPU/amdgpu.cpp
    include/PC_Parts/GPU/intelgpu.h
    src/PC_Parts/GPU/intelgpu.cpp
    include/PC_Parts/GPU/nvidiagpu.h
    src/PC_Parts/GPU/nvidiagpu.cpp
    include/PC_Parts/Motherboard/motherboard.h
    src/PC_Parts/Motherboard/motherboard.cpp
    include/PC_Parts/RAM/ram.h
    src/PC_Parts/RAM/ram.cpp
    include/PC_Parts/Cooler/cooler.h
    src/PC_Parts/Cooler/cooler.cpp
    include/PC_Parts/Cooler/aio.h
    src/PC_Parts/Cooler/aio.cpp
    include/PC_Parts/Cooler/aircooler.h
    src/PC_Parts/Cooler/aircooler.cpp
    include/PC_Parts/PSU/psu.h
    src/PC_Parts/PSU/psu.cpp
    include/PC_Parts/Storage/storage.h
    src/PC_Parts/Storage/storage.cpp
    include/PC_Parts/Storage/satassd.h
    src/PC_Parts/Storage/satassd.cpp
    include/PC_Parts/Storage/hdd.h
    src/PC_Parts/Storage/hdd.cpp
    include/PC_Parts/Storage/m2ssd.h
    src/PC_Parts/Storage/m2ssd.cpp
    include/PC_Parts/Case/pccase.h
    src/PC_Parts/Case/pccase.cpp

    # Database classes
    include/Database/dataholder.h
    src/Database/dataholder.cpp
    include/Database/filewriter.h
    src/Database/filewriter.cpp
    include/Database/filereader.h
    src/Database/filereader.cpp

    # Logic classes
    include/Logic/compatibility.h
    src/Logic/compatibility.cpp
    include/Logic/specbuilder.h
    src/Logic/specbuilder.cpp

    # Test classes
    Test/include/dbtests.h
    Test/src/dbtests.cpp
    Test/include/specbuildertests.h
    Test/src/specbuildertests.cpp
)


target_link_libraries(PCPartPicker Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Concurrent Qt6::Test)
