// Database methods for CRM application
// Copyright(C) 2022  Plnguins

// This program is free software : you can redistribute it and / or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.If not, see < https:  // www.gnu.org/licenses/>.
/*
 * Функции работы с СУБД
 */
#include "database-types/advertisement.h"
#include "database-types/client.h"
#include "database-types/deal.h"
#include "database-types/employee.h"
#include "database-types/laptop.h"
#include "database-types/provider.h"
#include "database-types/stock.h"
#include "db_pool.h"

std::vector<boost::tuple<stock, laptop, provider>> getStock(
    soci::session&, const int&,
    const int&);  // Функция получения данных о товарах на складе

std::vector<provider> getProvider(
    soci::session&, const int&,
    const int&);  // Функция получения данных о поставщиках

std::vector<boost::tuple<deal, laptop, client, employee>> getDeal(
    soci::session&, const int&,
    const int&);  // Функция получения данных о сделках

std::vector<employee> getEmployee(
    soci::session&, const int&,
    const int&);  // Функция получения данных о сотрудниках

std::vector<advertisement> getAdvertisement(
    soci::session&, const int&,
    const int&);  // Функция получения данных о рекламе

std::vector<client> getClient(
    soci::session&, const int&,
    const int&);  // Функция получения данных о клиентах
