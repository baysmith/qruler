/***************************************************************************
 *   Copyright (C) 2009 by Gancov Konstantin                               *
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

#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    labelCopyright = new QLabel(tr("<h3 align='center'>QRule v0.5</h3>"
            "<p>Copyright &copy; 2009 Gancov Konstantin</p>"
            "<p align='left'>e-mail: k.gantsov@gmail.com</p>"
            ), this);
    labelCopyright->setWordWrap(true);

    QStyle *style = QStyleFactory::create("Plastique");
    QApplication::setStyle(style);

    QIcon icon = QIcon(":/images/qrule_64.png");

    mainLayout = new QGridLayout;

    groupBox = new QGroupBox(tr("GNU General Public Licence"));
    groupBox->setFlat(false);

    LabelGnuGpl = new QLabel(tr("QRule is free software; you can redistribute it "
            "and/or modify it under the terms of the GNU General "
            "Public License as published by the Free Software "
            "Foundation; either version 2 of the License, or (at your "
            "option) any later version.<br><br>"
            "QRule is distributed in the hope that it will be "
            "useful, but WITHOUT ANY WARRANTY; without even the "
            "implied warranty of MERCHANTABILITY or FITNESS FOR<br>"
            "A PARTICULAR PURPOSE. See the GNU General Public<br>"
            "License for more details. <br><br>"
            "You should have received a copy of the GNU General Public License "
            "along with BinClock. If not, see http://www.gnu.org/licenses/."
            ));
    LabelGnuGpl->setWordWrap(true);
    LabelGnuGpl->setAlignment(Qt::AlignLeft);

    groupBoxLayout = new QHBoxLayout;
    groupBoxLayout->addWidget(LabelGnuGpl);
    groupBox->setLayout(groupBoxLayout);

    buttonOk = new QPushButton(tr("OK"));
    buttonOk->setMaximumWidth(60);
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(close()));
    
    mainLayout->addWidget(labelCopyright, 0, 0);
    mainLayout->addWidget(groupBox, 1, 0);
    mainLayout->addWidget(buttonOk, 2, 0, Qt::AlignCenter);
    setLayout(mainLayout);
    this->setWindowTitle(tr("About"));
    //setFixedWidth(400);
}
