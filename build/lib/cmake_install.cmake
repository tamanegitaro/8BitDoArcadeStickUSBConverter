# Install script for directory: C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/lib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/GP2040-CE")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/ADS1219/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/ADS1256/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/AnimationStation/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/CRC32/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/FlashPROM/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/httpd/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/lwip-port/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/nanopb/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/NeoPico/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/OneBitDisplay/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/PicoPeripherals/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/PlayerLEDs/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/rndis/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/WiiExtension/cmake_install.cmake")
  include("C:/Raspberrypi_Pico/GP2040-CE-0.7.10_USB_Convert/GP2040-CE/build/lib/SNESpad/cmake_install.cmake")

endif()

