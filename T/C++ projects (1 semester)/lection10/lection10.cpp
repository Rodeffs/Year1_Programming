#include <iostream>
#include <vector>
using std::string;

/* vector - это класс, благодяря которому мы можем создавать динамический массив. Кго операции:

    push_back() - добавить в конец
    size() - размер вектора

    имя_вектора[0] - таким образом мы можем обратиться к элементу вектора, но может быть выход за границы
*/

/*
class String { // кастомная реализация String
private:
    int m_size;
    char* m_str;

public:
    String(char* str) {
        strcpy(m_str, str);
        m_size = strlen(str);
    }
};
*/

class Patient {
private:
    unsigned int m_id;
    string m_name;
    // this-> это указатель на класс, т.е. мы указываем на переменную в private и нам не надо по разному именовать перепенные в private и public

public:
    Patient(int id, string name) {
        m_id = id;
        m_name = name;
    }

    string Name() {
        return m_name;
    }
};

class Doctor {
private:
    unsigned int m_id;
    string m_name;
    std::vector<Patient*> m_patients;

public:
    Doctor(int id, string name) {
        m_id = id;
        m_name = name;
    }

    void AddPatient(Patient* patient) {
        m_patients.push_back(patient);
    }

    void PrintPatient() {
        for (int i = 0; i < m_patients.size(); i++)
            std::cout << m_patients[i]->Name() << std::endl; // -> значит то же, что и точка, только стрелку мы используем, если операция создана на стэкэ
    }
};

int main()
{
    /*
    Doctor doctor(0, "Pavel");
    Patient patient1(0, "Pasha");
    Patient patient2(1, "Petr");
    */

    Doctor* doctor = new Doctor(0, "Pavel");

    doctor->PrintPatient();

    Patient* patient1 = new Patient(1, "Pasha");

    doctor->AddPatient(patient1);

    doctor->PrintPatient();

    /* swap() работает только с одним типом данных, если переменные разного типа, то будет ошибка
    int a = 5, b = 10;
    std::swap(a, b);

    double c = 1.2, d = 5.8;
    std::swap(c, d);

    std::swap(a, c);
    */

    delete doctor;

    return 0;
}