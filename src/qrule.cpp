/***************************************************************************
 *   Copyright (C) 2009 by Gancov Konstantin                               *
 *   kossne@mail.ru                                                        *
 *                                                                         *
 * QRule is free software: you can redistribute it and/or modify           *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * QRule is distributed in the hope that it will be useful,                *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with QRule. If not, see <http://www.gnu.org/licenses/>.           *
 ***************************************************************************/

#include "qrule.h"

QRule::QRule(QRect const & sg, QWidget *parent)
    : QWidget(0)
{
    horisontal = true;
    pointer = -1;
    createActions();
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(contexMenu);

    QIcon icon = QIcon(":/images/qrule_64.png");
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
    trayIcon->show();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
             this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    #ifdef Q_WS_WIN
    Qt::WindowFlags wf;
    wf |= Qt::WindowStaysOnTopHint;
    wf |= Qt::FramelessWindowHint;

    windowOnTopAct->setChecked(true);
    if (wf != windowFlags()) {
        setWindowFlags(wf);
        show();
        raise();
    }
    setWindowOpacity(0.8);
    move(0, sg.height() / 2);
    resize(sg.width() + 30, 76);
    #endif



    #ifdef Q_WS_X11
    Qt::WindowFlags wf = windowFlags();
    wf |= Qt::WindowStaysOnTopHint;
    wf |= Qt::X11BypassWindowManagerHint;
    setWindowFlags(wf);

    windowOnTopAct->setChecked(true);
    resize(sg.width() + 30, 76);
    setWindowOpacity(0.8);
    #endif

    QPixmap pxVert(":/images/pointer4.png");
    setCursor(QCursor(pxVert));
    setMouseTracking(true);

    colorGradTop = QColor("#517da2"); //be7d32
    colorGradBottom = QColor("#b7cde0"); //#feb969

    fontNormal = QFont("Arial", 7, QFont::Normal);
    fontBold = QFont("Arial", 7, QFont::Bold);
    defaultPen = QPen(Qt::black, 1, Qt::SolidLine);
    fontColorName = QFont("Arial", 8, QFont::Normal);
}

QRule::~QRule()
{
    //qDebug() << "destruct";
}

