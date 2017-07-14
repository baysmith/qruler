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

#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QWidget>
#include <QtGui/QPen>

class QMenu;

class QRuler : public QWidget
{
    Q_OBJECT

public:
    QRuler(QRect const &, QWidget *parent = nullptr);
    void createActions();

public slots:
    void showHideRule();
    void horisontalRule();
    void setOnTop(bool);
    void menuOnTop();
    void pickColor();
    void about();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

signals:
    void menu_quit();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QPoint clickPos;
    int pointer;
    QSystemTrayIcon *trayIcon;
    QAction *windowOnTopAct;
    QAction *hideAct;
    QMenu *contexMenu;
    bool horisontal;
    QClipboard *clipboard;
    QPoint newPlace;
    QPoint grabPoint;
    QColor colorGradTop;
    QColor colorGradBottom;
    QFont fontNormal;
    QFont fontBold;
    QFont fontColorName;
    QPen defaultPen;
    QColor pickedColor;

};
