# CMake script for building project
# Copyright (C) 2022 Plnguins

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
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(Boost_NO_WARN_NEW_VERSIONS 1)

find_package(OpenSSL REQUIRED)

find_package(Boost REQUIRED)
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

file(GLOB_RECURSE SRC "CRM/*.h" "CRM/*.cpp" "CRM/*.ui" "resources/*.qrc")

set(MACOSX_BUNDLE_ICON_FILE main.icns)
SET(MACOSX_BUNDLE_EXECUTABLE_NAME CRM)
SET(MACOSX_BUNDLE_BUNDLE_NAME CRM)

add_executable(CRM WIN32 MACOSX_BUNDLE ${SRC} ${resources})
set_target_properties(CRM PROPERTIES AUTOMOC TRUE AUTOUIC TRUE AUTORCC TRUE)

target_link_libraries(CRM ${Boost_LIBRARIES})

target_include_directories(CRM PRIVATE ${SOCI_BINARY_DIR}/include)

target_link_libraries(CRM PRIVATE soci_core soci_postgresql)

target_link_libraries(CRM PRIVATE Qt6::Core Qt6::Widgets Qt::Gui)

target_link_libraries(CRM PRIVATE OpenSSL::SSL)

set_target_properties(CRM PROPERTIES WIN32_EXECUTABLE ON MACOSX_BUNDLE ON)

get_target_property(QtCore_LOCATION Qt6::Core LOCATION)
get_filename_component(QT_DLL_DIR ${QtCore_LOCATION} PATH)

IF(WIN32)
    string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
    add_custom_command(TARGET CRM POST_BUILD
        COMMAND ${QT_DLL_DIR}/windeployqt.exe ${CMAKE_BINARY_DIR}/bin/CRM.exe --${BUILD_TYPE}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Copying libraries")
    add_custom_command(TARGET CRM POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/bin ${CMAKE_SOURCE_DIR}/packages/com.pinguins.crm/data)
ENDIF()

IF(APPLE)
    add_custom_command(TARGET CRM POST_BUILD
        COMMAND ${QT6_INSTALL_PREFIX}/bin/macdeployqt CRM.app -dmg
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        COMMENT "Copying libraries")
    add_custom_command(TARGET CRM POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/bin/CRM.app ${CMAKE_SOURCE_DIR}/packages/com.pinguins.crm/data)
ENDIF()

add_custom_command(TARGET CRM POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/LICENSE.txt ${CMAKE_SOURCE_DIR}/packages/com.pinguins.crm/meta/LICENSE.txt)
