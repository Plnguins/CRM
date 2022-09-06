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
IF(APPLE)
    cmake_minimum_required(VERSION 3.23) # Для сборки под macOS необходимо использовать версию CMake не ниже 3.23
ELSE()
    cmake_minimum_required(VERSION 3.16)
ENDIF()

project("CRM" CXX) # Название проекта и язык

# Указываем куда будут помещены собраные файлы
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Указываем, чтобы Boost не предупреждал о старой версии CMake, которая не знает последнюю версию Boost
set(Boost_NO_WARN_NEW_VERSIONS 1)

# Техническая переменная с типом сборке в нижнем регистре понадобится далее
string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)

# Необходима OpenSSL для криптографии
find_package(OpenSSL REQUIRED)

# Необходима Boost для работы с СУБД
find_package(Boost REQUIRED)
message(STATUS "Boost version: ${Boost_VERSION}")

# Необходим PostgreSQL
find_package(PostgreSQL REQUIRED)
include_directories(SYSTEM ${PostgreSQL_INCLUDE_DIRS})

# Необходим Qt для работы с графическим интерфейсом
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui LinguistTools)

# Включаем папки с Boost
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

# Указываем путь к SOCI
set(SOCI_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/soci)

# Опции для сборки SOCI
option(SOCI_CXX11 "Build to the C++11 standard" ON)
option(WITH_BOOST "Use Boost" ON)
option(SOCI_TESTS "Don't build tests" OFF)
option(SOCI_SHARED "Use shared lib" ON)
option(SOCI_STATIC "Don't use static lib" OFF)

# Какие СУБД нужны в SOCI
option(WITH_POSTGRESQL "Build PostgreSQL backend" ON)
option(WITH_ORACLE "" OFF)
option(WITH_ODBC "" OFF)
option(WITH_SQLITE3 "" OFF)
option(WITH_FIREBIRD "" OFF)
option(WITH_DB2 "" OFF)
option(WITH_MYSQL "" OFF)
option(SOCI_EMPTY "" OFF)

# Добавляем папку с SOCI
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/soci ${SOCI_BINARY_DIR})

# Использование ресурсов на Windows
IF(WIN32)
    set(resources "${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.rc")
ENDIF()

# Все исходные файлы приложения
file(GLOB_RECURSE SRC "CRM/*.h" "CRM/*.cpp" "CRM/*.ui" "resources/*.qrc")

# MacOS спецефичные файлы
set(MACOSX_BUNDLE_ICON_FILE main.icns)
set(MACOSX_BUNDLE_EXECUTABLE_NAME CRM)
set(MACOSX_BUNDLE_BUNDLE_NAME CRM)
set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/main.icns")
set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# Добавления цели сборки в зависимости от платформы
IF(WIN32)
    add_executable(CRM WIN32 ${SRC} ${resources})
ELSEIF(APPLE)
    add_executable(CRM MACOSX_BUNDLE ${app_icon_macos} ${SRC} ${resources})
ELSE()
    add_executable(CRM ${SRC} ${resources})
ENDIF()

# Файлы перевода, их обновление, сборка и добавление в сборку
qt_add_lupdate(CRM TS_FILES ${CMAKE_SOURCE_DIR}/resources/translation/crm_ru.ts ${CMAKE_SOURCE_DIR}/resources/translation/crm_en.ts SOURCES ${SRC} INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/CRM OPTIONS "-noobsolete")
qt_add_lrelease(CRM TS_FILES ${CMAKE_SOURCE_DIR}/resources/translation/crm_ru.ts ${CMAKE_SOURCE_DIR}/resources/translation/crm_en.ts QM_FILES_OUTPUT_VARIABLE qm_files)
qt_add_resources(CRM "translation" PREFIX "/i18n" BASE "${CMAKE_CURRENT_BINARY_DIR}" FILES "${qm_files}")

# Автоматическое преобразование форм в код, добавление ресурсов в сборку
set_target_properties(CRM PROPERTIES AUTOMOC TRUE AUTOUIC TRUE AUTORCC TRUE)

# Линковка всех библиотек к цели сборки
target_link_libraries(CRM ${Boost_LIBRARIES})
target_include_directories(CRM PRIVATE ${SOCI_BINARY_DIR}/include)
target_link_libraries(CRM PRIVATE soci_core soci_postgresql)
target_link_libraries(CRM PRIVATE Qt6::Core Qt6::Widgets Qt::Gui)
target_link_libraries(CRM PRIVATE OpenSSL::SSL)

# Дополнительные опции для сборки под разными платформами
set_target_properties(CRM PROPERTIES WIN32_EXECUTABLE ON MACOSX_BUNDLE ON)

# Дополнительные переменные для Qt
get_target_property(QtCore_LOCATION Qt6::Core LOCATION)
get_filename_component(QT_DLL_DIR ${QtCore_LOCATION} PATH)

IF(WIN32)
    # Копирование всех dll в папку сборки
    add_custom_command(TARGET CRM POST_BUILD
        COMMAND ${QT_DLL_DIR}/windeployqt.exe ${CMAKE_BINARY_DIR}/bin/CRM.exe --${BUILD_TYPE}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Copying libraries")

    # Копирование всей сборки в папку для установщика
    add_custom_command(TARGET CRM POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/bin ${CMAKE_SOURCE_DIR}/packages/com.pinguins.crm/data)
ENDIF()

IF(APPLE)
    # Копирование dylib в папку сборки и создание dmg образа
    add_custom_command(TARGET CRM POST_BUILD
        COMMAND ${QT6_INSTALL_PREFIX}/bin/macdeployqt CRM.app -dmg
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        COMMENT "Creating dmg")
ENDIF()

# Копирование лицензии в папку для установщика
add_custom_command(TARGET CRM POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/LICENSE.txt ${CMAKE_SOURCE_DIR}/packages/com.pinguins.crm/meta/LICENSE.txt)
