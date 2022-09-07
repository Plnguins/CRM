// View table structure
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

struct view {
    int id;      // ID просмотра
    int source;  // ID источника просмотра
    int deal;    // ID сделки

    view() = default;

    view(int id, int source, int deal) : id(id), source(source), deal(deal) {}

    view(const view& other)
        : id(other.id), source(other.source), deal(other.deal) {}

    view& operator=(const view& rhs) {
        if (this != std::addressof(rhs)) {
            id = rhs.id;
            source = rhs.source;
            deal = rhs.deal;
        }
        return *this;
    }
};

namespace soci {
template <>
struct type_conversion<view> {
    using base_type = values;

    static void from_base(values const& v, indicator ind, view& l) {
        /*
         * Конвертация из данных в структуру
         */
        if (ind == i_null) {
            return;
        }
        try {
            l.id = v.get<int>("id");
            l.source = v.get<int>("source");
            l.deal = v.get<int>("deal");
        } catch (const std::exception& l) {
            // Logging
        }
    }

    static void to_base(view const& l, values& v, indicator& ind) {
        /*
         * Конвертация из структуры в данные
         */
        try {
            v.set("id", l.id);
            v.set("source", l.source);
            v.set("deal", l.deal);

            ind = i_ok;
            return;
        } catch (const std::exception& l) {
            // Logging
        }
        ind = i_null;
    }
};
}  // namespace soci
