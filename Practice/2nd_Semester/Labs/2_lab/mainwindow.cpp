#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPoint>
#include <QVector>

// Условие контрольной работы 2: нельзя, чтобы клумбы (красные) накладывались друг на друга, либо опрокидовались в бассейн (синий), т.е. чтобы их центр был в бассейне
/* Дополнительное условия:
 1) квадратные клумбы = 20% от бассейна
 2) квадратные клумбы можно ставить друг на друга, если площадь их пересечения > 60%
 3) квадратные клумбы можно ставить на круглые, если они целиком будут в круглых
 4) круглые на круглые нельзя ставить
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool intersectionRect(QRectF r1, QRectF r2) { // проверка на площадь пересечения прямоугольных клумб
    QRectF inter(r1 & r2); // пересечение клумб
    if (((inter.width() * inter.height()) / (r1.width() * r1.height())) > 0.6) // если пересекаютя более чем на 60%
        return true;
    return false;
}

bool containsPoint(QCircle c, QPointF p) { // пересекает ли точка окружность
    QPointF dp = c.center - p;
    return (QPointF::dotProduct(dp, dp) <= c.radius * c.radius) ? true : false;
}

bool containsCircle(QCircle c1, QCircle c2) { // пересекает ли окружность окружность
    QPointF dp = c1.center - c2.center;
    return (QPointF::dotProduct(dp, dp) <= (c1.radius + c2.radius)*(c1.radius + c2.radius)) ? true : false; // т.е. если расстояние между центрами больше суммы радиусов
}

bool containsRect1(QCircle c, QRectF r) { // находится ли квадратная клумба в круглой 1 проверка
    return containsPoint(c, r.topLeft())&&containsPoint(c, r.bottomRight());
}

bool containsRect2(QCircle c, QRectF r) { // находится ли квадратная клумба в круглой 2 проверка
    return r.marginsAdded(QMargins(c.radius, c.radius, c.radius, c.radius)).contains(c.center); // QMargins "раздувает" наш прямоугольник на заданное значение, затем проверяем, пересекает ли он центр окружности
}

void MainWindow::paintEvent(QPaintEvent *) {

    QPainter painter (this);

    QImage waterTexture(":/src/src/water.jpg");
    QImage grassTexture(":/src/src/grass.jpg");

    QBrush water, grass, potCircle(QColor(255, 15, 203, 255)), potSquare(QColor(128, 0, 0, 255)); // не нашёл нормальной текстуры для клумб

    water.setTextureImage(waterTexture);
    grass.setTextureImage(grassTexture);

    painter.setBrush(grass);
    painter.drawRect(contentsRect());

    pool = QRectF(QPointF(200, 200), QSizeF(250, 150)); // задаём бассейн
    painter.setBrush(water);
    painter.drawRect(pool);

    painter.setBrush(potCircle);
    for (int i = 0; i < circles.size(); i++) // рисуем круглые клумбы
        painter.drawEllipse(circles[i].center, circles[i].radius, circles[i].radius);

    painter.setBrush(potSquare);
    for (int i = 0; i < squares.size(); i++) // рисуем квадратные клумбы
        painter.drawRect(squares[i]); // т.к. у нас есть центра квадрата, то нужно отнять от него половину длины стороны, чтобы получить левый верхний угол
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    bool doNotAppend = false; // для проверок, если хотя бы одна не пройдёт, то точку не включаем

    if (Qt::LeftButton & event->buttons()) { // добавляем круглую клумбу

        QCircle tempCircle = {event->pos(), 30};

        if (pool.contains(tempCircle.center)) // если центр внутри бассейна, то исключаем
            doNotAppend = true;

        for (int i = 0; i < circles.size(); i++)
            if (containsCircle(circles[i], tempCircle)) { // проверяем круглые с круглыми
                doNotAppend = true;
                break;
            }

        for (int i = 0; i < squares.size(); i++)
            if (containsRect1(tempCircle, squares[i])) { // проверяем круглые с квадратными
                doNotAppend = true;
                break;
            }

        if (!doNotAppend)
            circles.append(tempCircle);
    }

    if (Qt::RightButton & event->buttons()) { // добавляем квадратные клумбы

        QRectF tempRect(event->pos(), pool.size() * 0.2);

        if (pool.contains(tempRect.center())) // если центр прямоугольной клумбы внутри бассейна, то его не включаем
            doNotAppend = true;

        for (int i = 0; i < squares.size(); i++)
            if (intersectionRect(tempRect, squares[i])) { // проверяем квадратные с квадратными
                doNotAppend = true;
                break;
            }

        for (int i = 0; i < circles.size(); i++) {
            if (containsRect1(circles[i], tempRect)) // проверяем квадратные с круглыми
                break; // если нашли хотя бы один квадрат, который внутри окружности, то прекращаем проверку
            if (containsRect2(circles[i], tempRect))
                doNotAppend = true; // если ни один прямоугольник не находится внутри круга, то здесь два случая: либо он вне круга, либо пересекает его, нас не устраивает последний случай, поэтому и проверяем на него
        }

        if (!doNotAppend)
            squares.append(tempRect);
    }

    repaint();
}

/* Старый код:
void MainWindow::mousePressEvent(QMouseEvent *event) {

    double dist = sqrt(200) + 10; // сумма расстояний из центра квадрата 20x20 до его вершины и радиуса круга, нужна для проверок расстояния между разными клумбами

    QRect tempRect(event->pos() - QPoint(10, 10), QSize(20, 20)); // квадрат с цетром где кликнули, нужен для проверок и для квадратных клумб

    bool check = false; // для проверок, если хотя бы одна не пройдёт, то точку не включаем

    if (pool.contains(event->pos())) // если точка внутри бассейна, то её сразу исключаем
        check = true;

    if (Qt::LeftButton & event->buttons()) {

        for (int i = 0; i < circles.size(); i++) {
            double diff = sqrt(pow((circles[i].x() - event->x()), 2)+pow((circles[i].y() - event->y()), 2)); // manhattanlength здесь не подойдёт, нам нужно именно расстояние по прямой между двумя точками
    //            QPoint diff = event->pos() - circles[i];

            QRect arrRect(circles[i] - QPoint(10, 10), QSize(20, 20));

    //            if (diff.manhattanLength() < 20) { // такая проверка неверно отображает клумбы, они налегают друг на друга
            if (diff < 20) {
                check = true;
                break;
            }
        }

        for (int i = 0; i < squares.size(); i++) {
            double diff = sqrt(pow((squares[i].x() - event->x()), 2)+pow((squares[i].y() - event->y()), 2)); // manhattanlength здесь не подойдёт, нам нужно именно расстояние по прямой между двумя точками
    //            QPoint diff = event->pos() - squares[i];

            QRect arrRect(squares[i] - QPoint(10, 10), QSize(20, 20));

            if ((diff < dist)&&(arrRect.intersects(tempRect))) { // двойная проверка, таким образом одновременно клумбы не пересекаются друг с другом ни углами, ни сторонами
    //            if (diff.manhattanLength() < dist) { // такая проверка неверно отображает клумбы (неправильно считается расстояние по диагонали), они налегают друг на друга
                check = true;
                break;
            }
        }

        if (!check)
            circles.append(event->pos());
    }


    if (Qt::RightButton & event->buttons()) {

        for (int i = 0; i < squares.size(); i++) {
            QRect arrRect(squares[i] - QPoint(10, 10), QSize(20, 20));

            if (arrRect.intersects(tempRect)) { // если один квадрат пересекается с другим, то его не включаем
                check = true;
                break;
            }
        }

        for (int i = 0; i < circles.size(); i++) {
            double diff = sqrt(pow((circles[i].x() - event->x()), 2)+pow((circles[i].y() - event->y()), 2)); // manhattanlength здесь не подойдёт, нам нужно именно расстояние по прямой между двумя точками
    //            QPoint diff = event->pos() - circles[i];

            QRect arrRect(circles[i] - QPoint(10, 10), QSize(20, 20));

    //            if (diff.manhattanLength() < dist) { // такая проверка неверно отображает клумбы (неправильно считается расстояние по диагонали), они налегают друг на друга
            if ((diff < dist)&&(arrRect.intersects(tempRect))) { // двойная проверка, таким образом одновременно клумбы не пересекаются друг с другом ни углами, ни сторонами
                check = true;
                break;
            }
        }

        if (!check)
            squares.append(event->pos());
    }

    repaint();
}
*/
