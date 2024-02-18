#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::swap;

class complex { // класс комплексных чисел
private:
    double m_a;
    double m_b;
    int m_mas[10] = {1, 2, 3, 4};

public:
    complex(double a) : m_a(a), m_b(a){
        cout << "Default constructor #1" << endl;
    }

//    explicit complex(double a = 0.0, double b = 0.0) : m_a(a), m_b(b) { // запись = 0.0 значит, что это значения по умолчанию, а то, что после : - это список инициализации, т.е. мы сразу присваиваем значения
//        cout << "Default constructor #2" << endl;
//    }

    /* explicit ЗАПРЕЩАЕТ неявную конвертацию, то есть не получится к нашему комплексному числу прибавить, например, строку */

    complex(const complex& z) { // дефолтный конструктор копирования
        cout << "Copy constructor" << endl;
        m_a = z.m_a;
        m_b = z.m_b;
    }

    complex& operator=(complex z) { // оператор присваивания (не создаёт новый объект, ПОЭТОМУ нужна ссылка)
        cout << "Assignment operator" << endl;
        swap(m_a, z.m_a);
        swap(m_b, z.m_b);
        return *this; // т.к. объект передаётся по ссылке, то возвращаем разыменованный объект
    }

    complex& operator+=(const complex& z) { // оператор += (не создаёт новый объект, ПОЭТОМУ нужна ссылка)
        (*this).m_a += z.m_a; // просто прибавляем к данному комплексному числу значения a и b другого числа
        (*this).m_b += z.m_b;
        return *this;
    }

//    complex operator+(const complex& z) { // оператор сложения, ссылка не нужна, т.к. он СОЗДАЁТ новый объект (this в данном случае - это число z1, а const complex& z - это z2)
//        complex temp = *this;
////        temp.m_a += z.m_a;
////        temp.m_b += z.m_b;
//        temp += z; // т.к. мы реализовали оператор += выше, данная запись имеет смысл
//        return temp;
//    }

    int& operator[](int index) { // оператор [] - возвращает ссылку на элемент массива, поддерживает чтение и запись
        return m_mas[index]; // проверка выхода за границы массива изначально не определена
    }

    int& at(int index) { // не до конца правильно, требуется решить с помощью исключений
        if (0 <= index && index < 10)
            return m_mas[index];
    }

    complex& operator++() { // префиксный инкремент (т.е. ++z) - более эффективный, однако это не слишком значимо
        this->m_a += 1;
        return *this;
    }

    complex& operator++(int) { // постфиксный инкремент (т.е. z++)
        complex temp = *this;
        this->m_a += 1;
        return temp;
    }

    friend std::ostream& operator<<(std::ostream& out, const complex& z); // функция-друг, позволяет пользоваться ей вне класса, однако это нарушает инкапсуляцию
    friend std::istream& operator>>(std::istream& in, complex& z);
};

complex operator+(const complex& z1, const complex& z2) { // оператор сложения и для случаев, когда мы несколько типов складываем выносим за класс
    /* rvo - return value optimization */
    complex temp = z1;
    temp += z2;
    return temp;
}

std::ostream& operator<<(std::ostream& out, const complex& z) { // перегрузка оператора вывода в поток, ссылка позволяет обработать сразу несколько значений (т.к. мы можем писать cout << a << b << endl)
    out << z.m_a << " " << z.m_b << "i";
    return out;
}

std::istream& operator>>(std::istream& in, complex& z)  {
    in >> z.m_a  >> z.m_b;
    return in;
}

int main() {
    complex z1(1), z2(2.0);
//    complex z = z1 + z2; - изначально компилятор не умеет это обрабатывать, поэтому нужна перегрузка операторов
//    complex z3 = 1.0 + z1;
    complex z3 = z1 + z2; // copy elision, т.е. пропуск копирования

//    cout << z1[0] << endl;
//    z1.at(0) = 10;
//    cout << z1[0] << endl;

    complex z(0);
    cout << z << " " << z1 << endl;
//    z = ++z1; // сначала увеличивается на 1, потом увеличивается на 1
    z = z1++; // сначала даёт своё значение, потом увеличивается на 1
    cout << z << " " << z1 << endl;

    return 0;
}
