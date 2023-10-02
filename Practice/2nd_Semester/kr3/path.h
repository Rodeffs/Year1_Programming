#ifndef PATH_H
#define PATH_H

#include <qcircle.h>

// Здесь находится основная логика поиска пути

typedef QVector<QPoint> VecPoints;

enum { LEFT, UP, RIGHT, DOWN };

class Path { // наш искомый путь
private:

    VecPoints m_path;

    int directionX(int left, int right) { // находим ближайшую границу окружности либо левую, либо правую
        return left <= right ? LEFT : RIGHT;
    }

    int directionY(int up, int down) { // находим ближайшую границу окружности либо верхнюю, либо нижнюю
        return up <= down ? UP : DOWN;
    }

    int closestBorder(int left, int up, int right, int down) { // находим ближайшую любую границу окружности
        int min = INT_MAX;
        min = (left < min)  ? left  : min;
        min = (up < min)    ? up    : min;
        min = (right < min) ? right : min;
        min = (down < min)  ? down  : min;
        return min == left ? LEFT : min == up ? UP : min == right ? RIGHT : DOWN;
    }

    VecPoints directPath(QPoint begin, QPoint end, QCircle tree, int s) { // для поиска прямого пути, когда дерево уже не помеха

        VecPoints path1, path2; // 1) путь сначала вбок, потом вверх либо вниз  2) путь сначала вверх либо вниз, потом вбок

        QPoint temp(begin); // начинаем от муравья

        while (temp.x() != end.x()) { // идём вбок, пока либо не попадём в окружность, либо пока не дойдём по координаты x конечной точки
            if (temp.x() < end.x())
                temp.rx() += s, path1.append(temp);
            if (temp.x() > end.x())
                temp.rx() -= s, path1.append(temp);
            if (tree.containsPoint(temp)) {
                path1.clear();
                break;
            }
        }

        if (!path1.isEmpty()) // смысла искать дальше нет, если мы уже пересекли окружность
            while (temp.y() != end.y()) { // идём вверх или вниз, пока либо не попадём в окружность, либо пока не дойдём по координаты y конечной точки
                if (temp.y() < end.y())
                    temp.ry() += s, path1.append(temp);
                if (temp.y() > end.y())
                    temp.ry() -= s, path1.append(temp);
                if (tree.containsPoint(temp)) {
                    path1.clear();
                    break;
                }
            }

        if(!path1.isEmpty()) // если первый путь подошёл, смысла искать второй нет
            return path1;

        temp = begin;

        while (temp.y() != end.y()) {
            if (temp.y() < end.y())
                temp.ry() += s, path2.append(temp);
            if (temp.y() > end.y())
                temp.ry() -= s, path2.append(temp);
            if (tree.containsPoint(temp)) {
                path2.clear();
                break;
            }
        }

        if (!path2.isEmpty())
            while (temp.x() != end.x()) {
                if (temp.x() < end.x())
                    temp.rx() += s, path2.append(temp);
                if (temp.x() > end.x())
                    temp.rx() -= s, path2.append(temp);
                if (tree.containsPoint(temp)) {
                    path2.clear();
                    break;
                }
            }

        return path2; // оба эти пути имеют одинаковую длину, однако нам нужен из них тот, который не пересёк окружность. Если оба пересекли, то вернётся пустой вектор
    }


public:

    Path() {}

    ~Path() {}

    Path(VecPoints path) {
        m_path = path;
    }

    void setPath(VecPoints path) {
        m_path = path;
    }

    VecPoints getPath() {
        return m_path;
    }

    int size() {
        return m_path.size();
    }

    void clear() {
        m_path.clear();
    }

    void findPath(QPoint begin, QPoint end, QCircle tree, VecPoints net, QRect screen, int s) { // основной метод поиска пути

        VecPoints tempPath, shortPath = directPath(begin, end, tree, s); // искомый путь и прямой путь
        tempPath.append(begin);

        QPoint temp(begin); // начинаем от муравья

        int minX = tree.minX(net, screen, s), minY = tree.minY(net, screen, s), maxX = tree.maxX(net, s), maxY = tree.maxY(net, s); // границы окружности

        int closestDir = closestBorder(tree.distToLeft(temp, net, screen, s), tree.distToTop(temp, net, screen, s), tree.distToRight(temp, net, screen, s), tree.distToBottom(temp, net, screen, s)); // ближайшее направление к границе окружности

        while ((temp.x() != maxX)&&(temp.x() != minX)&&(temp.y() != maxY)&&(temp.y() != minY)&&shortPath.isEmpty()) { // муравей идёт к ближайшей границе окружности

            switch (closestDir) {
            case LEFT:
                if (temp.x() < minX)
                    temp.rx() += s, tempPath.append(temp);
                if (temp.x() > minX)
                    temp.rx() -= s, tempPath.append(temp);
                break;
            case RIGHT:
                if (temp.x() < maxX)
                    temp.rx() += s, tempPath.append(temp);
                if (temp.x() > maxX)
                    temp.rx() -= s, tempPath.append(temp);
                break;
            case UP:
                if (temp.y() < minY)
                    temp.ry() += s, tempPath.append(temp);
                if (temp.y() > minY)
                    temp.ry() -= s, tempPath.append(temp);
                break;
            case DOWN:
                if (temp.y() < maxY)
                    temp.ry() += s, tempPath.append(temp);
                if (temp.y() > maxY)
                    temp.ry() -= s, tempPath.append(temp);
            }

            shortPath = directPath(temp, end, tree, s);
        }

        int dirX = directionX(tree.distToLeft(end, net, screen, s), tree.distToRight(end, net, screen, s));
        int dirY = directionY(tree.distToTop(end, net, screen, s), tree.distToBottom(end, net, screen, s));

        if ((temp.x() == minX) || (temp.x() == maxX)) // потом муравей, в зависимости от того на какой границе он находится, выбирает направление по другой координате и идёт к ближайшей границе мухи, параллельно каждый раз проверяя прямой путь
            while (shortPath.isEmpty()&&(temp.y() != maxY)&&(temp.y() != minY)) {

                if ((temp.y() == maxY)||(temp.y() == minY))
                    break;

                if (dirY == UP) {
                    if (temp.y() < minY)
                        temp.ry() += s, tempPath.append(temp);
                    if (temp.y() > minY)
                        temp.ry() -= s, tempPath.append(temp);
                }

                if (dirY == DOWN) {
                    if (temp.y() < maxY)
                        temp.ry() += s, tempPath.append(temp);
                    if (temp.y() > maxY)
                        temp.ry() -= s, tempPath.append(temp);
                }

                shortPath = directPath(temp, end, tree, s);
            }

        if ((temp.y() == minY) || (temp.y() == maxY))
            while (shortPath.isEmpty()&&(temp.x() != maxX)&&(temp.x() != minX)) {

                if ((temp.x() == maxX)||(temp.x() == minX))
                    break;

                if (dirX == LEFT) {
                    if (temp.x() < minX)
                        temp.rx() += s, tempPath.append(temp);
                    if (temp.x() > minX)
                        temp.rx() -= s, tempPath.append(temp);
                }

                if (dirX == RIGHT) {
                    if (temp.x() < maxX)
                        temp.rx() += s, tempPath.append(temp);
                    if (temp.x() > maxX)
                        temp.rx() -= s, tempPath.append(temp);
                }

                shortPath = directPath(temp, end, tree, s);
        }

        for (int i = 0; i < shortPath.size(); i++)
            tempPath.append(shortPath[i]);

        this->setPath(tempPath);
    }
};

#endif // PATH_H
