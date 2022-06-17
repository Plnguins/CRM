# CMake script for building CRM folder
# Copyright (C) 2022  VadVergasov as part of Plnguins

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
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
qt_standard_project_setup()

add_executable(CRM "main.cpp")

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
