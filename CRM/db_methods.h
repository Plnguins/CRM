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
#pragma once

#include <openssl/evp.h>
#include <openssl/sha.h>

#include <QObject>
#include <iomanip>
#include <sstream>

#include "database-types/advertisement.h"
#include "database-types/client.h"
#include "database-types/deal.h"
#include "database-types/employee.h"
#include "database-types/laptop.h"
#include "database-types/provider.h"
#include "database-types/stock.h"
#include "db_pool.h"

class db_methods {
   public:
    static std::string hashPassword(const std::string& password);

    static std::vector<boost::tuple<stock, laptop, provider>> getStock(
        soci::session&, const int&,
        const int&);  // Функция получения данных о товарах на складе

    static std::vector<provider> getProvider(
        soci::session&, const int&,
        const int&);  // Функция получения данных о поставщиках

    static std::vector<boost::tuple<deal, laptop, client, employee>> getDeal(
        soci::session&, const int&,
        const int&);  // Функция получения данных о сделках

    static std::vector<employee> getEmployee(
        soci::session&, const int&,
        const int&);  // Функция получения данных о сотрудниках

    static std::vector<advertisement> getAdvertisement(
        soci::session&, const int&,
        const int&);  // Функция получения данных о рекламе

    static std::vector<client> getClient(
        soci::session&, const int&,
        const int&);  // Функция получения данных о клиентах

    static std::vector<laptop> getLaptop(
        soci::session&, const int&,
        const int&);  // Функция получение данных о ноутбуках

    static void deleteClient(
        soci::session&,
        const std::vector<int>&);  // Функция удаления клиентов по ID

    static client getClient(
        soci::session&,
        const int&);  // Функция получения данных о клиенте по ID

    static void updateClient(
        soci::session&, const client&);  // Функция обновления данных о клиенте

    static void newClient(soci::session&,
                          const client&);  // Функция добавления клиента

    static void deleteProvider(
        soci::session&,
        const std::vector<int>&);  // Функция удаления поставщиков по ID

    static provider getProvider(
        soci::session&,
        const int&);  // Функция получения данных о поставщике по ID

    static void updateProvider(
        soci::session&,
        const provider&);  // Функция обновления данных о поставщике

    static void newProvider(soci::session&,
                            const provider&);  // Функция добавления поставщика

    static void deleteEmployee(
        soci::session&,
        const std::vector<int>&);  // Функция удаления сотрудников по ID

    static employee getEmployee(
        soci::session&,
        const int&);  // Функция получения данных о сотруднике по ID

    static void updateEmployee(
        soci::session&,
        const employee&);  // Функция обновления данных о сотруднике

    static int newEmployee(soci::session&,
                           const employee&);  // Функция добавления сотрудника

    static void deleteStock(
        soci::session&,
        const std::vector<int>&);  // Функция удаления товаров на складе по ID

    static void newStock(soci::session&,
                         const stock&);  // Функция добавления на склад

    static void deleteAd(
        soci::session&,
        const std::vector<int>&);  // Функция удаления рекламы по ID

    static advertisement getAd(
        soci::session&,
        const int&);  // Функция получения данны о рекламе по ID

    static void updateAd(
        soci::session&,
        const advertisement&);  // Функция обновления данных о рекламы

    static void newAd(soci::session&,
                      const advertisement&);  // Функция добавления рекламы

    static void deleteDeal(
        soci::session&,
        const std::vector<int>&);  // Функция удаления сделок по ID

    static deal getDeal(soci::session&,
                        const int&);  // Функция получения сделки по ID

    static void updateDeal(soci::session&,
                           const deal&);  // Функция обновления сделки

    static void newDeal(soci::session&,
                        const deal&);  // Функция добавления сделки

    static void deleteLaptop(
        soci::session&,
        const std::vector<int>&);  // Функция удаления ноутбуков по ID

    static laptop getLaptop(soci::session&,
                            const int&);  // Функций получения ноутбука по ID

    static void updateLaptop(
        soci::session&, const laptop&);  // Функция обновления данных о ноутбуке

    static void newLaptop(soci::session&,
                          const laptop&);  // Функция добавления ноутбука

    static std::vector<employee> getSeller(
        soci::session&);  // Функция получения сотрудников продавцов

    static int row_count;
};
