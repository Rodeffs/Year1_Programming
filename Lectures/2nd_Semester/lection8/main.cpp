#include <iostream>
#import <vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;

struct shape {
    int a = 10;
};

struct circle : shape {

};

struct triangle : shape {

};


enum class shapeType {CIRCLE, TRIANGLE, RECTANGLE};

shape* factory(shapeType type) { // фабрика, скрываем за этой функцией детали конструирования объекта
    shape* shape = nullptr;
    switch (type) {
        case shapeType::CIRCLE:
            shape = new circle();
            break;
        case shapeType::TRIANGLE:
            shape = new triangle();
            break;
        default:
            shape = nullptr;
    }
    return shape;
}

struct A {
    char* m_str;
    A() {
//        m_str = new char[100];
//        int x, y;
//        cin >> x >> y;
//        if (y==0)
//            throw std::logic_error("error");
//        cout << "constructed A" << endl;
    }
    string getName() noexcept {

    }
    A(const A&) {
        cout << "copied A" << endl;
    }
    ~A() noexcept(false){
        throw std::logic_error("error");
//        delete[] m_str;
//        cout << "destroyed A" << endl;
//        int x, y;
//        cin >> x >> y;
//        if (y == 0)
//            throw std::logic_error("error");
    }
};

struct B : A {
    B() {
        cout << "constructed B" << endl;
    }
    B(const B&) {
        cout << "copied B" << endl;
    }
};

struct smartPointer { // умный указатель, суть в том, что объект создаётся на стеке, но внутри он динамический, таим образом гарантированно не будет утечки памяти
private:
    int* p;
public:
    smartPointer(int n) {
        p = new int[n];
        cout << "constructed";
    }
    ~smartPointer() {
        delete[] p;
        cout << "destroyed";
    }
};

//int f(int& error) {
int f() {
    int x, y;
    cin >> x >> y;

//    if (y == 0) { // обработка ошибки вариант 1
//        error = -1;
//        return 0;
//    }
//    error = 0;

    if (y == 0) // обработка ошибки вариант 2
        throw "division by 0"; // здесь тип данных char*

    throw string("111");

    return x / y;
}

int main() {

    vector<shape*> shapes;

    shape* shape = factory(shapeType::RECTANGLE);
    if (shape == nullptr)
        return 0;

    // обработка ошибок вариант 2
    try {
        vector<int> v;
//        v[0]; // такая индексация не сработает для вектора
        v.at(0); // намеренно сделаем ошибку и попытаемся её поймать

        A a;
    }
    catch (std::out_of_range& e) {
        cout << "out " << e.what() << endl;
    }
    catch (std::exception& e) {
        cout << e.what() << endl; // выведем тип ошибки
    }
    catch (int e) { // обрабатывать все типы аргументов throw
        cout << "int " << e << endl;
    }
    catch (char* e) {
        cout << "char* " << e << endl;
    }
    catch (string e) {
        cout << "string " << e << endl;
    }
    catch (A& e) {
        cout << "A catch" << endl;
    }
    catch (B& e) {
        cout << "B catch" << endl;
    }


    shapes.push_back(factory(shapeType::RECTANGLE));
    cout << shapes[0]->a;

    return 0;
}