void QRule::createActions()
{
    horisontalRuleAct = new QAction(tr("Horisontal"),this);
    horisontalRuleAct->setShortcut(tr("H"));
    horisontalRuleAct->setCheckable(true);
    horisontalRuleAct->setChecked(true);
    connect(horisontalRuleAct, SIGNAL(triggered()), this, SLOT(horisontalRule()));

    windowOnTopAct = new QAction(tr("Window on top"), this);
    windowOnTopAct->setCheckable(true);
    connect(windowOnTopAct, SIGNAL(triggered()), this, SLOT(menuOnTop()));

    pickColorAct = new QAction(tr("Pick color"), this);
    pickColorAct->setShortcut(tr("Ctrl+C"));
    connect(pickColorAct, SIGNAL(triggered()), this, SLOT(pickColor()));

    aboutAct = new QAction(tr("About"), this);
    aboutAct->setShortcut(tr("F1"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    hideAct = new QAction(tr("Hide"), this);
    connect(hideAct, SIGNAL(triggered()), this, SLOT(showHideRule()));
    QFont font(hideAct->font());
    font.setBold(true);
    hideAct->setFont(font);

    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SIGNAL(menu_quit()));

    contexMenu = new QMenu(this);

    contexMenu->addAction(hideAct);
    contexMenu->addAction(horisontalRuleAct);
    contexMenu->addAction(windowOnTopAct);
    contexMenu->addAction(pickColorAct);
    contexMenu->addAction(aboutAct);
    contexMenu->addSeparator();
    contexMenu->addAction(exitAct);
}

void QRule::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QFontMetrics fm(fontNormal);
    QFontMetrics fmColorName(fontColorName);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(defaultPen);
    if (horisontal == true) {
        QLinearGradient gradient(0, 0, 0, height());
        gradient.setColorAt(0, colorGradTop);
        gradient.setColorAt(1, colorGradBottom);
        painter.setBrush(gradient);
        painter.drawRect(0, 0, width() - 1, height() - 1);
        int lineHeight = 5;
        int cnt = 0;
        int marginLeft = 2;
        int k = 20;
        painter.setFont(fontNormal);
        QString pointer1 = QString::number(pointer);
        QPixmap pixel = QPixmap::grabWindow(QApplication::desktop()->winId(), grabPoint.x(), grabPoint.y() + 21, 1, 1);
        QImage img(pixel.toImage()); 
        if (pickedColor != QColor(img.pixel(0,0))) {
            pickedColor = QColor(img.pixel(0,0));
        }
        painter.setFont(fontColorName);
        painter.setBrush(QBrush(pickedColor, Qt::SolidPattern));
        painter.drawRect(10, 10, 30, 20);
        painter.drawText(50, 15, fmColorName.width(QChar('0')) * 7, fmColorName.height(), Qt::AlignLeft, pickedColor.name());

        for (int i = 0; i < (width() - 30); i+=2) {
            lineHeight = 5;

            if (i >= 1000)
                marginLeft = 5;

            QString number = QString::number(i);
            if (cnt == 0) {
                painter.setFont(fontBold);
                lineHeight = 20;
                painter.drawText(-2, height() - 30, 20, 10, Qt::AlignRight, number);
            }

            if (cnt == 10) {
                QString number1 = QString::number(k);
                if (i % 100 == 0) {
                    painter.setFont(fontBold);
                    painter.drawText(marginLeft + i, height() - 30, 23, 10, Qt::AlignRight, number);
                    lineHeight = 20;
                } else {
                    painter.setFont(fontNormal);
                    painter.drawText(0 + i, height() - 25, 20, 10, Qt::AlignRight, number1);
                    lineHeight = 15;
                }
                cnt = 0;
                if (i % 100 == 0)
                    k = 0;
                k += 20;
            }

            if (cnt == 5) {
                lineHeight = 10;
            }

            painter.drawLine(QPoint(15 + i, width()), QPoint(15 + i, height() - lineHeight));

            ++cnt;
        }

        if (pointer >= 0) {
            painter.setPen(defaultPen);
            painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
            painter.drawRect(pointer, 13, fm.width(QChar()) * 4, fm.height() + 1);
            painter.drawText(pointer, 13, fm.width(QChar()) * 4, fm.height() + 1, Qt::AlignCenter, pointer1);
        }

    } else {
        QLinearGradient gradient(width(), 0, 0, 0);
        gradient.setColorAt(0, colorGradTop);
        gradient.setColorAt(1, colorGradBottom);
        painter.setBrush(gradient);
        painter.drawRect(0, 0, width() - 1, height() - 1);
        int lineHeight = 5;
        int cnt = 0;
        int marginLeft = 2;
        int k = 20;
        painter.setFont(fontNormal);
        QString pointer1 = QString::number(pointer);

        QPixmap pixel = QPixmap::grabWindow(QApplication::desktop()->winId(), grabPoint.x() - 22, grabPoint.y(), 1, 1);
        QImage img(pixel.toImage());
        if (pickedColor != QColor(img.pixel(0,0))) {
            pickedColor = QColor(img.pixel(0,0));
        }

        painter.setFont(fontColorName);
        painter.setBrush(QBrush(pickedColor, Qt::SolidPattern));
        painter.drawRect(44, 10, 20, 30);
        painter.drawText(33, 50, fmColorName.width(QChar('0')) * 7, fmColorName.height(), Qt::AlignLeft, pickedColor.name());

        for (int i = 0; i < (height() - 30); i+=2) {
            lineHeight = 5;

            if (i >= 1000)
                marginLeft = 5;

            QString number = QString::number(i);
            if (cnt == 0) {
                painter.setFont(fontBold);
                lineHeight = 20;
                painter.drawText(5, i + 10, 25, 10, Qt::AlignRight, number);
            }

            if (cnt == 10) {
                QString number1 = QString::number(k);
                if (i % 100 == 0) {
                    painter.setFont(fontBold);
                    painter.drawText(15, i + 10, 25, 10, Qt::AlignRight, number);
                    lineHeight = 20;
                } else {
                    painter.setFont(fontNormal);
                    painter.drawText(5, i + 10, 25, 10, Qt::AlignRight, number1);
                    lineHeight = 15;
                }

                cnt = 0;
                if (i % 100 == 0)
                    k = 0;
                k += 20;
            }

            if (cnt == 5) {
                lineHeight = 10;
            }

            painter.drawLine(QPoint(0, 15 + i), QPoint(lineHeight, 15 + i));

            ++cnt;
        }
        if (pointer >= 0) {

            painter.setPen(defaultPen);
            painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
            painter.drawRect(40, pointer + 5, fm.width(QChar()) * 4, fm.height() + 1);
            painter.drawText(40, pointer + 5, fm.width(QChar()) * 4, fm.height() + 1, Qt::AlignCenter, pointer1);
        }
    }
}

