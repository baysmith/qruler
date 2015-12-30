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

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QDialog>
#include <QtWidgets/QStyle>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>

class AboutDialog : public QDialog
{
Q_OBJECT

public:
    AboutDialog(QWidget *parent = 0);
private:
    QGridLayout *mainLayout;
    QGroupBox *groupBox;
    QLabel *LabelGnuGpl;
    QHBoxLayout *groupBoxLayout;
    QPushButton *buttonOk;
    QLabel *labelCopyright;
};
#endif
