#include <iostream>

using std::cout;
using std::endl;

struct Test {
    Test() = default;
    Test(const Test& t) = delete;
};

// шаблоны:
template<typename T, typename U> // типы данных должны быть конвертируемы между собой
void swap(T& a, U& b) { // универсальный swap
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename T, unsigned int N, int M>
class Matrix {
    T m_matrix[N][M];
public:
    void Print() {
        cout << N << " " << M << endl;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cout << m_matrix[i][j];
    }

    double determinant() {
        if (N == 2 && M == 2) {

        }
        else if(N == 3 && M == 3) {
            m_matrix[2][2];
        }
    }
};

// про explicit
struct Latitude {
    double lat;

    explicit Latitude(double lat): lat(lat) {}

    operator double() { // оператор приведения типа
        return lat;
    }
};

struct Longitude {
    double lon;

    explicit Longitude(double lon): lon(lon) {}
};

double SetMarker(Latitude lat, Longitude lon) {

}

void f(const int& x) {
    int & p = const_cast<int&>(x);
}

struct TwoWords {
    unsigned short x1;
    unsigned short x2;
};

using Matrix22i = Matrix<int, 2, 2>; // вместо typedef. В Matrix первое число - это размерность, а буква - тип данных
using Vector2i = Matrix<int, 2, 1>;

// Специализация шаблонов:
template<typename T>
class vector {
    vector() {
        cout << "all types apart from bool" << endl;
    }
};

int main() {

    // c-style cast
    int n = 10;
    int* p = &n;
    char* c = (char*)p;

    // static cast
    double d = static_cast<double>(n);

    // const cast
    int x = 1;
    f(x);
    cout << x << endl;

    // reinterpret cast
    unsigned char arr[4] = {232, 3, 0, 1};
    TwoWords* tw = reinterpret_cast<TwoWords*>(arr);
    cout << tw->x1 << " " << tw->x2 << endl;


    Latitude lat(54.111);
    Longitude lon(21.88);
    SetMarker(lat, lon);

    cout << static_cast<double>(lat) << endl;

    Test a;
    Test b;
//    swap(a, b); не сработает для структур, но для других типов данных выполнит

    Matrix<int, 2, 2> M; // таким образом создадим матрицу 2x2 с типом int

    return 0;
}
