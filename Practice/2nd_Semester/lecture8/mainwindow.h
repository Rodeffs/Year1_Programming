#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "balls.h"
#include "cballs.h"

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

    Balls *bim = nullptr; // сделаем объект через указатель, чтобы различать "живой" от "мёртвого", т.е. когда мы ещё не кликнули, его не будет существовать
};

#endif // MAINWINDOW_H
