// Лекция 9. Сложный тип данных
#include <iostream>
#define N 10

int age[N]; // Здесь мы каждый тип данных записываем по отдельности, но это не лучший способ, для этого есть структуры
std::string name[N];
std::string surname[N];


/*                              Структура. Основное назначение - хранение данных             */

struct Person { // Структура для сложного типа данных
    int age;
    std::string name;
    std::string surname;
};


Person addPerson() {
    Person person;
    person.age = 18;

    return person;
}


/*                                Класс. Основное назначение - хранение данных и операции над ними            */

class Car {
private: // Из этой секции вызывать объекты в коде нельзя

    // 1 принцип ООП - Абстракция, т.е. от реального объекта берём минимальный набор параметров, необходимых для решения задачи:
    double m_acceleration = 0; // ускорение машины
    std::string m_model = ""; // модель машины
    double m_maxVelocity = 0; // макс. скорость машины
    double m_x = 0; // положение машины
    double m_radiusOfWheel = 0; // радиус колеса
    Person* m_persons = nullptr; // это массив для пассажиров в машине (nullptr нужен, чтобы мы могли очистить данные, т.к. это пустой указатель)


    // 2 принцип ООП - Инкапсуляция, т.е. разграничение доступа к полям и методам класса:

public: // Мы можем вызывать объекты лишь из этой секции  
    Car () {} // Конструктор по умолчанию

    // Это конструктор (функция без типа и с именем, совпадающим с именем класса; она создаётся всегда самим компилятором):
    Car(double acceleration, std::string model, double maxVelocity) {
    
        // Мы ставили m_ дабы отличить private от public
        m_acceleration = acceleration;
        m_model = model;
        m_maxVelocity = maxVelocity;
        m_x = 0;
    }

    // Это деструктор (очищает данные после выполнения программы, выполняется в самом конце, после всего остального):
    ~Car() {
        if (m_persons != nullptr)
            delete[] m_persons;
    };

    void Move(double dx) { // Движение машины
        m_x += dx;
    }

    // Это геттер:
    double Position() {
        return m_x;
    }

    // Это сеттер:
    bool SetRadiusOfWheel() {
        if (m_radiusOfWheel < 0) {
            std::cout << "Error, radius can't be negative" << std::endl;
            return false;
        }
        return true;
    }

    int Circumference() { // Длина окружности
        return 2 * acos(-1) * m_radiusOfWheel;
    }

    void SetPersonsQuantity(int n) { // Количество пассажиров
        m_persons = new Person[n];
    }

private: // Мы можем писать private и public несколько раз для каждого типа переменных
    int m_y = 0;
};

/* ООП :

1. Структурирование кода
2. Упрощается написание кода

*/


int main()
{
    // Данные первого человека
    age[0] = 21;
    name[0] = "Peter";
    surname[0] = "Ivanov";


    // Работа со сложным типом:
    Person person1;
    person1.age = 21;
    person1.name = "Peter";

    
    // Список для структуры
    Person persons[10];
    persons[0].age = 21;
    persons[0].name = "Ivan";


    // Работа с классом:
    Car car1(3, "Tesla", 160);
    std::cout << car1.Position() << std::endl;

    car1.Move(10);
    std::cout << car1.Position() << std::endl;

}