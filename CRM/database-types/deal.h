// Deal table structure
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

struct deal {
    int id;              // ID сделки
    int laptop;          // ID ноутбука
    int cost;            // Сумма сделки
    std::string status;  // Статус сделки
    std::tm created;     // Дата создания
    int seller;          // ID ответственного сотрудника
    int rate;            // Оценка покупателя
    std::tm last_update;  // Дата последнего обновления

    deal() = default;

    deal(const deal &other)
        : id(other.id),
          laptop(other.laptop),
          cost(other.cost),
          status(other.status),
          created(other.created),
          seller(other.seller),
          rate(other.rate),
          last_update(other.last_update) {}

    deal &operator=(const deal &rhs) {
        if (this != &rhs) {
            id = rhs.id;
            laptop = rhs.laptop;
            cost = rhs.cost;
            status = rhs.status;
            created = rhs.created;
            seller = rhs.seller;
            rate = rhs.rate;
            last_update = rhs.last_update;
        }
        return *this;
    }
};

namespace soci {
template <>
struct type_conversion<deal> {
    using base_type = values;

    static void from_base(values const &v, indicator ind, deal &d) {
        if (ind == i_null) {
            return;
        }
        try {
            d.id = v.get<int>("id");
            d.laptop = v.get<int>("laptop");
            d.cost = v.get<int>("cost");
            d.status = v.get<std::string>("status");
            d.created = v.get<std::tm>("created");
            d.seller = v.get<int>("seller");
            d.rate = v.get<int>("rate");
            d.last_update = v.get<std::tm>("last_update");
        } catch (std::exception const &e) {
            // Logging
        }
    }

    static void to_base(deal const &d, values &v, indicator &ind) {
        try {
            v.set("id", d.id);
            v.set("laptop", d.laptop);
            v.set("cost", d.cost);
            v.set("status", d.status);
            v.set("created", d.created);
            v.set("seller", d.seller);
            v.set("rate", d.rate);
            v.set("last_update", d.last_update);

            ind = i_ok;
            return;
        } catch (std::exception const &e) {
            // Logging
        }
        ind = i_null;
    }
};
}  // namespace soci
