#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "balls.h"

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

public slots: // слоты могут принимать сигналы в отличие от обычных методов
    void update();

private:
    Ui::MainWindow *ui;

    Balls bim;
};

#endif // MAINWINDOW_H
