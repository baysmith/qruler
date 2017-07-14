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

#pragma once

#include <QtWidgets/QDialog>

class QGridLayout;
class QGroupBox;
class QHBoxLayout;
class QLabel;
class QPushButton;

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    AboutDialog(QWidget *parent = nullptr);
};
