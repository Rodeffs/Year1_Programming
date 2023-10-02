#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int sizes(char *s) { // для вычисление длины строки

    int l;

    for (l = 0; s[l]!= 0; l++);

    return l;
}


int power(int a, int b) { // для вычисления степени a - число, b - степень

    int r = 1;

    for (int i = 0; i < b; i++)
        r = r * a;

    return r;
}


int stoi(char *s) {  // stoi - string to integer

    int m = 0;

    int l = sizes(s); // длина строки

    for (int i = 0; i < l; i++) {

        if ((s[i] >= '0') && (s[i] <= '9')) {

            int p10 = power(10, (l - 1 - i)); // степень десятки

            int c = s[i] - '0'; // перевод в int

            m += c * p10;

            if ((m >= INT_MAX) || (m < 0))
                return INT_MAX;
        }
    }
    return m;
}

int stoi2(char *s, int i1, int j1) {

    int n = 0;

    for (int i = i1; i < j1; i++) {

        int c = s[i] - '0'; // перевод в int

        n = n * 10 + c; // т.е. предыдущее значение n умножаем на 10 и прибавляем нынешний символ

        if ((n >= INT_MAX) || (n < 0))
            return INT_MAX;
    }
    return n;
}


int calc(char *s) { // калькулятор для чисел от 0 до 9

    int i; // мы запоминаем i, т.к. i - это индекс последней цифры первого числа, а следующий символ - знак операции
    int j;


    for (i = 0; s[i] != 0; i++)
        if (!((s[i] >= '0')&&(s[i] <= '9')))
            break;

    int x = stoi2(s, 0, i);


    for (j = i + 1; s[j] != 0; j++)
        if (!((s[j] >= '0')&&(s[j] <= '9')))
            break;

    int y = stoi2(s, i + 1, j);


    switch (s[i]) {
    case '+':
        return (x + y);
    case '-':
        return (x - y);
    case '/':
        return (x / y);
    case '*':
        return (x * y);
    case '%':
        return (x % y);
    case '^':
        return power(x, y);
    }
}

int main(int argc, char *argv[])
{
    char c = '9';
    int n;

    if (c >= '0' && c <= '9')
        n = c - '0'; // перевод char в int для символов, представляющих из себя цифру (от 0 до 9)


    printf("%d\n", stoi("545"));


    printf("%d\n", calc("9999999-6="));

    // Ещё можно сделать калькулятор с отрицательными членами, с количеством членов больше двух и с приоритетом операции, включая скобки


}
