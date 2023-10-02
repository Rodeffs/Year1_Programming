#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Здесь прописываем то, что будем использовать в mainwindow, например, трекинг мыши и переменные координат

namespace Ui {
    class MainWindow; // создаём класс, но его тело находится ниже
}

class MainWindow : public QMainWindow // наследование классов
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent *); // ПКМ -> Рефакторинг -> Добавить реализацию в mainwindow.cpp

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);



private:
    Ui::MainWindow *ui;
    int x, y; // координаты начала
    int x1, y1; // координаты конца
    bool clicked = false; // проверка, было ли нажатие мыши, изначально false
};

#endif // MAINWINDOW_H
