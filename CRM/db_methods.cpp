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
#include "db_methods.h"

std::vector<boost::tuple<stock, laptop, provider>> getStock(soci::session& sql,
                                                            const int& offset,
                                                            const int& limit) {
    std::vector<boost::tuple<stock, laptop, provider>> result;
    std::string query =
        "SELECT stock.*, laptop.*, provider.* FROM stock JOIN laptop "
        "ON laptop.id = stock.laptop JOIN provider ON "
        "provider.id = stock.source LIMIT " +
        std::to_string(limit) + " OFFSET " + std::to_string(offset * limit);
    soci::rowset<soci::row> rs = (sql.prepare << query);
    for (auto it = rs.begin(); it != rs.end(); it++) {
        const auto& row = *it;
        result.push_back(
            {stock(row.get<int>(0), row.get<int>(1), row.get<int>(2),
                   row.get<int>(3), row.get<int>(4), row.get<int>(5)),
             laptop(row.get<int>(6), row.get<std::string>(7),
                    row.get<double>(8), row.get<std::string>(9),
                    row.get<std::string>(10), row.get<std::string>(11),
                    row.get<int>(12), row.get<int>(13),
                    row.get<std::string>(14)),
             provider(row.get<int>(15), row.get<std::string>(16))});
    }
    return result;
}

std::vector<provider> getProvider(soci::session& sql, const int& offset,
                                  const int& limit) {
    std::vector<provider> result;
    std::string query = "SELECT * FROM provider LIMIT " +
                        std::to_string(limit) + " OFFSET " +
                        std::to_string(offset * limit);
    soci::rowset<provider> rs = (sql.prepare << query);
    for (auto it = rs.begin(); it != rs.end(); it++) {
        const auto& row = *it;
        result.push_back(row);
    }
    return result;
}

std::vector<boost::tuple<deal, laptop, client, employee>> getDeal(
    soci::session& sql, const int& offset, const int& limit) {
    std::vector<boost::tuple<deal, laptop, client, employee>> result;
    std::string query =
        "SELECT deal.*, laptop.*, client.*, employee.* FROM "
        "deal JOIN laptop ON laptop.id = deal.laptop JOIN client ON "
        "client.id = deal.client JOIN employee ON employee.id = "
        "deal.seller LIMIT " +
        std::to_string(limit) + " OFFSET " + std::to_string(offset * limit);
    soci::rowset<soci::row> rs = (sql.prepare << query);
    for (auto it = rs.begin(); it != rs.end(); it++) {
        const auto& row = *it;
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
                      row.get<std::string>(30), row.get<std::string>(31))});
    }
    return result;
}

std::vector<employee> getEmployee(soci::session& sql, const int& offset,
                                  const int& limit) {
    std::vector<employee> result;
    std::string query = "SELECT * FROM employee LIMIT " +
                        std::to_string(limit) + " OFFSET " +
                        std::to_string(offset * limit);
    soci::rowset<employee> rs = (sql.prepare << query);
    for (auto it = rs.begin(); it != rs.end(); it++) {
        const auto& row = *it;
        result.push_back(row);
    }
    return result;
}

std::vector<advertisement> getAdvertisement(soci::session& sql,
                                            const int& offset,
                                            const int& limit) {
    std::vector<advertisement> result;
    std::string query = "SELECT * FROM advertisement LIMIT " +
                        std::to_string(limit) + " OFFSET " +
                        std::to_string(offset * limit);
    soci::rowset<advertisement> rs = (sql.prepare << query);
    for (auto it = rs.begin(); it != rs.end(); it++) {
        const auto& row = *it;
        result.push_back(row);
    }
    return result;
}

std::vector<client> getClient(soci::session& sql, const int& offset,
                              const int& limit) {
    std::vector<client> result;
    std::string query = "SELECT * FROM client LIMIT " + std::to_string(limit) +
                        " OFFSET " + std::to_string(offset * limit);
    soci::rowset<client> rs = (sql.prepare << query);
    for (auto it = rs.begin(); it != rs.end(); it++) {
        const auto& row = *it;
        result.push_back(row);
    }
    return result;
}
