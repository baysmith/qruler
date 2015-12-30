/***************************************************************************
 *   Copyright (C) 2009 by Gantsov Konstantin                              *
 *   kossne@mail.ru                                                        *
 *                                                                         *
 * QRule is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * QRule is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with QRule. If not, see <http://www.gnu.org/licenses/>.        *
 ***************************************************************************/

#include <QtWidgets/QApplication>
#include "qrule.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QRule w(a.desktop()->screenGeometry());
    QObject::connect(&w, SIGNAL(menu_quit()), &a, SLOT(quit()));
    w.show();
    w.activateWindow();
    return a.exec();
}
