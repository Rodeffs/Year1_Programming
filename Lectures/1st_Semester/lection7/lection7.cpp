#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void swap1(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void swap2(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main()
{
	/* Работа с указателями */

	int* p; // указатель - это переменная, которая хранит адрес
	int x = 10;
	p = &x; // в переменной p хранится адрес x, & возвращает адрес переменной
	cout << p << endl; // выведет адрес p
	cout << *p << endl; // выведет значение, на которое указывает p (разыменование)

	int A = 52, B = 9;
	swap2(&A, &B);


	int mas[10] = { 1, 2, 3, 4 };
	cout << mas << endl; // выведет указатель на 1 элемент
	cout << mas + 1 << endl; // выведет указатель на 2 элемент
	cout << *(mas) << endl; // выведет значение 1 элемента
	cout << *(mas + 1) << endl; // выведет значение 2 элемента
	cout << mas[1] << endl; // тоже выведет значение 2 элемента

	unsigned char mass[4] = { 232, 3, 0, 0 };
	int x = *((int*)mass); // таким образом значение char выше выведется в int (получится 1000)
	int y = mass[0] + mass[1] * 256; // аналогично, что и выше

}

