#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct Circle {
    QPointF center;
    double radius;
}QCircle;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent (QPaintEvent *);

    void mousePressEvent (QMouseEvent *event);

private:
    Ui::MainWindow *ui;

    QVector<QRectF> squares;
    QVector<QCircle> circles;
    QRectF pool;
};
#endif // MAINWINDOW_H
