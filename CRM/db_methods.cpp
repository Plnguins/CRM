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
 * Реализация функций для работы с СУБД
 */
#include "db_methods.h"

int db_methods::row_count = 0;

std::vector<boost::tuple<stock, laptop, provider>> db_methods::getStock(
    soci::session& sql, const int& offset, const int& limit) {
    std::vector<boost::tuple<stock, laptop, provider>> result;
    std::string query =
        "SELECT stock.*, laptop.*, provider.*, COUNT(*) OVER() FROM stock JOIN "
        "laptop ON laptop.id = stock.laptop JOIN provider ON provider.id = "
        "stock.source LIMIT " +
        std::to_string(limit) + " OFFSET " +
        std::to_string(offset * limit);  // Формируем запрос к СУБД
    soci::rowset<soci::row> rs = (sql.prepare << query);  // Подготавливаем его
    for (auto it = rs.begin(); it != rs.end(); it++) {  // Выполняем построчно
        const auto& row = *it;  // Текущая строка
        result.push_back(
            {stock(row.get<int>(0), row.get<int>(1), row.get<int>(2),
                   row.get<int>(3), row.get<int>(4), row.get<int>(5)),
             laptop(row.get<int>(6), row.get<std::string>(7),
                    row.get<double>(8), row.get<std::string>(9),
                    row.get<std::string>(10), row.get<std::string>(11),
                    row.get<int>(12), row.get<int>(13),
                    row.get<std::string>(14)),
             provider(row.get<int>(15),
                      row.get<std::string>(16))});  // Добавляем в результат
        db_methods::row_count =
            row.get<long long>(17);  // Запоминаем количество строк
    }
    return result;  // Возвращаем результат
}

std::vector<provider> db_methods::getProvider(soci::session& sql,
                                              const int& offset,
                                              const int& limit) {
    std::vector<provider> result;
    std::string query =
        "SELECT *, COUNT(*) OVER() FROM provider LIMIT " +
        std::to_string(limit) + " OFFSET " +
        std::to_string(offset * limit);  // Формируем запрос к СУБД
    soci::rowset<soci::row> rs = (sql.prepare << query);  // Подготавливаем его
    for (auto it = rs.begin(); it != rs.end(); it++) {  // Выполняем построчно
        const auto& row = *it;  // Текущая строка
        result.push_back(
            provider(row.get<int>(0),
                     row.get<std::string>(1)));  // Добавляем в результат
        db_methods::row_count =
            row.get<long long>(2);  // Запоминаем количество строк
    }
    return result;  // Возвращаем результат
}

std::vector<boost::tuple<deal, laptop, client, employee>> db_methods::getDeal(
    soci::session& sql, const int& offset, const int& limit) {
    std::vector<boost::tuple<deal, laptop, client, employee>> result;
    std::string query =
        "SELECT deal.*, laptop.*, client.*, employee.*, COUNT(*) OVER() FROM "
        "deal JOIN laptop ON laptop.id = deal.laptop JOIN client ON client.id "
        "= deal.client JOIN employee ON employee.id = deal.seller LIMIT " +
        std::to_string(limit) + " OFFSET " +
        std::to_string(offset * limit);  // Формируем запрос к СУБД
    soci::rowset<soci::row> rs = (sql.prepare << query);  // Подготавливаем его
    for (auto it = rs.begin(); it != rs.end(); it++) {  // Выполняем построчно
        const auto& row = *it;  // Текущая строка
        result.push_back(
            {deal(row.get<int>(0), row.get<int>(1), row.get<int>(2),
                  row.get<int>(3), row.get<std::string>(4),
                  row.get<boost::gregorian::date>(5), row.get<int>(6),
                  row.get<int>(7, 0), row.get<boost::gregorian::date>(8)),
             laptop(row.get<int>(9), row.get<std::string>(10),
                    row.get<double>(11), row.get<std::string>(12),
                    row.get<std::string>(13), row.get<std::string>(14),
                    row.get<int>(15), row.get<int>(16),
                    row.get<std::string>(17)),
             client(row.get<int>(18), row.get<std::string>(19),
                    row.get<std::string>(20), row.get<std::string>(21),
                    row.get<std::string>(22), row.get<std::string>(23),
                    row.get<std::string>(24), row.get<std::string>(25)),
             employee(row.get<int>(26), row.get<std::string>(27),
                      row.get<std::string>(28), row.get<std::string>(29),
                      row.get<std::string>(30),
                      row.get<std::string>(31))});  // Добавляем в результат
        db_methods::row_count =
            row.get<long long>(32);  // Запоминаем количество строк
    }
    return result;  // Возвращаем результат
}

