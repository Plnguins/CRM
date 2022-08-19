// Provider table structure
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

struct provider {
    int id;            // ID поставщика
    std::string name;  // Название поставщика

    provider() = default;

    provider(const provider& other)
        : id(other.id),
          name(other.name.c_str()) {
    }  // c_str() нужен для того, чтобы конструктор копирования работал
       // корректно при включенном ASan

    provider& operator=(const provider& rhs) {
        if (this != std::addressof(rhs)) {
            id = rhs.id;
            name = rhs.name;
        }
        return *this;
    }
};

namespace soci {
template <>
struct type_conversion<provider> {
    using base_type = values;

    static void from_base(values const& v, indicator ind, provider& l) {
        if (ind == i_null) {
            return;
        }
        try {
            l.id = v.get<int>("id");
            l.name = v.get<std::string>("name");
        } catch (const std::exception& l) {
            // Logging
        }
    }

    static void to_base(provider const& l, values& v, indicator& ind) {
        try {
            v.set("id", l.id);
            v.set("name", l.name);

            ind = i_ok;
            return;
        } catch (const std::exception& l) {
            // Logging
        }
        ind = i_null;
    }
};
}  // namespace soci
