#ifndef PATH_H
#define PATH_H

#include <qcircle.h>

// Здесь находится основная логика поиска пути

// Идея состоит в том, что сначала муравей идёт к ближайшей границе окружности, а потом начинает её обходить по кругу в разных направлениях, попутно ища прямой путь до мухи. В конце возвращаем кратчайший путь

typedef QVector<QPoint> VecPoints;

enum { LEFT, UP, RIGHT, DOWN };

enum {CLOCKWISE, COUNTERCLOCKWISE};

class Path { // наш искомый путь
private:

    VecPoints m_path;

    int directionX(int left, int right) { // находим ближайшую границу окружности либо левую, либо правую
        return left <= right ? LEFT : RIGHT;
    }

    int directionY(int up, int down) { // находим ближайшую границу окружности либо верхнюю, либо нижнюю
        return up <= down ? UP : DOWN;
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

    VecPoints getToBorder(QPoint begin, QPoint end, QCircle tree, int closestSide, int s, int minX, int minY, int maxX, int maxY) {
        QPoint temp(begin);
        VecPoints tempPath, shortPath = directPath(begin, end, tree, s);
        tempPath.append(begin);

        while ((temp.x() != maxX)&&(temp.x() != minX)&&(temp.y() != maxY)&&(temp.y() != minY)&&shortPath.isEmpty()) { // муравей идёт к ближайшей границе окружности

            switch (closestSide) {
            case LEFT:
                if (temp.x() < minX)
                    temp.rx() += s, tempPath.append(temp), shortPath = directPath(temp, end, tree, s);
                if (temp.x() > minX)
                    temp.rx() -= s, tempPath.append(temp), shortPath = directPath(temp, end, tree, s);
                break;
            case RIGHT:
                if (temp.x() < maxX)
                    temp.rx() += s, tempPath.append(temp), shortPath = directPath(temp, end, tree, s);
                if (temp.x() > maxX)
                    temp.rx() -= s, tempPath.append(temp), shortPath = directPath(temp, end, tree, s);
                break;
            case UP:
                if (temp.y() < minY)
                    temp.ry() += s, tempPath.append(temp), shortPath = directPath(temp, end, tree, s);
                if (temp.y() > minY)
                    temp.ry() -= s, tempPath.append(temp), shortPath = directPath(temp, end, tree, s);
                break;
            case DOWN:
                if (temp.y() < maxY)
                    temp.ry() += s, tempPath.append(temp), shortPath = directPath(temp, end, tree, s);
                if (temp.y() > maxY)
                    temp.ry() -= s, tempPath.append(temp), shortPath = directPath(temp, end, tree, s);
            }
        }

        for (int i = 0; i < shortPath.size(); i++)
            tempPath.append(shortPath[i]);
        return tempPath;
    }

    VecPoints clockMove(QPoint begin, QPoint end, QCircle tree, QRect screen, int clock, int s, int minX, int minY, int maxX, int maxY) {
        QPoint temp(begin);
        VecPoints tempPath, shortPath = directPath(begin, end, tree, s);
        int check1 = (clock == CLOCKWISE) ? maxY : minY, check2 = (clock == CLOCKWISE) ? minX : maxX, check3 = (clock == CLOCKWISE) ? minY : maxY, check4 = (clock == CLOCKWISE) ? maxX : minX;

        if (temp.y() == check1)
            while ((temp.x() > minX)&&shortPath.isEmpty()) {
                temp.rx() -= s;
                if (temp.x() < 0) {
                    tempPath.clear();
                    return tempPath;
                }
                tempPath.append(temp), shortPath = directPath(temp, end, tree, s);
            }

        if (temp.x() == check2)
            while ((temp.y() > minY)&&shortPath.isEmpty()) {
                temp.ry() -= s;
                if (temp.y() < 0) {
                    tempPath.clear();
                    return tempPath;
                }
                tempPath.append(temp), shortPath = directPath(temp, end, tree, s);
            }

        if (temp.y() == check3)
            while ((temp.x() < maxX)&&shortPath.isEmpty()) {
                temp.rx() += s;
                if (temp.x() > screen.width()) {
                    tempPath.clear();
                    return tempPath;
                }
                tempPath.append(temp), shortPath = directPath(temp, end, tree, s);
            }

        if (temp.x() == check4)
            while ((temp.y() < maxY)&&shortPath.isEmpty()) {
                temp.ry() += s;
                if (temp.y() > screen.height()) {
                    tempPath.clear();
                    return tempPath;
                }
                tempPath.append(temp), shortPath = directPath(temp, end, tree, s);
            }

        for (int i = 0; i < shortPath.size(); i++)
            tempPath.append(shortPath[i]);
        return tempPath;
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

        VecPoints tempPath1, tempPath2, shortPath = directPath(begin, end, tree, s); // искомый путь и прямой путь
        if (!shortPath.isEmpty())
            shortPath.prepend(begin), this->setPath(shortPath);
        else {

            int minX = tree.minX(net, screen, s), minY = tree.minY(net, screen, s), maxX = tree.maxX(net, s), maxY = tree.maxY(net, s); // границы окружности
            int closestSideX = directionX(tree.distToLeft(begin, net, screen, s), tree.distToRight(begin, net, screen, s));
            int closestSideY = directionY(tree.distToTop(begin, net, screen, s), tree.distToBottom(begin, net, screen, s));

            tempPath1 = getToBorder(begin, end, tree, closestSideX, s, minX, minY, maxX, maxY);
            tempPath2 = getToBorder(begin, end, tree, closestSideY, s, minX, minY, maxX, maxY);

            QPoint temp1(tempPath1[tempPath1.size() - 1]), temp2(tempPath2[tempPath2.size() - 1]);
            VecPoints clockWise1 = clockMove(temp1, end, tree, screen, CLOCKWISE, s, minX, minY, maxX, maxY),
                    counterClockWise1 = clockMove(temp1, end, tree, screen, COUNTERCLOCKWISE, s, minX, minY, maxX, maxY),
                    clockWise2 = clockMove(temp2, end, tree, screen, CLOCKWISE, s, minX, minY, maxX, maxY),
                    counterClockWise2 = clockMove(temp2, end, tree, screen, COUNTERCLOCKWISE, s, minX, minY, maxX, maxY);

            if ((counterClockWise1.isEmpty())||(clockWise1.size() < counterClockWise1.size()))
                for (int i = 0; i < clockWise1.size(); i++)
                    tempPath1.append(clockWise1[i]);
            else if ((clockWise1.isEmpty())||(counterClockWise1.size() <= clockWise1.size()))
                for (int i = 0; i < counterClockWise1.size(); i++)
                    tempPath1.append(counterClockWise1[i]);

            if ((counterClockWise2.isEmpty())||(clockWise2.size() < counterClockWise2.size()))
                for (int i = 0; i < clockWise2.size(); i++)
                    tempPath2.append(clockWise2[i]);
            else if ((clockWise2.isEmpty())||(counterClockWise2.size() <= clockWise2.size()))
                for (int i = 0; i < counterClockWise2.size(); i++)
                    tempPath2.append(counterClockWise2[i]);

            if ((tempPath1[tempPath1.size() - 1] == end)&&(tempPath2[tempPath2.size() - 1] == end))
                this->setPath((tempPath1.size() < tempPath2.size()) ? tempPath1 : tempPath2);
            else if ((tempPath1[tempPath1.size() - 1] == end)&&(tempPath2[tempPath2.size() - 1] != end))
                this->setPath(tempPath1);
            else if ((tempPath1[tempPath1.size() - 1] != end)&&(tempPath2[tempPath2.size() - 1] == end))
                this->setPath(tempPath2);
        }
    }
};

#endif // PATH_H
