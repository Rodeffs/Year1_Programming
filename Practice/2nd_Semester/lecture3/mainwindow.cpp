#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPoint>
#include <QVector>


// Задание 1: при ПКМ ставится точка, при ЛКМ выводится, как далеко от нажатия ПКМ находится ЛКМ
// Задание 2 (Пылесос): при ПКМ ставим точку. При зажатой ЛКМ появляется пылесос, который захватывает ближайшие точки и двигает их с собой при удерживании ЛКМ
// Задание 3: две точки, создаётся отрезок, экран делится красится разными цветами по разные стороны
// Задание 4: вывести координаты пересечения прямой из задания 3 с границами экрана


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

    /*
    // Задание 1:
    QPen pen(Qt::red, 10);
    painter.setPen(pen);
    if ((!start.isNull())||(!end.isNull())) {
        painter.drawPoint(start);
        painter.drawPoint(end);
    }
    */



    // Задание 2:
    QBrush dot(Qt::black);
    QBrush vac(Qt::yellow);

    if (!circ.isNull()) { // рисуем пылесос
        painter.setBrush(vac);
        painter.drawEllipse(circ, 15, 15);
    }

    for (int i = 0; i < dots.length(); i++) { // рисуем точки
        painter.setBrush(dot);
        painter.drawEllipse(dots[i], 3, 3);
    }



    /*
    // Задание 3:
    QPen left_color(Qt::blue);
    QPen right_color(Qt::red);
    QPen line(Qt::black);

    QPoint a = dot2-dot1;

    QRect screen = contentsRect(); // разрешение окна

    if ((!dot1.isNull())&&(!dot2.isNull()))
        for (int i = 0; i < screen.width(); i++)
            for (int j = 0; j < screen.height(); j++) {
                QPoint pixel(i, j);
                QPoint b = pixel-dot1;
                int sign = a.x()*b.y() - a.y()*b.x();
                if (sign > 0)
                    painter.setPen(left_color);
                else if (sign < 0)
                    painter.setPen(right_color);
                else
                    painter.setPen(line);
                painter.drawPoint(pixel);
            }
    */



    // Задание 4:

    // У QLineF есть метод intersect, который сильно упрощает задание, т.к. возвращает 1 или 0 в зависимости от пересечения

//    QLineF inter(dot1, dot2); // для QLineF нужны QPointF
//    QLineF left(0, screen.height());
//    QLineF up(0, screen.width());
//    QLineF right(screen.width(), screen.height());
//    QLineF down(screen.height(), screen.width());

}

void MainWindow::mousePressEvent(QMouseEvent *event) {


    /*
    // Задание 1:
    if (Qt::RightButton & event->buttons())
        start = event->pos();

    end = event->pos();

    if (!start.isNull())
       QMessageBox::information(this, "Distance", (start - end).manhattanLength() >= 40 ? "Too far" : "Close");
    */


    // manhattanLength() - сумма координат точки по x и y



    // Задание 2:
    if (Qt::LeftButton & event->buttons())
        circ = event->pos(); // при ЛКМ появляется пылесос

    if (Qt::RightButton & event->buttons())
        dots.append(event->pos()); // при ПКМ создаётся точка и добавляется в вектор с ними



    /*
    // Задание 3:
    if (Qt::LeftButton & event->buttons())
        dot1 = event->pos();

    if (Qt::RightButton & event->buttons())
        dot2 = event->pos();
    */

    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {

    // Задание 2:
    circ *= 0; // убираем пылесос после отжатия ЛКМ

    repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {

    // Задание 2:
    if (!circ.isNull()) {
        QPoint diff = event->pos() - circ; // расстояние, на которое сдвинулись

        for (int i = 0; i < dots.length(); i++) {
            if ((dots[i] - circ).manhattanLength() < 18) // если точки в радиусе пылесоса, то двигаем их (расстояние вычисляем через manhattanLength разницы координат)
                dots[i] += diff;
        }

        circ = event->pos(); // не забываем обновлять значение
    }


    repaint();
}
