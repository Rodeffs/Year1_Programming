#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcircle.h> // вынес в отдельный файл, чтобы не засорять здесь место
#include <path.h>

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

private:
    Ui::MainWindow *ui;

    QPoint ant; // муравей
    QPoint fly; // муха

    QRect screen;

    QCircle tree;

    VecPoints net; // точки сетки
    Path path; // искомый путь
};

#endif // MAINWINDOW_H
