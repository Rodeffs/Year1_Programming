// Вариант 8
// Написать программу, которая, используя минимальное количество оперативное памяти, найдет объем куба по известной стороне A (целое, 0<A<40).

#include <iostream>
using std::cout;
using std::cin;

int main()
{
    cout << "Enter The Length Of The Side Of The Cube: ";
    short A;
    cin >> A;
    cout << "Cube Volume: " << pow(A, 2) << std::endl;
}

