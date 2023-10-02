// Наследование

#include <iostream>
#include <vector>
using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::endl;

enum class color {
    WHITE, PINK,
};

enum class animalType {
    CAT, DOG,
};

class animal {
private:
    string m_name;
    int m_age;
    color m_color;

protected: // - это спецификатор, который даёт доступ к данным для наследуемых классов, но только для них (т.е. работает как public для наследуемых и как private для остальных)
    animalType m_type;
    int* m_mas;

public:
    animal(const string& name, int age, color color) : m_name(name), m_age(age), m_color(color) {
        cout << "animal constructed" << endl;
    }

    virtual ~animal() { // virtual всегда нужно писать в наследуемом классе, чтобы оба деструктора вызывались
        cout << "animal destroyed" << endl;
    }

//    virtual void say() { - здесь тоже нужно писать virtual, иначе не получиться этот метод переопределить в наследуемых классах
//        cout << "ANIMAL SOUND" << endl;
//    }

    virtual void say() = 0; // чисто виртуальная функция, она не определена. Класс с виртуальным методом называется абстрактным
    // Теперь мы не можем создать объект этого класса, не дав метод say(), т.к. в таком случае этот метод будет не реализован

    void eat() {
        cout << "ANIMAL EATS" << endl;
    }

    void setName(const string& name) {
        m_name = name;
    }
};

class cat : public animal { // реализация наследования, класс кошка наследует класс животное, нужно писать public, т.к. без него не будет доступа к приватным полям
public:
    cat(const string& name, int age, color color) : animal(name, age, color) { // здесь вызываем конструктор родительского класса
        m_type = animalType::CAT;
        cout << "cat constructed" << endl;
    }

    virtual ~cat() { // virtual всегда нужно писать в наследуемом классе, чтобы оба деструктора вызывались
        cout << "cat destroyed" << endl;
    }

    virtual void say() override {
        cout << "MEOW" << endl;
    }
};

class dog : public animal {
public:
    dog(const string& name, int age, color color) : animal(name, age, color) {
        m_type = animalType::DOG;
        cout << "dog constructed" << endl;
        m_mas = new int[10];
    }

    virtual ~dog() {
        cout << "dog destroyed" << endl;
        delete[] m_mas;
    }

    virtual void say() override { // override пишется, когда мы переопределяем метод родительского класса
        cout << "BARK" << endl;
    }

    void bones() {
        cout << "bones" << endl;
    }
};

class chihuahua : public dog { // наследуемые классы также могут быть родительскими и так далее
public:
    chihuahua(const string& name, int age, color color) : dog(name, age, color) {}
    virtual ~chihuahua() {
        cout << "chihuahua destroyed" << endl;
    }

    void say() override {
        cout << "...bark" << endl;
    }
};

int main() {
//    cat barsik("barsik", 1, color::WHITE);
//    barsik.say();
//    dog tuzik("tuzik", 2, color::WHITE);
//    tuzik.say();

    vector<animal*> zoo; // массив зверей в зоопарке

    animal* barsik = new cat("barsik", 1, color::WHITE);
    zoo.push_back(barsik);

    animal* tuzik = new dog("tuzik", 2, color::WHITE);
    zoo.push_back(tuzik);

    animal* princess = new chihuahua("princess", 1, color::PINK);
    zoo.push_back(princess);

    for (animal* animal : zoo) { // благодаря такому циклу берём каждый объект из массива
        animal->say();
    }

    for (int i = 0; i < zoo.size(); i++)
        delete zoo[i]; // не забываем удалять
    return 0;
}
