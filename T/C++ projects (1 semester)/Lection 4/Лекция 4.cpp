// Лекция 4

#include <iostream>
#include <sstream>
#include <string> // здесь всё для работы со строками, включая getline
#include <fstream> // здесь находятся всё для работы с файлами


using std::cout;
using std::cin;
using std::endl;


int main()
{
                                /* Символы */ 
    char c;
    cin >> c;
    cout << (int)c; // преобразовать символ c в int

    scanf_s("%hhd", &c); // первое - это спецификатор (после %), второе - адрес (& - значит переменная меняется внутри функции)

    printf("%d", c); // работает быстрее std::cout, однако это устаревший способ (%d - значит переход к след. значения, как в Си)


    // (int)c - так называемый c-style, но данные таким образом могут потеряться
    /*
    int a = 1000;
    char b = (char)a; - потеряются значения, т.к. char до 127 байт
    */


    cout << static_cast<int>(c); // так лучше преобразовать переменные


    char a = '0';
    if ('a' < 'b') { // сравнение значений идёт по таблице ASCII, в данном случае 48<49
        cout << "a < b" << endl;
    }

    char b = 11; // символ 11 из таблицы ASCII


                                  /* Строки */

    char str[14] = "Hello, world!"; // массив из 14 строчных символов, их ВСЕГДА должно быть больше на один, чем кол-во символолв, т.к. в конце стоит терминирующий символ (он прекращает вывод)
    // str[13] = 'T' - таким образом мы удалим терминирующий символ (\0), что приведёт к неверному выводу
    // str[4] = '\0' - теперь 4 символ - это терминирующий символ


    cout << strlen(str) << endl; // strlen() - возвращает длину строки


    // Конкатенация - объединение строк:
    char d[100] = "Hello, ";
    char e[100] = "world!";
    strcat_s(d, e); // strcat_s(d, e) объединяет строки, первое - это начало, второе - конец
    // strcat(d, e); - но это не совсем безопасно
    cout << a << endl;


    // Копирование строк:

    strcpy_s(d, e); // strcpy_s() копирует строки


    for (int i = 0; i < strlen(d) + 5; i++) {
        cout << static_cast<int>(d[i]) << " "; // выведет значения int для списка d
    }


    char s1[5] = "abc";
    char s2[5] = "abb";
    cout << strcmp(s1, s2) << endl; // strcmp() сравнивает строки, если s1 > s2 (сравнивает коды символов последовательно), то выведется 1, иначе -1


    // Считывание строк:

    char str2[100];
    // cin >> str; - будет считывать до пробела
    // getline() - работает только с типом данных string, не char
    gets_s(str2, 100); // считыание до символа \n (перехода на сле. строку)
    cout << str2 << endl;


                                    /* Файловые ввод и вывод */

    char str3[100]; // '\n'
    std::ifstream in("input.txt", std::ios::in); // чтение файла из репозитория, пишется имя файла и спецификатор

    std::ofstream out("output.txt", std::ios::out);

    while (!in.eof()) {
        in.getline(str, 100);
        out << str3 << "\n";
    }


    // Дана строка из строчных букв, преобразовать в прописные

    char str4[100] = "abc";
    for (int i = 0; i < strlen(str4); i++) {
        str4[i] -= 32; // т.к. прописные имеют значение меньше на 32, чем строчные
    }
    cout << str4;


    // Посчитать кол-во гласных в слове

    char alphabet[100] = "abcdefghij";
    char vowels[7] = "aeioyu";
    int count = 0;
    for (int i = 0; i < strlen(alphabet); i++) {
        for (int j = 0; j < strlen(vowels); j++) {
            if (str[i] == vowels[j]) {
                count++;
                break;
            }
        }
    }


    std::string s = "Hello, world!";
    std::string s3 = "H";
    std::string s4 = "e";
    cout << s3 + s4 << endl; // плюс - это перегрузка
    s3 = s4;
    cout << s3;


    std::string alpha = "abcdefghuj";
    std::string vowels2 = "aeioyu";
    int cnt = 0;
    for (int i = 0; i < alpha.length(); i++) {
        if (vowels2.find(alpha[i]) != std::string::npos) // find работает со строками, возвращает позицию символа alpha[i] в строке vowels2
                                                         // std::string::npos - это значение, которое возвращается в случае, если поиск не удался
            cnt++;
    }
    cout << cnt;

}


