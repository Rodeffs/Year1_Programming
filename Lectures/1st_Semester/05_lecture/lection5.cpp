// Лекция 5
#include <iostream>
#include <cmath> // здесь находится матем. функции, включая sqrt()
#include "func.hpp" // Нужно, чтобы разделить функции на несколько файлов
// #include "func.cpp" просто бы скопировало файл сюда

using std::cout;
using std::cin;
using std::endl;


                                          /* Функции */

// Типы функций зависят от возвращаемых значений (т.е. int, bool, void если ничего и т.д.)
bool isPrime (int x) { // Проверка на простоту числа
    if (x < 2)
        return false;
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0)
            return false;
    }
    return true;
}

int sumOfDigits (int x) { // Сумма цифр в числе
    int sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int maxOfDigits (int x) { // Максимальная цифра в числе
    int max = 0;
    while (x > 0) {
        if (max < x % 10)
            max = x % 10;
        x /= 10;
    }
    return max;
}

void print10() { // Это процедура (функция, не возвращающая значений)
    for (int i = 0; i < 10; i++)
        cout << i << endl;
}

void swap (int &a, int &b) { // Передача параметров в функцию по ССЫЛКЕ (знак & перед переменной)
    // !!! Передача по ссылке МЕНЯЕТ исходную переменную
    int tmp = a;
    a = b;
    b = tmp;
}

void swapSort (int* mas, int m) { // Сортировка массивов. Массивы всегда передаются по ссылке
    // * - это указатель. Таким образом нам не нужно писать int mas[10]
    for (int i = 0; i < m - 1; i++)
        for (int j = i + 1; j < m; j++)
            if (mas[i] > mas[j])
                swap(mas[i], mas[j]); // Если бы мы написали using std; в начале, то компилятор мог выдать не ту функцию, т.к. в пространстве имён std есть свой swap()
}


int main() {
    int n;
    cin >> n;
    if (isPrime(n))
        cout << n << " is prime" << endl;
    else
        cout << n << " is not prime" << endl;


    int mas[5] = {1454,42,300,789324,5};
    swapSort(mas, 5);
    for (int i : mas) // То же, что и i in range(len(mas)) в Питоне
        cout << i << " ";
}
