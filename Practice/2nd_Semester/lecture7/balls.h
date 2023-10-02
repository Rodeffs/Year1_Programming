#ifndef BALLS_H
#define BALLS_H

class QPainter; // форвардная декларация, тем самым нам не нужно здесь писать include

class Balls
{
private:
    int m_x = 100, m_y = 100, m_r = 40;
    int m_dx = -10, m_dy = -10; // вектора скорости

public: // сами методы прописаны в balls.cpp (здесь работает то же правило, что и с функциями - обозначить из внутри класса, а тело прописать после)
    Balls();

    void draw(QPainter *painter); // так лучше не делать, т.к. мы связываем один класс с другим, что в дальнейшем может привести к "спагетти"

    void move(int width, int height);

    int x() const; // const - значит метод константный, т.е. он ничего не поменяет в полях класса

    int y() const;

    int r() const;

    int dx() const;

    int dy() const;

    void setX(int x);

    void setY(int y);

    void setR(int r);

    void setDX(int dx);

    void setDY(int dy);
};

#endif // BALLS_H
