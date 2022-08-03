// Employee table structure
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

struct employee {
    int id;                  // ID сотрудника
    std::string surname;     // Фамилия сотрудника
    std::string name;        // Имя сотрудника
    std::string patronymic;  // Отчество сотрудника
    std::string login;       // Логин сотрудника
    std::string password;    // Пароль сотрудника

    employee() = default;

    employee(const employee &other)
        : id(other.id),
          surname(other.surname),
          name(other.name),
          patronymic(other.patronymic),
          login(other.login),
          password(other.password) {}

    employee &operator=(const employee &rhs) {
        if (this != std::addressof(rhs)) {
            id = rhs.id;
            surname = rhs.surname;
            name = rhs.name;
            patronymic = rhs.patronymic;
            login = rhs.login;
            password = rhs.password;
        }
        return *this;
    }
};

namespace soci {
template <>
struct type_conversion<employee> {
    using base_type = values;

    static void from_base(values const &v, indicator ind, employee &e) {
        if (ind == i_null) {
            return;
        }
        try {
            e.id = v.get<int>("id");
            e.surname = v.get<std::string>("surname");
            e.name = v.get<std::string>("name");
            e.patronymic = v.get<std::string>("patronymic");
            e.login = v.get<std::string>("login");
            e.password = v.get<std::string>("password");
        } catch (const std::exception &e) {
            // Logging
        }
    }

    static void to_base(employee const &e, values &v, indicator &ind) {
        try {
            v.set("id", e.id);
            v.set("surname", e.surname);
            v.set("name", e.name);
            v.set("patronymic", e.patronymic);
            v.set("login", e.login);
            v.set("password", e.password);

            ind = i_ok;
            return;
        } catch (const std::exception &e) {
            // Logging
        }
        ind = i_null;
    }
};
}  // namespace soci
