#include <stdio.h>

int checkword (int c) { // Проверка на то, является ли символ знаком

    switch (c) {
    case -1: // Конец строки
        return 1;
    case ' ':  // Пробел кодируется как 32, одиночные кавычки здесь нужны, т.к. пробел - это один символ
        return 1;
    case '.':
        return 1;
    case ',':
        return 1;
    case '!':
        return 1;
    case '?':
        return 1;
    case ':':
        return 1;
    case ';':
        return 1;
    default:
        return 0;
    }
}

int main(int argc, char *argv[])
{
    /* Работа с файлами:
    FILE *f = fopen("file.txt", "r"); - существует ещё fopen_s() - более безопасный вариант

        fopen() нужен для чтения файлов. В первых кавычках название файла, а во вторых:

    r - чтение
    w - запись, исходные данные стираются
    a - запись, добавляется к исходным данным
    b - в двоичной системе (можно сочетать с другими)


    if(f == NULL) { - это проверка на случай, если файл либо пустой, либо его нельзя менять, либо его не существует
    Другой вариант - if(!f)

        printf("Error, file can't be opened\n");
        return 0;
    }

    fclose(f); - После прочтения файл нужно закрыть!
    */

    /* Консоль:

    stdin - ввод данных
    stdout - вывод данных
    stderr - в случае ошибки

    FILE *freopen()
    FILE *fdopen()

    */


    char *file = "D:\\Apps\\Programming\\K\\C projects\\lesson6\\sample.txt";

    FILE *fd = fopen(file, "r");

    if (!fd) {
        printf("Error, file can't be opened\n");
        return 0;
    }

//    // Вывод файла:
//    int cc;
//    while ((cc = fgetc(ИМЯ ФАЙЛА)) != EOF) // EOF - End Of File
//        putchar(cc);

    // Вывод длины файла в байтах:
    fseek(fd, 0, SEEK_END); // Указатель передвигается в начало файла из конца
    long size;
    size = ftell(fd);
    printf("File size is %ld bytes\n", size);


    // Вывод файла задом наперёд:
    for (int i = 0; i <= size; i++) {

        fseek(fd, -i, SEEK_END);
        int c;
        c = fgetc(fd); // Вывод символа
        printf("%c", c);
    }


    printf("\n");


    // Подсчёт количества слов:
    int count = 0;
    int check = 0;

    for (int i = 0; i <= size; i++) {

        fseek(fd, i, SEEK_SET);
        int c;
        c = fgetc(fd);

        if ((check == 0)&&(checkword(c) == 0)) // Если этот символ не является знаком (т.е. хороший), а предыдущий символ был знаком (т.е. плохим)...

            check = 1; // ...то этот символ хороший и теперь он становится предыдущим символом (для проверки)

        else if ((check == 1) && (checkword(c) == 1)) { // Если этот символ плохой, а предыдущий был хорошим...

            check = 0; // ...то этот символ плохой и теперь он становится предыдущим символом

            count++; // И в таком случае счётчик слов + 1
        }
    }

    printf("The number of words is %d\n", count);

    fclose(fd);

    /*

    int getchar(void); - Ввод символов в stdin

    int putchar(int c); - Вывод символов в stdout

    int fgetc(FILE *stream);

    int getc(FILE *stream);

    char *gets(char *s); - Ввод строк (опасная функция, т.к. у неё нет ограеичения и она может переполнить буфер )

    char *fgets(char *s, int n, FILE *stream); - Ввод строк, только безопасная, т.к. у неё есть ограничение

    и так далее...

    Форматы вывода:

    %d - вывод int
    %ld - вывод long
    %lld - вывод long long
    %s - вывод char *
    %c - вывод char
    %o - вывод в 8-чной системе
    %x - вывод в 16-чной ситеме
    %p - вывод указателя

    и прочее...

    %04d - ?

    int scanf(const char *format,...); // Функция, обратная printf(), т.е. ввод данных с клавиатуры

    int fseek(FILE *stream, long offset, int whence);
    fseek() управляет указателем:

    whence указывает на то, откуда пойдёт указатель (флаг) файла
    whence имеет параметры: SEEK_SET (начало), SEEK_CUR (нынешнее положение) и SEEK_END (конец)

    offset указывает, до куда именно передвинется указатель (флаг)

    ftell() - выводит в формате long, куда переместился указатель, т.е. длину файла

    size_t fwrite();
    size_t fread();

    int ferror(FILE *stream); - Если в потоке есть ошибка, выводит 1, если нет, то 0

    */
    return 0;
}
