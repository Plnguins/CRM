// Comment table structure
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

struct comment {
    int id;                       // ID комментария
    int deal;                     // ID сделки комментария
    boost::gregorian::date date;  // Дата комментария
    std::string content;          // Содержимое комментария

    comment() = default;

    comment(int id, int deal, boost::gregorian::date date, std::string content)
        : id(id), deal(deal), date(date), content(content) {}

    comment(const comment& other)
        : id(other.id),
          deal(other.deal),
          date(other.date),
          content(other.content) {}

    comment& operator=(const comment& rhs) {
        if (this != std::addressof(rhs)) {
            id = rhs.id;
            deal = rhs.deal;
            date = rhs.date;
            content = rhs.content;
        }
        return *this;
    }
};

namespace soci {
template <>
struct type_conversion<comment> {
    using base_type = values;

    static void from_base(values const& v, indicator ind, comment& c) {
        if (ind == i_null) {
            return;
        }
        try {
            c.id = v.get<int>("id", 0);
            c.deal = v.get<int>("deal", 0);
            c.date =
                v.get<boost::gregorian::date>("date", boost::gregorian::date());
            c.content = v.get<std::string>("content", "");
        } catch (soci_error const& e) {
            // Logging
        }
    }

    static void to_base(const comment& p, values& v, indicator& ind) {
        try {
            v.set("id", p.id);
            v.set("deal", p.deal);
            v.set("date", p.date);
            v.set("content", p.content);

            ind = i_ok;
            return;
        } catch (std::exception const& e) {
            // Logging
        }
        ind = i_null;
    }
};
}  // namespace soci
