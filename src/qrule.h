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

#ifndef QRULE_H
#define QRULE_H

#include <QFrame>
#include <QtGui>
#include "aboutdialog.h"
#include <QSystemTrayIcon>

class QRule : public QWidget
{
    Q_OBJECT

public:
    QRule(QRect const &, QWidget *parent = 0);
    ~QRule();
    QPoint clickPos;
    int pointer;
    //PopupMenu *popupMenu;
    QSystemTrayIcon *trayIcon;
    void createActions();
    QAction *horisontalRuleAct;
    QAction *windowOnTopAct;
    QAction *pickColorAct;
    QAction *aboutAct;
    QAction *hideAct;
    QAction *exitAct;
    QMenu *contexMenu;
    //QMenu *myMenu;
private:
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
protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
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
};

#endif // QRULE_H
