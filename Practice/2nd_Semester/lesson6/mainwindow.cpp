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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *) {

    QPainter painter(this);


                                            /* Работа с QRect: */

//    QPoint p1 (15, 15);
//    QPoint p2 (64, 64);
//    QSize s (90, 60);


    // Разные способы задачи:
//    QRect rect1 (p2, p1); - через начальную и конечную точки
//    QRect rect2 (p1, s); - через начальную точку и размер
//    QRect rect3 (10, 10, 50, 50); - через координаты каждой из вершин


    QBrush blue(Qt::blue);
    QBrush red(Qt::red);

    painter.setBrush(blue);


    // Задание 1: рисуем прямоугольник 120x80 с центром, где кликнули
    if (!centre.isNull()) {

        painter.drawRect(rect);

    // Задание 2: рисуем точки на расстоянии 20 от вершин
//        QPoint tL(-20, -20), tR(20, -20), bL(-20, 20), bR(20, 20);
//        painter.drawEllipse(rect.topLeft()     + tL, 3, 3);
//        painter.drawEllipse(rect.topRight()    + tR, 3, 3);
//        painter.drawEllipse(rect.bottomLeft()  + bL, 3, 3);
//        painter.drawEllipse(rect.bottomRight() + bR, 3, 3);
    }

    painter.setBrush(red);

    if (!copy.isNull())
        painter.drawRect(copy);


//    QRect inv(QPoint(100, 100), QSize(-1, -1));
//    qDebug() << inv.Valid(); // неправильный прямоугольник с отрицательным размером
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton)&&!(event->modifiers() & Qt::ControlModifier)&&!(event->modifiers() & Qt::AltModifier)) {
        centre = event->pos();
        QSize size(120, 80);
        rect = QRect(QPoint(centre - QPoint(size.width() / 2, size.height() / 2)), size);
    }

    if ((event->buttons() & Qt::RightButton)&&!centre.isNull()) {

        // Задание 3: сдвигаем стороны прямоугольника на половину расстояния от клика до стороны
        if (event->x() > rect.right())
            rect.setRight((event->x() + rect.right()) / 2);

        if (event->x() < rect.left())
            rect.setLeft((event->x() + rect.left()) / 2);

        if (event->y() < rect.top())
            rect.setTop((event->y() + rect.top()) / 2);

        if (event->y() > rect.bottom())
            rect.setBottom((event->y() + rect.bottom()) / 2);
    }

    // Задание 4: сдвигаем прямоугольник либо делаем его копию в зависимости от нажатия
    if ((event->buttons() & Qt::LeftButton)&&(event->modifiers() & Qt::ControlModifier)&&!centre.isNull())
        rect.translate((event->x() - centre.x()) / 2, (event->y() - centre.y()) / 2);

    if ((event->buttons() & Qt::LeftButton)&&(event->modifiers() & Qt::AltModifier)&&!centre.isNull())
        copy = rect.translated((event->x() - centre.x()) / 2, (event->y() - centre.y()) / 2);

       repaint();
}
