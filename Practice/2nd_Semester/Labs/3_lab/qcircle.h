#ifndef QCIRCLE_H
#define QCIRCLE_H

#include <QMainWindow>

typedef QVector<QPoint> VecPoints;

class QCircle { // решил попробовать написать класс, чтобы красиво было
private:

    QPoint m_centre;
    int m_radius;

public:

    QCircle () {}

    QCircle (QPoint centre, int radius) {
        m_centre = centre;
        m_radius = radius;
    }

    ~QCircle() {}

    void setCentre(QPoint centre) {
        m_centre = centre;
    }

    void setRadius(int radius) {
        m_radius = radius;
    }

    QPoint getCentre() {
        return m_centre;
    }

    int getRadius() {
        return m_radius;
    }

    bool containsPoint(QPoint p) { // проверка, включает ли окружность точку
        QPoint dp = m_centre - p;
        return (QPoint::dotProduct(dp, dp) <= m_radius * m_radius) ? true : false;
    }

    bool isNull() { // проверка, есть ли вообще эта окружность
        return m_centre.isNull() ? true : false;
    }

    int minX(VecPoints net, QRect screen, int s) { // нахождение крайней левой границы по x (т.е. максимально допустимые ближайшие к ней точки)
        int minX = screen.width();
        for (int i = 0; i < net.size(); i++)
            if (this->containsPoint(net[i]))
                minX = net[i].x() < minX ? net[i].x() : minX;
        return minX - s;
    }

    int minY(VecPoints net, QRect screen, int s) { // нахождение крайней верхней границы по y (т.е. максимально допустимые ближайшие к ней точки)
        int minY = screen.height();
        for (int i = 0; i < net.size(); i++)
            if (this->containsPoint(net[i]))
                minY = net[i].y() < minY ? net[i].y() : minY;
        return minY - s;
    }

    int maxX(VecPoints net, int s) { // нахождение крайней правой границы по x (т.е. максимально допустимые ближайшие к ней точки)
        int maxX = 0;
        for (int i = 0; i < net.size(); i++)
            if (this->containsPoint(net[i]))
                maxX = net[i].x() > maxX ? net[i].x() : maxX;
        return maxX + s;
    }

    int maxY(VecPoints net, int s) { // нахождение крайней нижней границы по y (т.е. максимально допустимые ближайшие к ней точки)
        int maxY = 0;
        for (int i = 0; i < net.size(); i++)
            if (this->containsPoint(net[i]))
                maxY = net[i].y() > maxY ? net[i].y() : maxY;
        return maxY + s;
    }

    int distToLeft(QPoint temp, VecPoints net, QRect screen, int s) { // расстояние от точки до левой границы окружности (если выходит за границы экрана, то возвращаем максимально возможное расстояние, в данном случае размер экрана)
        return (this->minX(net, screen, s) < 0) ? screen.width() : (temp - QPoint(this->minX(net, screen, s), temp.y())).manhattanLength();
    }

    int distToTop(QPoint temp, VecPoints net, QRect screen, int s) { // расстояние от точки до верхней границы окружности (если выходит за границы экрана, то возвращаем максимально возможное расстояние, в данном случае размер экрана)
        return (this->minY(net, screen, s) < 0) ? screen.height() : (temp - QPoint(temp.x(), this->minY(net, screen, s))).manhattanLength();
    }

    int distToRight(QPoint temp, VecPoints net, QRect screen, int s) { // расстояние от точки до правой границы окружности (если выходит за границы экрана, то возвращаем максимально возможное расстояние, в данном случае размер экрана)
        return (this->maxX(net, s) >= screen.width()) ? screen.width() : (temp - QPoint(this->maxX(net, s), temp.y())).manhattanLength();
    }

    int distToBottom(QPoint temp, VecPoints net, QRect screen, int s) { // расстояние от точки до нижней границы окружности (если выходит за границы экрана, то возвращаем максимально возможное расстояние, в данном случае размер экрана)
        return (this->maxY(net, s) >= screen.height()) ? screen.height() : (temp - QPoint(temp.x(), this->maxY(net, s))).manhattanLength();
    }

};

#endif // QCIRCLE_H
