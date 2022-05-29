# CMake script for building project
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
cmake_minimum_required (VERSION 3.22)

project ("CRM")

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.79.0)
message(STATUS "Boost version: ${Boost_VERSION}")

find_package(PostgreSQL REQUIRED)
include_directories(SYSTEM ${PostgreSQL_INCLUDE_DIRS})

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

set(SOCI_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/soci)

option(SOCI_CXX11 "Build to the C++11 standard" ON)
option(SOCI_ASAN "" ON)
option(WITH_BOOST "" ON)
option(SOCI_TESTS "" OFF)

option(WITH_POSTGRESQL "Build PostgreSQL backend" ON)
option(WITH_ORACLE "" OFF)
option(WITH_ODBC "" OFF)
option(WITH_SQLITE3 "" OFF)
option(WITH_FIREBIRD "" OFF)
option(WITH_DB2 "" OFF)
option(WITH_MYSQL "" OFF)
option(SOCI_EMPTY "" OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/soci ${SOCI_BINARY_DIR})

add_subdirectory ("CRM")
