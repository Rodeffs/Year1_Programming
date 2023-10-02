#include <iostream>
#include <memory> // здесь хранятся умные указатели
using std::cout;
using std::endl;

/* Умные указатели:
1) unique_ptr - уникальный указатель, который не даёт другому объекту присвоить этот указатель, т.е. его нельзя копировать (один объект - один указатель)
2) shared_ptr - указатель, который позволяет копировать
3) weak_ptr
 */

/* Ключевое слово auto автоматически подбирает тип нашей переменной в зависимости от присваиваемых данных */

template<typename T>
struct smartPointer {
private:
    T *p;
    int *count;

public:
    smartPointer(int n) : p(new T), count(new int(1)) {
        p = new int[n];
        cout << "constructed" << endl;
    }

    smartPointer(const smartPointer&) = delete;
    smartPointer& operator=(const smartPointer&) = delete; // таким образом не даём присваивать указатель какому-либо другому объекту, кроме того, на который он уже указывает

    ~smartPointer() {
        if (*count == 1) {
            delete[] p;
            cout << "deleted" << endl;
        }
    }
};

struct Student;

struct Teacher {
    std::weak_ptr<Student> m_student;

    Teacher(std::shared_ptr<Student> student) {
        m_student = student;
    }

    ~Teacher() {
        m_student.lock();
        cout << "teacher deleted" << endl;
    }
};

struct Student {
    std::string name = "Pasha";
    std::shared_ptr<Teacher> m_teacher;

    Student() {}

    void setup(std::shared_ptr<Teacher> teacher) {
        m_teacher = teacher;
    }

    ~Student() {
        cout << "student deleted" << endl;
    }
};

//int g(int x) {
//    if (x == 0)
//        throw 1;
//    return 2;
//}
//
//void f(std::unique_ptr<int> p, int x) {
//
////    std::unique_ptr<int> p = std::make_unique<int>(5);
////    auto p = std::make_unique<int>(5);
////    return p;
//}

int main() {

    auto student = std::make_shared<Student>();
    auto teacher = std::make_shared<Teacher>(student);
    student->setup(teacher);

    cout << teacher.use_count() << " " << student.use_count() << endl;

    try {
//        f(std::unique_ptr<int>(new int(5)), g(1));
//        Порядок выполнения этой операции:
//        1) new int(5)
//        2) g(1)
//        3) std::unique_ptr

//        f(std::make_unique<int>(5), g(1)); // лучше писать так
//        Порядок выполнения этой операции:
//        1) std::make_unique
//        2) g(1)

        auto p = std::make_shared<int>(5);
        cout << p.use_count() << endl;
        auto pp = p;
        cout << p.use_count() << endl;
    }
    catch (std::exception& e) {
        cout << "Ex " << e.what() << endl;
    }
    return 0;
}
