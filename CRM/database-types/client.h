// Client table structure
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
#pragma once
#include <memory>

#include "../db_pool.h"

struct client {
    int id;                  // ID клиента
    std::string surname;     // Фамилия клиента
    std::string name;        // Имя клиента
    std::string patronymic;  // Отчество клиента
    std::string email;       // Email клиента
    std::string phone;       // Телефон клиента
    std::string sex;         // Пол клиента
    std::string city;        // Город клиента

    client() = default;

    client(int id, std::string surname, std::string name,
           std::string patronymic, std::string email, std::string phone,
           std::string sex, std::string city)
        : id(id),
          name(name),
          surname(surname),
          patronymic(patronymic),
          email(email),
          phone(phone),
          sex(sex),
          city(city) {}

    client(const client& other)
        : id(other.id),
          surname(other.surname),
          name(other.name),
          patronymic(other.patronymic),
          email(other.email),
          phone(other.phone),
          sex(other.sex),
          city(other.city) {}

    client& operator=(const client& rhs) {
        if (this != std::addressof(rhs)) {
            id = rhs.id;
            surname = rhs.surname;
            name = rhs.name;
            patronymic = rhs.patronymic;
            email = rhs.email;
            phone = rhs.phone;
            sex = rhs.sex;
            city = rhs.city;
        }
        return *this;
    }
};

namespace soci {

template <>
struct type_conversion<client> {
    using base_type = values;

    static void from_base(values const& v, indicator ind, client& c) {
        /*
         * Конвертация из данных в структуру
         */
        if (ind == i_null) {
            return;
        }
        try {
            c.id = v.get<int>("id", 0);
            c.surname = v.get<std::string>("surname", "");
            c.name = v.get<std::string>("name", "");
            c.patronymic = v.get<std::string>("patronymic", "");
            c.email = v.get<std::string>("email", "");
            c.phone = v.get<std::string>("phone", "");
            c.sex = v.get<std::string>("sex", "");
            c.city = v.get<std::string>("city", "");
        } catch (std::exception const& e) {
            // Logging
        }
    }

    static void to_base(const client& c, values& v, indicator& ind) {
        /*
         * Конвертация из структуры в данные
         */
        try {
            v.set("id", c.id);
            v.set("surname", c.surname);
            v.set("name", c.name);
            v.set("patronymic", c.patronymic);
            v.set("email", c.email);
            v.set("phone", c.phone);
            v.set("sex", c.sex);
            v.set("city", c.city);

            ind = i_ok;
            return;
        } catch (std::exception const& e) {
            // Logging
        }
        ind = i_null;
    }
};
}  // namespace soci
