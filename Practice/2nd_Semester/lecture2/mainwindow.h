#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

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

//    QPoint coord[10]; - массив координатных точек
    QVector<QPoint> coord;

    QPoint capture; // координаты точки, где была нажата ПКМ

//    int i = 0; - сколько кликов ЛКМ, для векторов не нужно
};

#endif // MAINWINDOW_H
