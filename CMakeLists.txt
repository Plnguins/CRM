# CMake script for building project
# Copyright (C) 2022  Plnguins

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.

# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
cmake_minimum_required(VERSION 3.16)

project("CRM")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.79.0)
message(STATUS "Boost version: ${Boost_VERSION}")

find_package(PostgreSQL REQUIRED)
include_directories(SYSTEM ${PostgreSQL_INCLUDE_DIRS})

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

set(SOCI_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/soci)

option(SOCI_CXX11 "Build to the C++11 standard" ON)
option(SOCI_ASAN "" OFF)
option(WITH_BOOST "" ON)
option(SOCI_TESTS "" OFF)
option(SOCI_SHARED "" ON)
option(SOCI_STATIC "" OFF)

option(WITH_POSTGRESQL "Build PostgreSQL backend" ON)
option(WITH_ORACLE "" OFF)
option(WITH_ODBC "" OFF)
option(WITH_SQLITE3 "" OFF)
option(WITH_FIREBIRD "" OFF)
option(WITH_DB2 "" OFF)
option(WITH_MYSQL "" OFF)
option(SOCI_EMPTY "" OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/soci ${SOCI_BINARY_DIR})

IF(WIN32)
    set(resources "${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.rc")
ENDIF()

file(GLOB SRC "CRM/*.h" "CRM/*.cpp" "CRM/*.ui" "resources/*.qrc")

set(AUTO_RCC ON)
add_executable(CRM ${SRC} ${resources})
set_target_properties(CRM PROPERTIES AUTOMOC TRUE AUTOUIC TRUE AUTORCC TRUE)

target_link_libraries(CRM ${Boost_LIBRARIES})

target_include_directories(CRM PRIVATE ${SOCI_BINARY_DIR}/include)

target_link_libraries(CRM PRIVATE soci_core soci_postgresql)

target_link_libraries(CRM PRIVATE Qt6::Core Qt6::Widgets Qt::Gui)

set_target_properties(CRM PROPERTIES WIN32_EXECUTABLE ON MACOSX_BUNDLE ON)

get_target_property(QtCore_LOCATION Qt6::Core LOCATION)
get_filename_component(QT_DLL_DIR ${QtCore_LOCATION} PATH)

IF(WIN32)
    add_custom_command(TARGET CRM POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::Core> $<TARGET_FILE_DIR:CRM>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::Gui> $<TARGET_FILE_DIR:CRM>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::Widgets> $<TARGET_FILE_DIR:CRM>
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${QT6_INSTALL_PREFIX}/plugins/platforms $<TARGET_FILE_DIR:CRM>/platforms
    )
ENDIF()

set_target_properties(CRM PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
