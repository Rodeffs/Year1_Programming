#include <iostream>
#include <fstream> // для работы с файлами0

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;

template <typename T, int N, int M>
class matrix {

    T m[N][M];

//    template <typename T, int N, int M>
//    friend std::istream& operator>>(std::istream& in, matrix<T, N, M>& other);

        public:
    matrix() {
        m[0][0] = 0;
    }
//    void det() {
//        if constexpr (N == 2) { // constexpr значит, что выражение в скобках вычисляется на этапе компиляции
//
//        }
//    }
};

/*
template<typename T, int N, int M>
std::istream& operator>>(std::istream& in, matrix<T, N, M>& other) {
    for (int i = 0; i < N, i++)

}
*/

void f() {
    static int count = 0; // статическая переменная уничтожается после выполнения программы, отличается от heap и stack
    count++;
    cout << count << endl;
}

enum class LogLevel {
    DEBUG,
    RELEASE
};

class Log {
private:
    static ofstream m_out;
    static LogLevel m_loglevel;
public:
    Log() {
        cout << "created" << endl;
    }

    static void setLogLevel(LogLevel logLevel) {
        m_loglevel = logLevel;
    }

    static void setLogPath(const string& path) {
        m_out.open(path);
    }

    static void Write(const string& msg) { // статический вывод
        if (m_loglevel == LogLevel::DEBUG)
            cout << msg << endl;
        m_out << msg << endl;
    }
    ~Log() {
        cout << "destroyed"<< endl;
    }
};

ofstream Log::m_out;

int main() {
    matrix<int, 2, 2> m;
//    m.det();

    f();
    f();

    Log::setLogPath("log.txt");
    Log::Write("hello");

    return 0;
}
