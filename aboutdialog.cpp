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

#include "aboutdialog.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStyle>
#include <QtWidgets/QStyleFactory>

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    auto labelCopyright = new QLabel(tr("<h3 align='center'>QRuler</h3>"
                    "<p>Copyright &copy; 2017 Bradley Smith</p>"),
                 this);
    labelCopyright->setWordWrap(true);

    QStyle *style = QStyleFactory::create("fusion");
    QApplication::setStyle(style);

    QIcon icon = QIcon(":/images/qruler_64.png");

    auto groupBox = new QGroupBox(tr("GNU General Public Licence"));
    groupBox->setFlat(false);

    auto LabelGnuGpl = new QLabel(
    tr("QRuler is free software; you can redistribute it "
       "and/or modify it under the terms of the GNU General "
       "Public License as published by the Free Software "
       "Foundation; either version 3 of the License, or (at your "
       "option) any later version.<br><br>"
       "QRuler is distributed in the hope that it will be "
       "useful, but WITHOUT ANY WARRANTY; without even the "
       "implied warranty of MERCHANTABILITY or FITNESS FOR<br>"
       "A PARTICULAR PURPOSE. See the GNU General Public<br>"
       "License for more details. <br><br>"
       "You should have received a copy of the GNU General Public License "
       "along with QRuler. If not, see http://www.gnu.org/licenses/."));
    LabelGnuGpl->setWordWrap(true);
    LabelGnuGpl->setAlignment(Qt::AlignLeft);

    auto groupBoxLayout = new QHBoxLayout;
    groupBoxLayout->addWidget(LabelGnuGpl);
    groupBox->setLayout(groupBoxLayout);

    auto buttonOk = new QPushButton(tr("OK"));
    buttonOk->setMaximumWidth(60);
    connect(buttonOk, QPushButton::clicked, this, AboutDialog::close);

    auto mainLayout = new QGridLayout;
    mainLayout->addWidget(labelCopyright, 0, 0);
    mainLayout->addWidget(groupBox, 1, 0);
    mainLayout->addWidget(buttonOk, 2, 0, Qt::AlignCenter);
    setLayout(mainLayout);
    setWindowTitle(tr("About"));
}
