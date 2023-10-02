#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>

#include <QPoint> // QPoint уже включён в QPainter, однако на всякий случай лучше прописать отдельно, т.к. программа может неправильно скомпилировать
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

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


    // Задание: при каждом клике отрисовать ломанную, вершины которой - это координаты клика. При зажатой ПКМ можно двигать рисунок
    for (int j = 1; j < coord.size(); j++)
        painter.drawLine(coord[j-1], coord[j]);

//    int j = 1;
//    while (!coord[j].isNull()) {
//        painter.drawLine(coord[j-1], coord[j]);
//        j++;
//    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Задание: при каждом клике отрисовать ломанную, вершины которой - это координаты клика. При зажатой ПКМ можно двигать рисунок
    if (!(Qt::RightButton & event->buttons()))
        coord.append(event->pos());

    if (Qt::RightButton & event->buttons())
        capture = event->pos();

    repaint();


    /* Вектора

    QVector<QPoint> vec; - так создаём вектор

    У вектора нет размерности, это "резиновый" массив
    В <> пишем тип данных, которые хранит вектор
    К элементам вектора можно также обращаться через [], как и с массивами
    Стоит отметить, что индексация списка обходится дорого в плане памяти, это нужно учитывать лишь тогла, когда в списке более 100 элементов

    vec.size(); - этот метод говорит, сколько элементов в векторе
    vec.append(); - этот метод добавляет элемент в конец вектора
    */

#if 0
    // QPoint - это точка, в скобках указываем её декартовые координаты на плоскости

    int x = 100, y;

    QPoint w = {100,150};

    QPoint p(100,150), q; // также, как и с типом переменных, можно сразу инициализировать переменную, а также инициализировать сразу несколько переменных
    // мы q не проинициализировали, в таком случае default constructor даст ему значения по умолчанию

    p.x(); // геттер (прописан в классе QPoint), возвращает координату x для p, которая хранится на стеке (постоянная память)
    event->x(); // тоже геттер, стрелочка нужна, т.к. event - это указатель, а он хранится на хипе (оперативная память)

    q = QPoint(200, 200); // можно навести курсор на QPoint и нажать F1 для просмотра документации


    p.setX(110); // сеттер (прописан в классе QPoint), присваиваем значение координате x точки p

//    p.setX(p.() + 10); - увеличиваем значение координаты x на 10
    p.rx() += 10; // аналогично, rx() - reference x, т.е. ссылка на x, таким образом можем легко изменить значение переменных


    // есть ещё метод operator, нужен для работы с векторами (т.е. умножить а 0.5 - значит точка будет на середине отрезка, сложенить две точки - как с векторами и т.д.)


//    p == q; - такая операция недопустима, т.к. она не определена в классе


    QPoint p = QPoint(event->x(), event->y());
    QPoint q = event->pos(); // аналогичная запись, что и выше
#endif
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    capture *= 0; // когда отпустили
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Задание: при каждом клике отрисовать ломанную, вершины которой - это координаты клика. При зажатой ПКМ можно двигать рисунок
    if (!capture.isNull()) {
        QPoint diff = event->pos() - capture; // расстояние, на которое сдвинулись

        for (int j = 0; j < coord.size(); j++)
            coord[j] += diff;

        capture = event->pos(); // !!! ВАЖНО: после завершения цикла нужно обновлять значение capture, иначе возникает ускорение из-за того, что мы будем вычитаем старые значения capture
    }

    repaint();
}
