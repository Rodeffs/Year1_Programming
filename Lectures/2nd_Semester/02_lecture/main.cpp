#include <iostream>
#include <vector>
#include <cstring>

using std::cout;
using std::endl;

#if 0
// void print (std::vector<int> v) - если передавать без ссылки, то расходуется лишняя оперативная память, плюс тратиться время
void print (std::vector<int>& v) {
    system("pause"); // останавливаемся внутри функии
}
#endif

struct String { // у класса 3 конструктора
private:
    size_t m_size;
    char* m_str = nullptr;
//    int& p; - ссылка обязана быть инициализирована в конструкторе
//    const int n; - аналогично, константы должны быть инициализированы

    // Список инициализации идёт в том порядке, в котором здесь идут поля класса

//    String(int c, size_t size) {} - сначала компилятор выбирает конструктор для использования, а уже затем проверяет, приватный он или публичный, перегрузка метода

public:
    String() = default; // конструктор по умолчанию

    String(int c, size_t size) = delete; // таким образом запрещаем конструктор

//    String(int& p) : p(p) {
//        m_size = 0;
//    }

    String(char c, size_t size) : m_size(size), m_str(new char[size+1]){ // конструктор (неявное преобразование из int в char
        cout << "First constructor" << endl;
        std::fill(m_str, m_str + m_size, c); // заполнение массива, можно сделать через memset
        m_str[m_size] = 0;
    }

    String(char* str) : m_size(strlen(str)), m_str(new char[m_size+1]){ // member initializer list (список инициализации членов класса)
        cout << "Second constructor" << endl;
        std::copy(str, str + m_size, m_str);
    }

    String(const String& other) : String(other.m_str) { // конструктор копирования и делегирующий конструктор
        cout << "Copy constructor" << endl;
        m_size = other.m_size; // так можно писать внутри класса

        m_str = new char[m_size]; // выделение памяти

        std::copy(other.m_str, other.m_str + other.m_size, m_str);
    }

    String& operator = (String& temp) {
//        delete[] m_str;
//        m_size = other.m_size;
//        m_str = new char [m_size];
//        std::copy (other.m_str, other.m_str + other.m_size, m_str);

        // Идиома copy-and-swap
        cout << "Copy assignment operator" << endl;
        std::swap(m_size, temp.m_size);
        std::swap(m_str, temp.m_str);
        return *this; // this - указатель на класс, *this - сам класс
    }

    ~String() { // деструктор также может быть дефолтным, но здесь его не стоит использовать
        cout << "Destructor" << endl;
        if(m_str != nullptr)
            delete[] m_str;
    }

    size_t Size() const {
        return m_size;
    }

    void Print() const {
        for (int i = 0; i < m_size; i++)
            cout << m_str[i];
        cout << endl;
    }
};

void f(String s) {
    s.Print();
}

int main() {
//    std::vector<int> vec (100'000'000); - занимает ~800 Мб
//    print(vec);

    String s1("Hello, World!");
//    String s2 = s1;

//    f(s1);
    String s2("test");
    String s3("1111");

    s2 = s1 = s3; // здесь уже работает оператор присваивания, а не копирования
    s1.Print();
    s2.Print();
    s3.Print();

    // Правило трёх: Если нужен нетривиальный деструктор / конструктор присваивания / конструктор копирования, то реализовать нужно их всех

    return 0;
}
