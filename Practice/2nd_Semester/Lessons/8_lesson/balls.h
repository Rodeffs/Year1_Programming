#ifndef BALLS_H
#define BALLS_H

class QPainter; // форвардная декларация, тем самым нам не нужно здесь писать include

class Balls
{
protected: // пишем это ключевое слово, чтобы у наследуемых классов был доступ
    int m_x, m_y, m_r, m_dx, m_dy; // параметры шарика

public: // сами методы прописаны в balls.cpp (здесь работает то же правило, что и с функциями - обозначить из внутри класса, а тело прописать после)
    Balls();

    Balls(int x, int y, int r, int dx = -10, int dy = -10); // конструктор, но уже передаём какие-то значения. Если какой-либо параметр не будет указан, то ему будет присвоено дефолтное значение после знака равно

    virtual void draw(QPainter *painter) = 0; // так лучше не делать, т.к. мы связываем один класс с другим, что в дальнейшем может привести к "спагетти"
    // знак = 0 означает, что это чисто виртуальная функция, а класс с ней называется АБСТРАКТНЫМ. Т.е. тела функции в этом классе нет и никогда не будет, все наследники будут ОБЯЗАНЫ реализовать её, либо также объявят её чисто виртуальной
    // так писать можно ТОЛЬКО для виртуальных функций

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