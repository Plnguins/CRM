// Main source code for CRM application
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
#include <QApplication>
#include <QTranslator>

#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QTranslator translator;
    if (translator.load(QLocale::system(), u"crm"_qs, u"_"_qs,
                        u":/i18n"_qs)) {  // Если удалось загрузить перевод -
                                          // устанавливаем его
        a.installTranslator(&translator);
    }
    MainWindow w;
    w.show();
    return a.exec();
}
