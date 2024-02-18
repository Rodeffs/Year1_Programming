#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPoint>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *) {

    QPainter painter(this);

    // Задача про фонарик (если в зоне видимости 30 градусов - то видит, иначе - не видит):
    QLineF line1(dot1, dot2);
    QLineF line2(line1); // копируем координаты line1 в line2
    line2.setAngle(line1.angle() + 30); // строим вторую прямую так, чтобы между ней и первой было 30 градусов

    QPointF a1 = dot2 - dot1;
    QPointF a2 = line2.p2() - line2.p1(); // находим первую и вторую точку прямой через .p1() и .p2()

    if (!(dot1.isNull())&&!(dot2.isNull())) {
        painter.drawLine(line1); // линия 1
        painter.drawLine(line2); // линия 2

        // Для отрисовки света фонарика (отключить, если лагает)
        /*
        QRect screen = contentsRect();
        QPen yellow(QColor(255, 255, 0, 85));
        QPen black(Qt::black);
        for (int i = 0; i < screen.width(); i++)
            for (int j = 0; j < screen.height(); j++) {
                QPointF pixel(i, j);
                QPointF b1 = pixel - dot1;
                QPointF b2 = pixel - line2.p1();
                int sign1 = a1.x()*b1.y() - a1.y()*b1.x();
                int sign2 = a2.x()*b2.y() - a2.y()*b2.x();
                if (sign1 < 0 && sign2 > 0) {
                    painter.setPen(yellow);
                    painter.drawPoint(pixel);
                    painter.setPen(black);
                }
            }
        */
    }

    if ((!obj.isNull())&&(!(dot1.isNull())&&!(dot2.isNull()))) {
        painter.drawEllipse(obj, 5, 5);

        QPointF b1 = obj - dot1;
        QPointF b2 = obj - line2.p1();

        // Выясняем, с какой стороны находится точка по формуле из учебника Ласло
        int sign1 = a1.x()*b1.y() - a1.y()*b1.x();
        int sign2 = a2.x()*b2.y() - a2.y()*b2.x();

        if (sign1 <= 0 && sign2 >= 0) // в фонарике (т.е. слева от одной и справа от другой)
            qDebug() << "I see";
        else if (sign1 <= 0 && sign2 <= 0) // слева от фонарика
            qDebug() << "I can't see, it's to the left";
        else if (sign1 >= 0 && sign2 >= 0) // справа от фонарика
            qDebug() << "I can't see, it's to the right";
        else  // сзади от фонарика
            qDebug() << "I can't see, it's behind";
    }

#if 0
    // Пересечение двух прямых:

    QPointF inter; // точка, которой будем присваивать координаты пересечения

    QLineF line1 (100, 100, 150, 140);

//    QLineF line2 (100, 100, 150, 140);

    QLineF line2 (110, 150, 160, 80);

    line1.intersects(line2, &inter); // intersect() берёт первым параметром линию, с проверяем пересечение, а вторым - ссылку на точку, которой он присвоит координаты пересечения

    qDebug() << line1.intersects(line2, &inter);

    painter.drawLine(line1);

    painter.drawLine(line2);

    QBrush black (Qt::black);

    painter.setBrush(black);

    painter.drawEllipse(inter, 2, 2);
#endif
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    if (!(Qt::ControlModifier & event->modifiers())&&(Qt::LeftButton & event->buttons()))
        dot1 = event->pos();

    if (Qt::RightButton & event->buttons())
        dot2 = event->pos();

    if ((Qt::ControlModifier & event->modifiers())&&(Qt::LeftButton & event->buttons()))
        obj = event->pos();

    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {

}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {

    if (!(Qt::ControlModifier & event->modifiers())&&(Qt::LeftButton & event->buttons())) {
        dot1 = event->pos();
        repaint(); // repaint() каждый раз вызваю отдельно, чтобы не забивать консоль
    }

    if (Qt::RightButton & event->buttons()) {
        dot2 = event->pos();
        repaint();
    }

    if ((Qt::ControlModifier & event->modifiers())&&(Qt::LeftButton & event->buttons())) {
        obj = event->pos();
        repaint();
    }
}
