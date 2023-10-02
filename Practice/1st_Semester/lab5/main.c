#include <stdio.h> /* Лабораторная работа №5. */
#include <string.h>
int rect(int n) { // Решение задачи 1
    int r = 0, i = 0; // Изначальное кол-во прямоугольников, плюс каждый раз прибавляемое количество увеличивается на 1
    for (int j = n; j >= 4; j -= 2) // Если 4 точки - то мы можем сделать 1 прямоуг., если 6 - то 3, если 8 - то 6 (к одному прибавляем 2 получаем 3, затем к 3 прибавляем 3 получаем 6, затем к 6 прибавляем 4 получаем 10 и т.д.)
        r += ++i;
    return r;
}
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int thimbles(char *s) { // Решение задачи 2 (thimble - напёрсток)
    int mas[3] = {1}; // Массив из напёрстков, по условию шарик изначально в самом первом
    for (int i = 0; i < strlen(s); i++) // Меняем положение шарика в зависимости от буквы
        (s[i] == 'A') ? swap(&mas[0], &mas[1]) : (s[i] == 'B') ? swap(&mas[2], &mas[1]) : swap(&mas[0], &mas[2]);
    return mas[0] ? 1 : mas[1] ? 2 : 3;
}
int main() {
    int N = 5; // Кол-во вершин 4-угольников для задания 1
    char s[] = "CBABCACCC"; // Строка для задания 2
    printf("The amount of rectangles is: %d\nBall is under thimble number: %d", rect(N), thimbles(s));
    return 0;
}
