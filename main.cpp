/***************************************************************************
 *   Copyright (C) 2017 by Bradley Smith                                   *
 *   Copyright (C) 2009 by Gantsov Konstantin                              *
 *                                                                         *
 * QRuler is free software: you can redistribute it and/or modify          *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * QRuler is distributed in the hope that it will be useful,               *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with QRuler. If not, see <http://www.gnu.org/licenses/>.          *
 ***************************************************************************/

#include "qruler.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QRuler w(a.desktop()->screenGeometry());
    QObject::connect(&w, QRuler::menu_quit, &a, QApplication::quit);
    w.show();
    w.activateWindow();
    return a.exec();
}
