#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPoint>
#include <QVector>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

                                            /*          Тема: Создание анимации          */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
                                            /*          Работа с таймером:          */

    QTimer *timer = new QTimer(); // создаём таймер на хипе для того, чтобы он не умирал после завершение блока этого кода. Таймер нужно include отдельно

    connect(timer, SIGNAL(timeout()), this, SLOT(update())); // что подключаем, какой сигнал посылаем, кому посылаем и в какой слот

    timer->start(50); // наачало таймера, в скобках указывается интервал отсчёта в миллисекундах
//    timer->stop(); - остановка таймера
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (bim)
        bim->draw(&painter); // т.к. метод принимает указатель, то передаём ему ссылку
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    bim = new CBalls(event->x(), event->y(), 30, 10, -20); // нужно создать объект, иначе не сможем присвоить значения. Создаём через конструктор, которому сразу присвоим значения

//    bim->setX(event->x()), bim->setY(event->y());

    repaint();
}

void MainWindow::update() // этот метод будет вызываться про обновлении таймера
{
//    qDebug("tick");

//    if (bim != nullptr) - не оптимально
    if (bim)
        bim->move(contentsRect().width(), contentsRect().height());

    repaint();
}
