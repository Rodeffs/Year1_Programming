#include <stdio.h>
#include <stdlib.h>

int myfunc(int a); // Если я хочу, чтобы тело функции было внизу, то я должен с самого верха эту функцию обозвать, иначе код не выполнится

void func3(int a[], int b[]) { // void функции могут не вернуть ничего
    a[0] = 0; // Массивы вызываются по ссылке
    b[0] = 0;
}

int fsum(int n) { // Сумма всех чисел до n
    int count = 0;
    for (int i = 0; i <= n; i++) {
        count += i;
    }
    printf("%d", count);
    return 0;
}

int fact1(int n) { // Обычная функция для факториала
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    printf("\n%d", result);
    return 0;
}

int fact2(int n) { // Рекурсивная функция для факториала
    if ((n == 1) || (n == 0))
        return 1;
    if (n < 0)
        return 0;
    return (fact2(n-1)) * n;
}

int fact3(int n) {return n <= 1 ? 1 : (fact3(n-1)*n);} // Функция факториала в одну строку




/* Максимальное количество тёплых дней в месяце */
int temperature(int a[], int s) {
    int count = 1;
    int max_count = 0;
    for (int i=0; i < s-1; i++) {
        if (a[i] > 0 && a[i+1] > 0) {
            count += 1;
            if (count > max_count)
                max_count = count; // Максимальная температура
        }
        else count = 1; // Если след. день холодный, то обнуляем счётчик
    }
    return max_count;
}




int main(int argc, char *argv[])
{

/* Сапёр


#define N 10 // Присваиваем значение N (размер поля)

#define M 30

    int mines[N][N] = {0};

    srand(time(0));

    for (int m = 0; m < M; m++) {
        int i = rand() % N; // Присваиваем значение остатка от деления на N (он будет от 0 до N-1)
        int j = rand() % N;
        if (mines[i][j] != -1)
            mines[i][j] = -1;
        else m--; // Если в этой клетке уже имеется мина, то мы уменьшаем счётчик цикла (тем самым проходим по нему ещё раз), иначе мины будут накладываться друг на друга
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mines[i][j] == -1)
                continue; // Если в клетке мина, то пропускаем

            // Дабы не превысить допустимые значения, там, где индекс уменьшается нужно прописать уловие > 0, а где увеличивается прописать < (N - 1)

            if (i > 0 && j < (N - 1) && mines[i-1][j+1] == -1) // Северо-Запад
                mines[i][j]++; // Если в клетке рядом мина, то увеличиваем значение, делаем так для всех ближник клеток

            if (j < (N - 1) && mines[i][j+1] == -1) // Север
                mines[i][j]++;

            if (i < (N - 1) && j < (N - 1) && mines[i+1][j+1] == -1) // Северо-Восток
                mines[i][j]++;

            if (i > 0 && mines[i-1][j] == -1) // Запад
                mines[i][j]++;

            if (i < (N - 1) && mines[i+1][j] == -1) // Восток
                mines[i][j]++;

            if (i > 0 && j > 0 && mines[i-1][j-1] == -1) // Ю-З
                mines[i][j]++;

            if (j > 0 && mines[i][j-1] == -1) // Юг
                mines[i][j]++;

            if (i < (N - 1) && j > 0 && mines[i+1][j-1] == -1) // Ю-В
                mines[i][j]++;

            // Этот код был написан троими: Юрой, Сашей и Димой. RIP, помянем героев
            }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mines[i][j] == -1)
                printf("*");
            else
                printf("%d",mines[i][j]);
        }
        printf("\n");
    }

*/

/* Функции.
     Лучше всего их писать перед main, т.к. иначе они не выполнятся

    int n = 5, m[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    int len = sizeof(m) / sizeof(int); // Вычисление размера массива (т.к. sizeof возвращает в байтах, мы делим общее кол-во байтов на байт/символ

    int len2 = sizeof(m) / sizeof(m[0]); // Так считать лучше, т.к. в таком случае тип данных всегда правильный

    int a = myfunc(n);

    func3(m, n);

*/

//    fsum(5);

//    fact1(13);

//    printf("\n%d", fact2(5));




    /* ПРОДОЛЖЕНИЕ Максимальное количество тёплых дней в месяце */
    float temp[] = {-5.5, -4, 0, -2, -3.7, -1, 1, 3, -1, 4, 3, 4, -2, 0, 0, 1, 2, 3, 3, -1};

    int s = 0;

    s = (sizeof(temp) / sizeof(temp[0])); // Кол-во дней всего

    printf("%d", temperature(temp, s));

    return 0;
}



int myfunc(int a) { // int функции всегда должны что-то вернуть

    a =-10;
    return 0;
}



void myfunc1(int x, int y, ...) {

}





