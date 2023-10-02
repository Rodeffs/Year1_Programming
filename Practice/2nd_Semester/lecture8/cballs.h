#ifndef CBALLS_H
#define CBALLS_H
#include "balls.h"

// cballs - color balls

class CBalls : public Balls // при наследовании обязательно нужно писать public (есть ещё другие типы наследования, protected и private, но пустым это место НЕЛЬЗЯ оставлять)
{
public:
    CBalls(); // единственная вещь, которая НЕ наследуется - это конструкторы

    CBalls(int x, int y, int r, int dx = -10, int dy = -10);

    virtual void draw(QPainter *painter); // виртуальная функция выполнит метод того класса, через который мы создали объект (т.е. у нас bim в mainwindow.h через Balls, а в mainwindow.cpp через CBalls. Т.е. виртуальная функция идёт по всем своим "предкам" и выполняет первую функцию, которая ей встретится, даже если в самом первом "материнском" классе она другая
};

#endif // CBALLS_H
