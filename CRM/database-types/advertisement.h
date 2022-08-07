// Advertisement table structure
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

// структура таблицы advertisement
struct advertisement {
    int id;                // ID рекламы
    std::string source;    // Источник рекламы
    long long budget;      // Бюджет рекламы
    std::string comments;  // Комментарий к рекламе

    advertisement() = default;

    void clear() {
        id = 0;
        source.clear();
        budget = 0;
        comments.clear();
    }

    advertisement(const advertisement& other)
        : id(other.id),
          source(other.source),
          budget(other.budget),
          comments(other.comments) {}

    advertisement& operator=(const advertisement& rhs) {
        if (this != std::addressof(rhs)) {
            id = rhs.id;
            source = rhs.source;
            budget = rhs.budget;
            comments = rhs.comments;
        }
        return *this;
    }
};

namespace soci {

template <>
struct type_conversion<advertisement> {
    using base_type = values;

    static void from_base(values const& v, indicator ind, advertisement& ad) {
        if (ind == i_null) {
            return;
        }
        try {
            ad.id = v.get<int>("id", 0);
            ad.source = v.get<std::string>("source", "");
            ad.budget = v.get<long long>("budget", 0);
            ad.comments = v.get<std::string>("comments", "");
        } catch (std::exception const& e) {
            // Logging
        }
    }

    static void to_base(const advertisement& p, values& v, indicator& ind) {
        try {
            v.set("id", p.id);
            v.set("source", p.source);
            v.set("budget", p.budget);
            v.set("comments", p.comments);

            ind = i_ok;
            return;
        } catch (std::exception const& e) {
            // Logging
        }
        ind = i_null;
    }
};

}  // namespace soci
