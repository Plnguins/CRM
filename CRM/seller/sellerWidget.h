// Seller window header for CRM application
// Copyright(C) 2022 Plnguins

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

#include "../interface/interfaceWidget.h"

class sellerWidget : public interfaceWidget {
    Q_OBJECT

   public:
    explicit sellerWidget(QMainWindow* parent = nullptr, std::string name = "",
                          std::string surname = "")
        : interfaceWidget(parent, name, surname) {
        ui->Ads->hide();
        ui->Employee->hide();
        ui->Provider->hide();
    }
    ~sellerWidget() = default;
};
