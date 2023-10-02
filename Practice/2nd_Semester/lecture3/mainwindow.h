#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;

    /*
    // Задание 1:
    QPoint start;
    QPoint end;
    */



    // Задание 2:
    QVector<QPoint> dots; // вектор с точками
    QPoint circ; // пылесос



    /*
    // Задание 3:
    QPoint dot1;
    QPoint dot2;
    */


    // Задание 4:
//    QPointF dot1;
//    QPointF dot2;
};

#endif // MAINWINDOW_H
