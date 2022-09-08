// Stock table structure
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

struct stock {
    int id;         // ID поставки
    int laptop;     // ID ноутбука
    int price;      // Цена поставки
    int count;      // Количество ноутбуков
    int available;  // Количество доступных ноутбуков
    int source;     // ID поставщика

    stock() = default;

    stock(int id, int laptop, int price, int count, int available, int source)
        : id(id),
          laptop(laptop),
          price(price),
          count(count),
          available(available),
          source(source) {}

    stock(const stock& other)
        : id(other.id),
          laptop(other.laptop),
          price(other.price),
          count(other.count),
          available(other.available),
          source(other.source) {}

    stock& operator=(const stock& rhs) {
        if (this != &rhs) {
            id = rhs.id;
            laptop = rhs.laptop;
            price = rhs.price;
            count = rhs.count;
            available = rhs.available;
            source = rhs.source;
        }
        return *this;
    }
};

namespace soci {
template <>
struct type_conversion<stock> {
    using base_type = values;

    static void from_base(values const& v, indicator ind, stock& d) {
        /*
         * Конвертация из данных в структуру
         */
        if (ind == i_null) {
            return;
        }
        try {
            d.id = v.get<int>("id");
            d.laptop = v.get<int>("laptop");
            d.price = v.get<int>("price");
            d.count = v.get<int>("count");
            d.available = v.get<int>("available");
            d.source = v.get<int>("source");
        } catch (std::exception const& e) {
            // Logging
        }
    }

    static void to_base(stock const& d, values& v, indicator& ind) {
        /*
         * Конвертация из структуры в данные
         */
        try {
            v.set("id", d.id);
            v.set("laptop", d.laptop);
            v.set("price", d.price);
            v.set("count", d.count);
            v.set("available", d.available);
            v.set("source", d.source);

            ind = i_ok;
            return;
        } catch (std::exception const& e) {
            // Logging
        }
        ind = i_null;
    }
};
}  // namespace soci
