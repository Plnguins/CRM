// Marketer table structure
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

struct marketer {
    int id;        // ID маркетолога
    int employee;  // ID сотрудника

    marketer() = default;

    marketer(const marketer &other) : id(other.id), employee(other.employee) {}

    marketer &operator=(const marketer &rhs) {
        if (this != std::addressof(rhs)) {
            id = rhs.id;
            employee = rhs.employee;
        }
        return *this;
    }
};

namespace soci {
template <>
struct type_conversion<marketer> {
    using base_type = values;

    static void from_base(values const &v, indicator ind, marketer &l) {
        if (ind == i_null) {
            return;
        }
        try {
            l.id = v.get<int>("id");
            l.employee = v.get<int>("employee");
        } catch (const std::exception &l) {
            // Logging
        }
    }

    static void to_base(marketer const &l, values &v, indicator &ind) {
        try {
            v.set("id", l.id);
            v.set("employee", l.employee);

            ind = i_ok;
            return;
        } catch (const std::exception &l) {
            // Logging
        }
        ind = i_null;
    }
};
}  // namespace soci
