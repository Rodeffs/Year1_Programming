#include <stdio.h> /*Простейший калькулятор для нахождения x в равенствах, где 0<=Z<=9. */
int operation (int v1, int v2, char op, int inv) { // данная функция выполняет операции, где v1 - первое число, v2 - второе число, op - выполняемая операция
    switch (op) { // выполнение указанной операции
        case '+':
            return !inv ? v1 + v2 : v1 - v2; // inv - проверка на то, обратная ли это операция или нет (например для x-2=3 будет обратная для '-', т.е. '+' и получится x=3+2)
        case '-':
            return !inv ? v1 - v2 : v1 + v2;
        case '*':
            return !inv ? v1 * v2 : v1 / v2;
        case '/':
            return !inv ? v1 / v2 : v1 * v2;
        case '%': // не рассматриваем обратное, т.к. в таком случае x нельзя определить точно
            return v1 % v2;
    }
}
int calc(char *s) { // данная функция возвращает значение x в равенствах
    int x_i = s[0] == 'x' ? 0 : s[2] == 'x' ? 2 : 4; // ищем позицию x через тернарный алгоритм для краткости
    if (s[1] == '=') { // то есть выражение выглядит так: a = b <операция> c
        if (x_i == 0) // если a - это x, то:
            return operation(s[2] - '0', s[4] - '0', s[3], 0);
        if (x_i == 2) // если b - это x, то:
            return operation(s[0] - '0', s[4] - '0', s[3], 1);
        if ((s[3] == '-') || (s[3] == '/')) // если c - это x, и при этом <операция> - это вычитание или деление, то:
            return operation(s[2] - '0', s[0] - '0', s[3], 0);
        return operation(s[0] - '0', s[2] - '0', s[3], 1); // если c - это x, и при этом <операция> - это не вычитание или деление
    }  // в иных случаях будет так: a <операция> b = c
    if (x_i == 4) // если c - это x, то:
        return operation(s[0] - '0', s[2] - '0', s[1], 0);
    if (x_i == 0) // если a - это x, то:
        return operation(s[4] - '0', s[2] - '0', s[1], 1);
    if ((s[1] == '-') || (s[1] == '/')) // если b - это x, и при этом <операция> - это вычитание или деление, то:
        return operation(s[0] - '0', s[4] - '0', s[1], 0);
    return operation(s[4] - '0', s[0] - '0', s[1], 1); // если b - это x, и при этом <операция> - это не вычитание или деление
}
int main() {
    char *exp[] = {"2+x=5", "x+2=5", "2+x=5", "x-5=2", "5-x=2", "x=5*2", "x*2=6", "9*9=x", "x=7/3", "x/2=5", "x=9%6", "3*x=9"};
    for (int i = 0; i < (sizeof(exp) / sizeof(char *)); i++) printf("%s x=%d\n", exp[i], calc(exp[i]));
    return 0;
}