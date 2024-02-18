#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPoint>
#include <QVector>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#define s 20 // размер сетки

// Условие задачи: вывести кратчайший путь между муравьём и мухой, при этом, чтобы он не пересекал дерево

// Основная логика поиска пути находится в path.h

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

QPoint optimalPoint(QPoint cur, QCircle tree, VecPoints net) { // поиск ближайшей точки сетки к кликнутой
    QPoint optimalPoint;
    int minD = s;
    for (int i = 0; i < net.size(); i++) {
        if (QCircle(cur, s).containsPoint(net[i])&&(!tree.containsPoint(net[i]))) { // находим ближайшую точку сетки к клику
            int diff = (cur - net[i]).manhattanLength();
            if (diff < minD)
                minD = diff, optimalPoint = net[i];
        }
    }
    return optimalPoint;
}

void MainWindow::paintEvent(QPaintEvent *) {

    QPainter painter(this);

    int w = contentsRect().width(), h = contentsRect().height();

    for (int x = 0; x < w; x += s)
        painter.drawLine(QPoint(x, 0), QPoint(x, h)); // рисуем линию сетки по x

    for (int y = 0; y < h; y += s)
        painter.drawLine(QPoint(0, y), QPoint(w, y)); // рисуем линию сетки по y

    painter.setPen(QPen(QColor(128, 64, 48)));
    painter.setBrush(QBrush(QColor(128, 64, 48)));
    if (!tree.getCentre().isNull())
        painter.drawEllipse(tree.getCentre(), tree.getRadius(), tree.getRadius());

    painter.setPen(QPen(QColor(255, 165, 0), 4));
    if (path.size() > 1)
        for (int i = 1; i < path.size(); i++)
            painter.drawLine(path.getPath()[i-1], path.getPath()[i]);

    painter.setPen(QPen(Qt::red));
    painter.setBrush(QBrush(Qt::red));
    if (!ant.isNull())
        painter.drawEllipse(ant, 4, 4);

    painter.setPen(QPen(Qt::blue));
    painter.setBrush(QBrush (Qt::blue));
    if (!fly.isNull())
        painter.drawEllipse(fly, 4, 4);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    QPoint cur(event->pos());

    if (screen != contentsRect()) { // нам нужно знать количество всех возможных точек для правильной работы алгоритма, поэтому находим размеры экрана и обновляем их при изменении окна
        net.clear();
        screen = contentsRect();
        for (int x = 0; x < screen.width(); x += s)
            for (int y = 0; y < screen.height(); y += s)
                net.append(QPoint(x, y)); // муравей или муха могут находиться только на точках сетки, т.е. их пересечение
    }

    if (event->buttons() & Qt::LeftButton) { // ЛКМ - дерево
        tree = {cur, 70 + (rand()% 130)};  // случайный радиус дерева, первое число - от какого минимально, второе число (на проверку остатка) - какой максимальным (в сумме в первым)
        ant *= tree.containsPoint(ant) ? 0 : 1; // если муравей внутри дерева, то убираем муравья
        fly *= tree.containsPoint(fly) ? 0 : 1; // если муха внутри дерева, то убираем муху
        for (int i = 0; i < path.size(); i++) // если путь внутри дерева, то очищаем его
            if (tree.containsPoint(path.getPath()[i]))
                path.clear();
    }

    if ((event->buttons() & Qt::RightButton)&&!(event->modifiers() & Qt::ControlModifier)) { // ПКМ - муравей
        QPoint oP = optimalPoint(cur, tree, net);
        ant *= (oP != ant) ? 0 : 1; // обновляем значения при послед. кликах, если точка сдвинулась
        if (oP != fly) // чтобы не наложились друг на друга
            ant = oP;
    }

    if ((event->buttons() & Qt::RightButton)&&(event->modifiers() & Qt::ControlModifier)) { // ПКМ + ctrl - муха
        QPoint oP = optimalPoint(cur, tree, net);
        fly *= (oP != fly) ? 0 : 1; // обновляем значения при послед. кликах, если точка сдвинулась
        if (oP != ant)  // чтобы не наложились друг на друга
            fly = oP;
    }

    path.clear(); // очищаем предыдущий путь, когда меняются координаты
    if (!fly.isNull() && !ant.isNull())
        path.findPath(ant, fly, tree, net, screen, s);

    repaint();
}
