#include <iostream>
#include <vector>
using std::endl;
using std::cout;

// См. в основном репозитории

//class base {
//public:
//    int a = 1;
//    void f() {
//        cout << "base" << endl;
//    }
//};
//
//class derived : public base {
//public:
//    int a = 2;
//    void f() {
//        cout << "derived" << endl;
//    }
//};

struct granny {
    virtual void f() {
        cout << "granny" << endl;
    }
};

int main() {

//    derived* d = new derived();
//    d->f();
//
//    // конвертация из родителя в наследника
//    base* b = static_cast<base*>(d);
//    b->f();
//
//    derived* dd = static_cast<derived*>(b);
//    dd->f();

    return 0;
}
