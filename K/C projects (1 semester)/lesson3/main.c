#include <stdio.h>


// Сколько молекул c2h5oh можно сделать из данных c, h и o
int min(int c, int h , int o) {
    if (c/2 < h/6)
    return c/2 < o ? c/2 : o;
    else
    return h/6 < o ? h/6 : o;
}


// Проверка на простое число
int isPrime(int num) {
    if (num == 1)
        return 0;
    if (num == 2)
        return 1;
    for (int i = 2; i < (num/2 + 1); i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}


// НОД
int nod_find(int a, int b) {

    if (a == b)
        return a;

    int min_num = a < b ? a : b;

    int max_num = (a + b) - min_num;

    int nod = 1;

    for (int i = 1; i < (min_num + 1); i++) {
        if (min_num % i == 0)
            if (max_num % i == 0)
                nod = i > nod ? i : nod;
    }
    return nod;
}


// Счастливый билет
int lucky(int n) {
    return (n%10 + (n/10)%10 + (n/100)%10) == ((n/1000)%10 + (n/10000)%10 + (n/100000)%10) ? 1 : 0;
}


// Алиса
int change(int a) {
    int count3 = 0;
    int count5 = 0;
    int i = a;
    while (i >= 0) {
        if (i % 5 == 0) {
            count5 = i / 5;
            printf("\nAmount of 5: %d", count5);
            printf("\nAmount of 3: %d", count3);
            return count3 + count5;
        }
        i -= 3;
        count3 += 1;
    }
    if (i < 3)
        return 0;
    printf("\nAmount of 5: %d", count5);
    printf("\nAmount of 3: %d", count3);
    return count3 + count5;
}


// Прямоугольники на плоскости
int rect(int n) {
    if ((n % 2 != 0) || (n < 4))
        return 0;
    int r = 0; // Изначальное кол-во прямоугольников
    int i = 1;
    int j = n;
    while (j >= 4) { // Если 4 точки - то мы можем сделать 1 прямоуг., если 6 - то 3, если 8 - то 6 (к одному прибавляем 2 получаем 3, затем к 3 прибавляем 3 получаем 6, затем к 6 прибавляем 4 получаем 10 и т.д.)
           r += i;
           j -= 2;
           i++;
    }
    return r;
}


int main(int argc, char *argv[])
{

// Прямоугольники на плоскости
int n = 22;
printf("The amount of rectangles is: %d\n", rect(n));


// Счастливый билет
int number = 532603;
if (lucky(number))
     printf("%d is lucky!\n", number);
else
    printf("%d is unlucky\n", number);


// НОД:
printf("NOD is %d\n", nod_find(360, 90));

// Алиса
int money = 1;
if (change(money))
    printf("Amount of coins: %d\n", change(money));
else
    printf("Error\n");


// Сколько молекул c2h5oh можно сделать из данных c, h и o:
int C = 4;
int H = 19;
int O = 3;
printf("The amount of alcohol molecules is: %d\n", min(C, H, O));


// Проверка на простое число
for (int j = 1; j < 101; j++)
    if (isPrime(j) == 1)
        printf("%d is prime\n", j);


// Шахматная доска
int board[8][8] = {0};
for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        if ((i + j) % 2 == 0)
            board[i][j] = 1;
    }
}
for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++)
        printf("%d ", board[i][j]);
printf("\n");
}
}
