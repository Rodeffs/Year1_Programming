// Вариант 8.
/* 1.	Ввести натуральные числа A, B и C.Если A кратно C и B кратно C, то вывести(A + B) / C, если A кратно C и B не кратно C, то вывести A / С + B, в остальных случаях вывести A - B - C.
   2.	Ввести цифру N, при помощи оператора switch вывести название цифры.Предусмотреть обработку ошибочного ввода N. */


#include <iostream>
using std::cin;
using std::cout;

int main()
{
	// Задание 1:
	int A, B, C;
	cout << "Enter integers A, B, C (with spaces between them): "; cin >> A >> B >> C;
	if ((A % C == 0) && (B % C == 0)) {
		cout << (A + B) / C;
	}
	else if ((A % C == 0) && (B % C != 0)) {
		cout << A / C + B;
	}
	else {
		cout << A - B - C;
	}


	// Задание 2:
	short N; cout << "\n" << "Enter N (must be a numeral): "; cin >> N;
	switch (N) {
	case 0:
		cout << "Zero";
		break;
	case 1:
		cout << "One";
		break;
	case 2:
		cout << "Two";
		break;
	case 3:
		cout << "Three";
		break;
	case 4:
		cout << "Four";
		break;
	case 5:
		cout << "Five";
		break;
	case 6:
		cout << "Six";
		break;
	case 7:
		cout << "Seven";
		break;
	case 8:
		cout << "Eight";
		break;
	case 9:
		cout << "Nine";
		break;
	default:
		cout << "Error: N is not a numeral";
		break;
	}
}