std::vector<employee> db_methods::getEmployee(soci::session& sql,
                                              const int& offset,
                                              const int& limit) {
    std::vector<employee> result;
    std::string query =
        "SELECT *, COUNT(*) OVER() FROM employee LIMIT " +
        std::to_string(limit) + " OFFSET " +
        std::to_string(offset * limit);  // Формируем запрос к СУБД
    soci::rowset<soci::row> rs = (sql.prepare << query);  // Подготавливаем его
    for (auto it = rs.begin(); it != rs.end(); it++) {  // Выполняем построчно
        const auto& row = *it;  // Текущая строка
        result.push_back(employee(
            row.get<int>(0), row.get<std::string>(1), row.get<std::string>(2),
            row.get<std::string>(3), row.get<std::string>(4),
            row.get<std::string>(5)));  // Добавляем в результат
        db_methods::row_count =
            row.get<long long>(6);  // Запоминаем количество строк
    }
    return result;  // Возвращаем результат
}

std::vector<advertisement> db_methods::getAdvertisement(soci::session& sql,
                                                        const int& offset,
                                                        const int& limit) {
    std::vector<advertisement> result;
    std::string query =
        "SELECT *, COUNT(*) OVER() FROM advertisement LIMIT " +
        std::to_string(limit) + " OFFSET " +
        std::to_string(offset * limit);  // Формируем запрос к СУБД
    soci::rowset<soci::row> rs = (sql.prepare << query);  // Подготавливаем его
    for (auto it = rs.begin(); it != rs.end(); it++) {  // Выполняем построчно
        const auto& row = *it;  // Текущая строка
        result.push_back(advertisement(
            row.get<int>(0), row.get<std::string>(1), row.get<int>(2),
            row.get<std::string>(3)));  // Добавляем в результат
        db_methods::row_count =
            row.get<long long>(4);  // Запоминаем количество строк
    }
    return result;  // Возвращаем результат
}

std::vector<client> db_methods::getClient(soci::session& sql, const int& offset,
                                          const int& limit) {
    std::vector<client> result;
    std::string query =
        "SELECT *, COUNT(*) OVER() FROM client LIMIT " + std::to_string(limit) +
        " OFFSET " + std::to_string(offset * limit);  // Формируем запрос к СУБД
    soci::rowset<soci::row> rs = (sql.prepare << query);  // Подготавливаем его
    for (auto it = rs.begin(); it != rs.end(); it++) {  // Выполняем построчно
        const auto& row = *it;  // Текущая строка
        result.push_back(client(
            row.get<int>(0), row.get<std::string>(1), row.get<std::string>(2),
            row.get<std::string>(3), row.get<std::string>(4),
            row.get<std::string>(5), row.get<std::string>(6),
            row.get<std::string>(7)));  // Добавляем в результат
        db_methods::row_count =
            row.get<long long>(8);  // Запоминаем количество строк
    }
    return result;  // Возвращаем результат
}

void db_methods::deleteClient(soci::session& sql, const std::vector<int>& ids) {
    soci::transaction tr(sql);  // Открываем транзакцию
    std::string query =
        "DELETE FROM client WHERE id = :id";  // Формируем запрос к СУБД
    try {
        sql << query, soci::use(ids);
        tr.commit();
    } catch (soci::soci_error const& e) {
        tr.rollback();  // При исключении откатываем изменения
        throw e;
    }
}
void db_methods::newClient(soci::session& sql, const client& client) {
    std::string query =
        "INSERT INTO client(surname, name, patronymic, email, phone, sex, "
        "city) VALUES (:surname, :name, :patronymic, :email, :phone, :sex, "
        ":city)";  // Формируем запрос к СУБД
    sql << query, soci::use(client.surname, "surname"),
        soci::use(client.name, "name"),
        soci::use(client.patronymic, "patronymic"),
        soci::use(client.email, "email"), soci::use(client.phone, "phone"),
        soci::use(client.sex, "sex"), soci::use(client.city, "city");
}
