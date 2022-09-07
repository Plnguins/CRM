// Laptop table structure
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

struct laptop {
    int id;            // ID ноутбука
    std::string name;  // Название ноутбука
    double income;     // Желаемая прибыль
    std::string type;  // Тип ноутбука
    std::string cpu;   // Процессор ноутбука
    std::string gpu;   // Видеокарта ноутбука
    int ram;  // Объем оперативной памяти ноутбука
    int rom;  // Объем внутренней памяти ноутбука
    std::string color;  // Цвет ноутбука

    laptop() = default;

    laptop(int id, std::string name, double income, std::string type,
           std::string cpu, std::string gpu, int ram, int rom,
           std::string color)
        : id(id),
          name(name),
          income(income),
          type(type),
          cpu(cpu),
          gpu(gpu),
          ram(ram),
          rom(rom),
          color(color) {}

    laptop(const laptop& other)
        : id(other.id),
          name(other.name),
          income(other.income),
          type(other.type),
          cpu(other.cpu),
          gpu(other.gpu),
          ram(other.ram),
          rom(other.rom),
          color(other.color) {}

    laptop& operator=(const laptop& rhs) {
        if (this != std::addressof(rhs)) {
            id = rhs.id;
            name = rhs.name;
            income = rhs.income;
            type = rhs.type;
            cpu = rhs.cpu;
            gpu = rhs.gpu;
            ram = rhs.ram;
            rom = rhs.rom;
            color = rhs.color;
        }
        return *this;
    }
};

namespace soci {
template <>
struct type_conversion<laptop> {
    using base_type = values;

    static void from_base(values const& v, indicator ind, laptop& l) {
        /*
         * Конвертация из данных в структуру
         */
        if (ind == i_null) {
            return;
        }
        try {
            l.id = v.get<int>("id");
            l.name = v.get<std::string>("name");
            l.income = v.get<double>("income");
            l.type = v.get<std::string>("type");
            l.cpu = v.get<std::string>("cpu");
            l.gpu = v.get<std::string>("gpu");
            l.ram = v.get<int>("ram");
            l.rom = v.get<int>("rom");
            l.color = v.get<std::string>("color");
        } catch (const std::exception& l) {
            // Logging
        }
    }

    static void to_base(laptop const& l, values& v, indicator& ind) {
        /*
         * Конвертация из структуры в данные
         */
        try {
            v.set("id", l.id);
            v.set("name", l.name);
            v.set("income", l.income);
            v.set("type", l.type);
            v.set("cpu", l.cpu);
            v.set("gpu", l.gpu);
            v.set("ram", l.ram);
            v.set("rom", l.rom);
            v.set("color", l.color);

            ind = i_ok;
            return;
        } catch (const std::exception& l) {
            // Logging
        }
        ind = i_null;
    }
};
}  // namespace soci
