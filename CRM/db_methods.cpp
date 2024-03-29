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

std::string db_methods::hashPassword(const std::string& password) {
    // Encrypting and hashing password using PBKDF2 algorithm and hashing using
    // sha512, salt is static, iterations is 4096, result length is 128
    const unsigned int key_length = 128;
    unsigned char result[key_length];
    memset(result, 0, key_length * sizeof(unsigned char));
    unsigned char salt = 0;
    PKCS5_PBKDF2_HMAC(password.c_str(), password.size() * sizeof(password[0]),
                      &salt, sizeof(salt), 4096, EVP_sha512(),
                      key_length * sizeof(unsigned char), result);
    std::stringstream output;
    for (size_t i = 0; i < key_length; i++) {
        output << std::setw(sizeof(unsigned char) * 2) << std::setfill('0')
               << std::hex << static_cast<unsigned short>(result[i]);
    }
    return output.str();
}

std::vector<boost::tuple<stock, laptop, provider>> db_methods::getStock(
    soci::session& sql, const int& offset, const int& limit) {
    std::vector<boost::tuple<stock, laptop, provider>> result;
    std::string query =
        "SELECT stock.*, laptop.*, provider.*, COUNT(*) OVER() FROM stock JOIN "
        "laptop ON laptop.id = stock.laptop JOIN provider ON provider.id = "
        "stock.source ORDER BY stock.id LIMIT " +
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
        "SELECT *, COUNT(*) OVER() FROM provider ORDER BY id LIMIT " +
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
        "= deal.client JOIN employee ON employee.id = deal.seller ORDER BY "
        "deal.id LIMIT " +
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
        "SELECT *, COUNT(*) OVER() FROM employee ORDER BY id LIMIT " +
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
        "SELECT *, COUNT(*) OVER() FROM advertisement ORDER BY id LIMIT " +
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
        "SELECT *, COUNT(*) OVER() FROM client ORDER BY id LIMIT " +
        std::to_string(limit) + " OFFSET " +
        std::to_string(offset * limit);  // Формируем запрос к СУБД
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

std::vector<laptop> db_methods::getLaptop(soci::session& sql, const int& offset,
                                          const int& limit) {
    std::vector<laptop> result;
    std::string query =
        "SELECT *, COUNT(*) OVER() FROM laptop ORDER BY id LIMIT " +
        std::to_string(limit) + " OFFSET " +
        std::to_string(offset * limit);  // Формируем запрос к СУБД
    soci::rowset<soci::row> rs = (sql.prepare << query);  // Подготавливаем его
    for (auto it = rs.begin(); it != rs.end(); it++) {  // Выполняем построчно
        const auto& row = *it;  // Текущая строка
        result.push_back(
            laptop(row.get<int>(0), row.get<std::string>(1), row.get<double>(2),
                   row.get<std::string>(3), row.get<std::string>(4),
                   row.get<std::string>(5), row.get<int>(6), row.get<int>(7),
                   row.get<std::string>(8)));  // Добавляем в результат
        db_methods::row_count =
            row.get<long long>(9);  // Запоминаем количество строк
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

client db_methods::getClient(soci::session& sql, const int& id) {
    boost::optional<client> result;
    std::string query =
        "SELECT * FROM client WHERE id = :id";  // Формируем запрос к СУБД
    sql << query, soci::into(result), soci::use(id, "id");  // Выполняем запрос
    if (result) {
        return result.get();
    }
    throw std::runtime_error(
        QObject::tr("База данных не вернула значение").toStdString());
}

void db_methods::updateClient(soci::session& sql, const client& client) {
    std::string query =
        "UPDATE client SET name = :name, surname = :surname, patronymic = "
        ":patronymic, phone = :phone, email = :email, sex = :sex, city = :city "
        "WHERE id = :id";  // Формируем запрос к СУБД
    sql << query, soci::use(client.name, "name"),
        soci::use(client.surname, "surname"),
        soci::use(client.patronymic, "patronymic"),
        soci::use(client.phone, "phone"), soci::use(client.email, "email"),
        soci::use(client.sex, "sex"), soci::use(client.city, "city"),
        soci::use(client.id, "id");
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

void db_methods::deleteProvider(soci::session& sql,
                                const std::vector<int>& ids) {
    soci::transaction tr(sql);  // Открываем транзакцию
    std::string query =
        "DELETE FROM provider WHERE id = :id";  // Формируем запрос к СУБД
    try {
        sql << query, soci::use(ids);
        tr.commit();
    } catch (soci::soci_error const& e) {
        tr.rollback();  // При исключении откатываем изменения
        throw e;
    }
}

provider db_methods::getProvider(soci::session& sql, const int& id) {
    boost::optional<provider> result;
    std::string query =
        "SELECT * FROM provider WHERE id = :id";  // Формируем запрос к СУБД
    sql << query, soci::into(result), soci::use(id, "id");  // Выполняем запрос
    if (result) {
        return result.get();
    }
    throw std::runtime_error(
        QObject::tr("База данных не вернула значение").toStdString());
}

void db_methods::updateProvider(soci::session& sql, const provider& provider) {
    std::string query =
        "UPDATE provider SET name = :name WHERE id = :id";  // Формируем запрос
                                                            // к СУБД
    sql << query, soci::use(provider.name, "name"),
        soci::use(provider.id, "id");
}

void db_methods::newProvider(soci::session& sql, const provider& provider) {
    std::string query =
        "INSERT INTO provider(name) VALUES (:name)";  // Формируем запрос к СУБД
    sql << query, soci::use(provider.name, "name");
}

void db_methods::deleteEmployee(soci::session& sql,
                                const std::vector<int>& ids) {
    soci::transaction tr(sql);  // Открываем транзакцию
    std::string query =
        "DELETE FROM employee WHERE id = :id";  // Формируем запрос к СУБД
    try {
        sql << query, soci::use(ids);
        tr.commit();
    } catch (soci::soci_error const& e) {
        tr.rollback();  // При исключении откатываем изменения
        throw e;
    }
}

employee db_methods::getEmployee(soci::session& sql, const int& id) {
    boost::optional<employee> result;
    std::string query =
        "SELECT * FROM employee WHERE id = :id";  // Формируем запрос к СУБД
    sql << query, soci::into(result), soci::use(id, "id");  // Выполняем запрос
    if (result) {
        return result.get();
    }
    throw std::runtime_error(
        QObject::tr("База данных не вернула значение").toStdString());
}

void db_methods::updateEmployee(soci::session& sql, const employee& employee) {
    std::string query =
        "UPDATE employee SET name = :name, surname = :surname, patronymic "
        "= :patronymic, login = :login, password = :password WHERE id = "
        ":id";  // Формируем запрос к СУБД
    sql << query, soci::use(employee.name, "name"),
        soci::use(employee.surname, "surname"),
        soci::use(employee.patronymic, "patronymic"),
        soci::use(employee.login, "login"),
        soci::use(employee.password, "password"), soci::use(employee.id, "id");
}

int db_methods::newEmployee(soci::session& sql, const employee& employee) {
    soci::transaction tr(sql);
    std::string query =
        "INSERT INTO employee(name, surname, patronymic, login, "
        "password) VALUES (:name, :surname, :patronymic, "
        ":login, :password)";  // Формируем запрос к СУБД
    sql << query, soci::use(employee.name, "name"),
        soci::use(employee.surname, "surname"),
        soci::use(employee.patronymic, "patronymic"),
        soci::use(employee.login, "login"),
        soci::use(employee.password, "password");
    query = "SELECT id FROM employee WHERE login = :login";
    boost::optional<int> id;
    sql << query, soci::use(employee.login, "login"), soci::into(id);
    if (id) {
        tr.commit();
        return id.get();
    }
    throw std::runtime_error(
        QObject::tr("Не получилось добавить сотрудника").toStdString());
    tr.rollback();
}

void db_methods::deleteStock(soci::session& sql, const std::vector<int>& ids) {
    soci::transaction tr(sql);  // Открываем транзакцию
    std::string query =
        "DELETE FROM stock WHERE id = :id";  // Формируем запрос к СУБД
    try {
        sql << query, soci::use(ids);
        tr.commit();
    } catch (soci::soci_error const& e) {
        tr.rollback();  // При исключении откатываем изменения
        throw e;
    }
}

void db_methods::newStock(soci::session& sql, const stock& stock) {
    std::string query =
        "INSERT INTO stock(laptop, price, count, available, source) "
        "VALUES "
        "(:laptop, :price, :count, :available, :provider)";  // Формируем запрос
                                                             // к СУБД
    sql << query, soci::use(stock.laptop, "laptop"),
        soci::use(stock.price, "price"), soci::use(stock.count, "count"),
        soci::use(stock.available, "available"),
        soci::use(stock.source, "provider");
}

void db_methods::deleteAd(soci::session& sql, const std::vector<int>& ids) {
    soci::transaction tr(sql);  // Открываем транзакцию
    std::string query =
        "DELETE FROM advertisement WHERE id = :id";  // Формируем запрос к СУБД
    try {
        sql << query, soci::use(ids);
        tr.commit();
    } catch (soci::soci_error const& e) {
        tr.rollback();  // При исключении откатываем изменения
        throw e;
    }
}

advertisement db_methods::getAd(soci::session& sql, const int& id) {
    boost::optional<advertisement> result;
    std::string query =
        "SELECT * FROM advertisement WHERE id = :id";  // Формируем запрос к
                                                       // СУБД
    sql << query, soci::into(result), soci::use(id, "id");  // Выполняем запрос
    if (result) {
        return result.get();
    }
    throw std::runtime_error(
        QObject::tr("База данных не вернула значение").toStdString());
}

void db_methods::updateAd(soci::session& sql, const advertisement& ad) {
    std::string query =
        "UPDATE advertisement SET source = :source, budget = :budget, "
        "comments = :comments WHERE id = :id";  // Формируем запрос к СУБД
    sql << query, soci::use(ad.source, "source"),
        soci::use(ad.budget, "budget"), soci::use(ad.comments, "comments"),
        soci::use(ad.id, "id");
}

void db_methods::newAd(soci::session& sql, const advertisement& ad) {
    std::string query =
        "INSERT INTO advertisement(source, budget, comments) VALUES "
        "(:source, :budget, :comments)";  // Формируем запрос к СУБД
    sql << query, soci::use(ad.source, "source"),
        soci::use(ad.budget, "budget"), soci::use(ad.comments, "comments");
}

void db_methods::deleteDeal(soci::session& sql, const std::vector<int>& ids) {
    soci::transaction tr(sql);  // Открываем транзакцию
    std::string query =
        "DELETE FROM deal WHERE id = :id";  // Формируем запрос к СУБД
    try {
        sql << query, soci::use(ids);
        tr.commit();
    } catch (soci::soci_error const& e) {
        tr.rollback();  // При исключении откатываем изменения
        throw e;
    }
}

deal db_methods::getDeal(soci::session& sql, const int& id) {
    boost::optional<deal> result;
    std::string query = "SELECT * FROM deal WHERE id = :id";  // Формируем
                                                              // запрос к СУБД
    sql << query, soci::into(result), soci::use(id, "id");  // Выполняем запрос
    if (result) {
        return result.get();
    }
    throw std::runtime_error(
        QObject::tr("База данных не вернула значение").toStdString());
}

void db_methods::updateDeal(soci::session& sql, const deal& deal) {
    std::string query =
        "UPDATE deal SET laptop = :laptop, cost = :cost, client = :client, "
        "status = :status, seller = :seller WHERE id = :id";  // Формируем
                                                              // запрос к СУБД
    sql << query, soci::use(deal.laptop, "laptop"),
        soci::use(deal.cost, "cost"), soci::use(deal.client, "client"),
        soci::use(deal.status, "status"), soci::use(deal.seller, "seller"),
        soci::use(deal.id, "id");
}

void db_methods::newDeal(soci::session& sql, const deal& deal) {
    std::string query =
        "INSERT INTO deal(laptop, cost, client, status, seller) VALUES "
        "(:laptop, :cost, :client, :status, :seller)";
    sql << query, soci::use(deal.laptop, "laptop"),
        soci::use(deal.cost, "cost"), soci::use(deal.client, "client"),
        soci::use(deal.status, "status"), soci::use(deal.seller, "seller");
}

void db_methods::deleteLaptop(soci::session& sql, const std::vector<int>& ids) {
    soci::transaction tr(sql);  // Открываем транзакцию
    std::string query =
        "DELETE FROM laptop WHERE id = :id";  // Формируем запрос к СУБД
    try {
        sql << query, soci::use(ids);
        tr.commit();
    } catch (soci::soci_error const& e) {
        tr.rollback();  // При исключении откатываем изменения
        throw e;
    }
}

laptop db_methods::getLaptop(soci::session& sql, const int& id) {
    boost::optional<laptop> result;
    std::string query = "SELECT * FROM laptop WHERE id = :id";  // Формируем
                                                                // запрос к СУБД
    sql << query, soci::into(result), soci::use(id, "id");  // Выполняем запрос
    if (result) {
        return result.get();
    }
    throw std::runtime_error(
        QObject::tr("База данных не вернула значение").toStdString());
}

void db_methods::updateLaptop(soci::session& sql, const laptop& laptop) {
    std::string query =
        "UPDATE laptop SET name = :name, income = :income, type = :type, cpu = "
        ":cpu, gpu = :gpu, ram = :ram, rom = :rom, color = :color WHERE id = "
        ":id ";  // Формируем запрос к СУБД
    sql << query, soci::use(laptop.name, "name"),
        soci::use(laptop.income, "income"), soci::use(laptop.type, "type"),
        soci::use(laptop.cpu, "cpu"), soci::use(laptop.gpu, "gpu"),
        soci::use(laptop.ram, "ram"), soci::use(laptop.rom, "rom"),
        soci::use(laptop.color, "color"), soci::use(laptop.id, "id");
}

void db_methods::newLaptop(soci::session& sql, const laptop& laptop) {
    std::string query =
        "INSERT INTO laptop(name, income, type, cpu, gpu, ram, rom, "
        "color) VALUES (:name, :income, :type, :cpu, "
        ":gpu, :ram, :rom, :color)";  // Формируем
                                      // запрос к СУБД
    sql << query, soci::use(laptop.name, "name"),
        soci::use(laptop.income, "income"), soci::use(laptop.type, "type"),
        soci::use(laptop.cpu, "cpu"), soci::use(laptop.gpu, "gpu"),
        soci::use(laptop.ram, "ram"), soci::use(laptop.rom, "rom"),
        soci::use(laptop.color, "color");
}

std::vector<employee> db_methods::getSeller(soci::session& sql) {
    std::vector<employee> result;
    std::string query =
        "SELECT employee.* FROM employee JOIN seller ON employee.id = "
        "seller.employee";  // Формируем
                            // запрос к СУБД
    soci::rowset<employee> rs = (sql.prepare << query);  // Подготавливаем его
    for (auto it = rs.begin(); it != rs.end(); it++) {  // Выполняем построчно
        const auto& row = *it;  // Текущая строка
        result.push_back(row);  // Добавляем в результат
    }
    return result;  // Возвращаем результат
}
