#include "cballs.h"
#include <QPainter>

CBalls::CBalls() {}

CBalls::CBalls(int x, int y, int r, int dx, int dy) : Balls(x, y, r, dx, dy){} // в списочной инициализации можно также вызывать конструктор суперкласса (т.е. наследуемого класса), даже если доступа к приватным полям нет

void CBalls::draw(QPainter *painter)
{
    painter->setBrush(QBrush(Qt::red));
//    painter->drawEllipse(QPoint(m_x, m_y), m_r, m_r);

    Balls::draw(painter); // просто вызовем draw() у родителя, нет смысла его снова здесь писать
}
