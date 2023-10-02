#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPoint>
#include <QVector>


// Положение точки и прямой линии из учебника Ласло:
enum {LEFT, RIGHT, BEYOND, BEHIND, BETWEEN, ORIGIN, DESTINATION};

int classify(const QLineF &line, const QPointF &point) { // ссылка должна быть константной, иначе выдаёт ошибку (она и так константа, ведь мы не собираемся менять сами line и point)

    QPointF a = line.p2() - line.p1();
    QPointF b = point - line.p1();

    double check = a.x() * b.y() - b.x() * a.y();
    if (check > 0)
        return LEFT;
    if (check < 0)
        return RIGHT;
    if ((a.x() * b.x() < 0) || (a.y() * b.y() < 0))
        return BEHIND;
    if (a.manhattanLength() < b.manhattanLength())
        return BEYOND;
    if (line.p1() == point)
        return ORIGIN;
    if (line.p2() == point)
        return DESTINATION;
    return BETWEEN;
}


enum {NONE, FIRSTFULLOVERLAP, FIRSTPARTIALOVERLAP, SECONDPATRIALOVERLAP, SECONDFULLOVERLAP}; // типы наложения прямых: НИКАК, ПЕРВАЯ ПЕРЕКРЫВАЕТ ВТОРУЮ, ПЕРВАЯ ЧАСТИЧНО ПЕРЕКРЫВАЕТ ВТОРУЮ, ВТОРАЯ ЧАСТИЧНО ПЕРЕКРЫВАЕТ ПЕРВУЮ (разница в том, что в одном случае начальная точка первой линии находится за второй, а конечная - в ееё пределах, а в другом случае наоборот), ВТОРАЯ ПЕРЕКРЫВАЕТ ПЕРВУЮ.

int overlapType(const QLineF &side, const QLineF &line) {
    if ((classify(side, line.p1()) == BEHIND)&&(classify(side, line.p2()) == BEYOND))
        return FIRSTFULLOVERLAP;
    if ((classify(side, line.p1()) == BEHIND)&&(classify(side, line.p2()) == BETWEEN))
        return FIRSTPARTIALOVERLAP;
    if ((classify(side, line.p1()) == BETWEEN)&&(classify(side, line.p2()) == BEYOND))
        return SECONDPATRIALOVERLAP;
    if (((classify(side, line.p1()) == BETWEEN)||(classify(side, line.p1()) == ORIGIN))&&((classify(side, line.p2()) == BETWEEN)||(classify(side, line.p2()) == DESTINATION)))
        return SECONDFULLOVERLAP;
    return NONE;
}

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

    QLineF line; // линия, которая пересекает треугольник
    QLineF sides[3]; // стороны треугольника
    QPointF inters[3]; // точки пересечения со сторонами (в случае, если line не совпадает с side)

    if (triangleDots.length() == 3) { // рисуем треугольник и находим его стороны

        // Для проверок:
//        triangleDots[0].setX(175);
//        triangleDots[0].setY(75);
//        triangleDots[1].setX(79);
//        triangleDots[1].setY(236);
//        triangleDots[2].setX(272);
//        triangleDots[2].setY(221);

        painter.drawPolygon(triangleDots);
        sides[0].setPoints(triangleDots[0], triangleDots[1]);
        sides[1].setPoints(triangleDots[1], triangleDots[2]);
        sides[2].setPoints(triangleDots[0], triangleDots[2]);
    }

    QPen blue(Qt::blue); // точку, пересекающую треугольник делаем синей
    painter.setPen(blue);

    if (lineDots.length() == 2) { // находим и рисуем линию, которая может пересекать треугольник

        // Для проверок:
//        lineDots[0].setX(127);
//        lineDots[0].setY(155.5);
//        lineDots[1].setX(79);
//        lineDots[1].setY(236);

        line.setPoints(lineDots[0], lineDots[1]);
        painter.drawLine(line);
    }

    QPen red(Qt::red, 3); // общие точки либо общие отрезки закрашиваем красным
    painter.setPen(red);

    if (lineDots.length() + triangleDots.length() == 5)  // то есть если все точки, включая пересекающую прямую и точки треугольника были проставлены
        for (int i = 0; i < 3; i++) { // делаем эти проверки для каждой из сторон треугольника
            if (line.intersects(sides[i], &inters[i]) == 1) // если пересекает, то рисуем эту точку
                intersectionDots.append(inters[i]);
            else if (!line.intersects(sides[i], &inters[i])) // если лежит параллельно, то проверяем, как именно и затем закрашиваем область пересечения (тоже прямая), если она будет
                switch (overlapType(sides[i], line)) {
                case FIRSTFULLOVERLAP:
                    painter.drawLine(sides[i]); // закрашиваем всю сторону треугольника, т.к. она лежит полностью в нашей линии
                    break;
                case FIRSTPARTIALOVERLAP:
                    painter.drawLine(sides[i].p1(), line.p2()); // закрашиваем отрезок от первой координаты стороны трегольника до второй коодринаты нашей линии
                    break;
                case SECONDPATRIALOVERLAP:
                    painter.drawLine(line.p1(), sides[i].p2()); // закрашиваем отрезок от первой координаты нашей линии до второй коодринаты стороны треугольника
                    break;
                case SECONDFULLOVERLAP:
                    painter.drawLine(line); // закрашиваем всю нашу линию, т.к. она лежит полностью в стороне треугольника
                    break;
                default:
                    break;
                }
        }

    if (intersectionDots.length() > 0)
        painter.drawPoints(intersectionDots); // рисуем точки пересечения, если таковые будут
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    if ((Qt::LeftButton & event->buttons())&&(triangleDots.length() < 3))
        triangleDots.append(event->pos());

    if ((Qt::LeftButton & event->buttons())&&(Qt::ControlModifier & event->modifiers())) { // удалить треугольник
        triangleDots.clear();
        intersectionDots.clear();
    }

    if ((Qt::RightButton & event->buttons())&&(lineDots.length() < 2))
        lineDots.append(event->pos());

    if ((Qt::RightButton & event->buttons())&&(Qt::ControlModifier & event->modifiers())) { // удалить прямую
        lineDots.clear();
        intersectionDots.clear();
    }

    repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
}