void QRule::mouseMoveEvent(QMouseEvent* e)
{
    grabPoint = e->globalPos();
    newPlace = e->pos();

    if (e->buttons() & Qt::LeftButton)
        move(grabPoint - clickPos);

    if (horisontal) {
        pointer = newPlace.x() - 15;
        if ((pointer >= 0) && (pointer <= width() - 31)) {
            repaint();
        }
    } else {
        pointer = newPlace.y() - 15;
        if ((pointer >= 0) && (pointer <= height() - 31)) {
            repaint();
        }
    }
}

void QRule::mousePressEvent(QMouseEvent* e)
{
    activateWindow();
    clickPos = e->pos();
    raise();
    if (e->button() == Qt::RightButton) {
        contexMenu->popup(e->globalPos());
    }
}

void QRule::resizeEvent(QResizeEvent * event)
{

}

void QRule::showHideRule()
{
    if (isVisible()) {
        hide();
        hideAct->setText(tr("Show"));
    } else {
        show();
        activateWindow();
        hideAct->setText(tr("Hide"));
    }
}

void QRule::setOnTop(bool f)
{
    Qt::WindowFlags wf = windowFlags();
    bool isv = isVisible();
    if (f) {
        wf |= Qt::WindowStaysOnTopHint;
    } else {
        wf &= ~Qt::WindowStaysOnTopHint;
    }
    if (wf != windowFlags()) {
        setWindowFlags(wf);
        if (isv) {
            show();
            raise();
        }
    }
}


void QRule::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        showHideRule();
    break;
    case QSystemTrayIcon::DoubleClick:
    break;
    default:
        ;
    }
}

void QRule::menuOnTop()
{
    setOnTop(windowOnTopAct->isChecked());
}

void QRule::pickColor()
{
    clipboard = QApplication::clipboard();
    QString str;
    str = pickedColor.name();
    str.replace(0, 1, "");
    clipboard->setText(str, QClipboard::Clipboard);
}

void QRule::horisontalRule()
{
    QPixmap pxVert(":/images/pointer4.png");
    QPixmap pxHor(":/images/pointer4hor.png");
    if (horisontal)
        horisontal = false;
    else
        horisontal = true;

    resize(height(), width());

    if (horisontal)
        setCursor(QCursor(pxVert));
    else
        setCursor(QCursor(pxHor));
}

void QRule::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Q:
            if (event->modifiers() & Qt::ControlModifier) {
                menu_quit();
            } else {
                QWidget::keyPressEvent(event);
            }
        break;

        case Qt::Key_H:
            horisontalRule();
        break;

        case Qt::Key_C:
            if (event->modifiers() & Qt::ControlModifier) {
                pickColor();
            } else {
                QWidget::keyPressEvent(event);
            }
        break;

        case Qt::Key_F1:
            about();
        break;

        default:
            QWidget::keyPressEvent(event);
    }
}

void QRule::about()
{
    /*QMessageBox::about(
        this,
        tr("QRule v0.1."),
        tr("<h3 align='center'>QRule v0.1.</h3> <p>Copyright &copy; "
           "2009 Gancov Konstantin</p><p align='left'>e-mail: kossne@mail.ru <br>"
           "ICQ: 365978665</p><h4>GNU General Public Licence</h4>"
           "QRule is free software; you can redistribute it<br>"
            "and/or modify it under the terms of the GNU General<br>"
            "Public License as published by the Free Software<br>"
            "Foundation; either version 2 of the License, or (at your<br>"
            "option) any later version.<br><br>"
            "QRule is distributed in the hope that it will be<br>"
            "useful, but WITHOUT ANY WARRANTY; without even the <br>"
            "implied warranty of MERCHANTABILITY or FITNESS FOR<br>"
            "A PARTICULAR PURPOSE. See the GNU General Public<br>"
            "License for more details. <br><br>"
            "You should have received a copy of the GNU General Public License<br>"
            "along with BinClock. If not, see http://www.gnu.org/licenses/."
    ));*/
    AboutDialog about(this);
    about.exec();
}
