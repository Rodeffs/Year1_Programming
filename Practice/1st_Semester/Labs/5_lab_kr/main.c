#include <stdio.h> /* Контрольная работа №5.  */
#include <math.h>
float traverse_clockwise(float coord[], const int n) {
    float perimeter = 0, vectors[50][3] = {0}, centreX = 0, centreY = 0, mainVector[2] = {0}; // Идея в том, чтобы провести радиус-вектор от центра к точке, затем найти углы между ним и другими радиус-векторами и по этим углам определить, в какую сторону пойдёт отсчёт
    for (int i = 0; i < n << 1; i += 2) // vectors[][0] - это угол между главным вектором и данным радиус-вектором, vectors[][1] - координата x данного радиус-вектора, vectors[][2] - координата y данного радиус-вектора
        centreX += coord[i], centreY += coord[i+1]; // Находим центр фигуры по формуле x0 = сумма координат x всех точек / на их количество, аналогично для y0
    centreX /= n, centreY /= n, mainVector[0] = coord[0] - centreX, mainVector[1] = coord[1] - centreY, vectors[0][1] = coord[0], vectors[0][2] = coord[1]; // Координаты центра и главного вектора
    for (int i = 2; i < n << 1; i += 2) {
        float a = coord[i] - centreX, b = coord[i+1] - centreY;
        float plusPI = (b - a * mainVector[1] / mainVector[0]) > 0 ? 180 : 0; // Нам нужно знать по какую сторону от главного вектора находиться точка, если слева - то ничего не прибавляем, а если справа - то плюс 180 градусов
        vectors[i>>1][0] = plusPI + (180/3.14) * acosf((mainVector[0] * a + mainVector[1] * b) / sqrtf((powf(mainVector[0], 2) + powf(mainVector[1], 2)) * (powf(a, 2) + powf(b, 2)))); // Угол находим по формуле скалярного произведения векторов (из неё его проще всего выразить)
        vectors[i>>1][1] = coord[i], vectors[i>>1][2] = coord[i+1];
    }
    for (int i = 0; i < n-1; i++) // Пузырьковая сортировка для расположения точек в нужном порядке
        for (int j = i+1; j < n; j++)
            if (vectors[j][0] <= vectors[i][0])
                for (int k = 0; k < 3; k++) {
                    float tmp = vectors[j][k];
                    vectors[j][k] = vectors[i][k], vectors[i][k] = tmp; // Меняем все значения, не только угла, но и координат, иначе будет несоответствие
                }
    for (int i = 0; i < n-1; i++)
        perimeter += sqrtf(powf(vectors[i + 1][1] - vectors[i][1], 2) + powf(vectors[i + 1][2] - vectors[i][2], 2));
    return perimeter + sqrtf(powf(vectors[0][1] - vectors[n - 1][1], 2) + powf(vectors[0][2] - vectors[n - 1][2], 2)); // Не забываем прибавить значение последней стороны (в цикле оно не считается)
}
int main() {
    float rect[] = {1,5,7,1,7,5,1,1}, star[] = {3.97, 0.82, 2.26, 3.69, 5.39, 2.16, 2.03, 2.11, 5.36, 4.06}, enneagon[] = {76, 67.1, -8.3, 18, 55, 93.3, 77, 33, 21.3, 99, -20, 50, -8.3, 82, 55, 6.7, 21.3, 0.76};
    const int N1 = 4, N2 = 5, N3 = 9;
    printf("The perimeter of rectangle is %f\nThe perimeter of star is %f\nThe perimeter of enneagon is %f\n", traverse_clockwise(rect, N1), traverse_clockwise(star, N2), traverse_clockwise(enneagon, N3));
    return 0;
}

/* Сокращённая версия
#include <stdio.h> // Контрольная работа №5. 
#include <math.h>
float traverse_clockwise(float coord[], const int n) {
    float perimeter = 0, vectors[50][3] = {0}, x0 = 0, y0 = 0, mainVector[2] = {0}; // Идея в том, чтобы провести радиус-вектор от центра к точке, затем найти углы между ним и другими радиус-векторами и по этим углам определить, в какую сторону пойдёт отсчёт
    for (int i = 0; i < (n << 1); i += 2) // vectors[][0] - это угол между главным вектором и данным радиус-вектором, vectors[][1] - координата x данного радиус-вектора, vectors[][2] - координата y данного радиус-вектора
        x0 += coord[i], y0 += coord[i+1]; // Находим центр фигуры по формуле x0 = сумма координат x всех точек / на их количество, аналогично для y0
    x0 /= n, y0 /= n, mainVector[0] = coord[0] - x0, mainVector[1] = coord[1] - y0, vectors[0][1] = coord[0], vectors[0][2] = coord[1]; // Координаты центра и главного вектора
    for (int i = 2; i < (n << 1); i += 2)  // Нам нужно знать по какую сторону от главного вектора находиться точка, если слева - то ничего не прибавляем, а если справа - то плюс 180 градусов. Угол находим по формуле скалярного произведения векторов (из неё его проще всего выразить)
        vectors[i>>1][0] = (((coord[i+1]-y0) - (coord[i]-x0) * mainVector[1] / mainVector[0]) > 0 ? 180 : 0) + (180/3.14) * acosf((mainVector[0] * (coord[i]-x0) + mainVector[1] * (coord[i+1]-y0)) / sqrtf((powf(mainVector[0], 2) + powf(mainVector[1], 2)) * (powf((coord[i]-x0), 2) + powf((coord[i+1]-y0), 2)))), vectors[i>>1][1] = coord[i], vectors[i>>1][2] = coord[i+1];
    for (int i = 0; i < n-1; i++) // Пузырьковая сортировка для расположения точек в нужном порядке
        for (int j = i+1; j < n; j++)
            if (vectors[j][0] <= vectors[i][0])
                for (int k = 0; k < 3; k++) {
                    float tmp = vectors[j][k];
                    vectors[j][k] = vectors[i][k], vectors[i][k] = tmp; // Меняем все значения, не только угла, но и координат, иначе будет несоответствие
                }
    for (int i = 0; i < n-1; i++)
        perimeter += sqrtf(powf(vectors[i+1][1] - vectors[i][1], 2) + powf(vectors[i+1][2] - vectors[i][2], 2));
    return perimeter + sqrtf(powf(vectors[0][1]-vectors[n-1][1], 2) + powf(vectors[0][2]-vectors[n-1][2], 2)); // Не забываем прибавить значение последней стороны (в цикле оно не считается)
}
int main() {
    float rect[] = {1,5,7,1,7,5,1,1}, star[] = {3.97, 0.82, 2.26, 3.69, 5.39, 2.16, 2.03, 2.11, 5.36, 4.06}, enneagon[] = {76, 67.1, -8.3, 18, 55, 93.3, 77, 33, 21.3, 99, -20, 50, -8.3, 82, 55, 6.7, 21.3, 0.76};
    const int N1 = 4, N2 = 5, N3 = 9;
    printf("The perimeter of rectangle is %f\nThe perimeter of star is %f\nThe perimeter of enneagon is %f\n", traverse_clockwise(rect, N1), traverse_clockwise(star, N2), traverse_clockwise(enneagon, N3));
    return 0;
}*/

/* Версия со структурами
#include <stdio.h> // Контрольная работа №5. Сделал Пилипенко Александр, 1 ПМ, 4 гр. АДМО
#include <math.h>
typedef struct vector {
    float a; // angle
    float x;
    float y;
} newVector;
float traverse_clockwise(const float coord[], const int n) {
    float perimeter = 0, centreX = 0, centreY = 0, mainVector[2] = {0}; // Идея в том, чтобы провести радиус-вектор от центра к точке, затем найти углы между ним и другими радиус-векторами и по этим углам определить, в какую сторону пойдёт отсчёт
    for (int i = 0; i < n << 1; i += 2)
        centreX += coord[i], centreY += coord[i+1]; // Находим центр фигуры по формуле x0 = сумма координат x всех точек / на их количество, аналогично для y0
    centreX /= n, centreY /= n;
    mainVector[0] = coord[0] - centreX, mainVector[1] = coord[1] - centreY;
    newVector vectors[50];
    vectors[0].x = coord[0], vectors[0].y = coord[1]; // Координаты центра и главного вектора
    for (int i = 2; i < n << 1; i += 2) {
        float a = coord[i] - centreX, b = coord[i+1] - centreY;
        float plusPI = (b - a * mainVector[1] / mainVector[0]) > 0 ? 180 : 0; // Нам нужно знать по какую сторону от главного вектора находиться точка, если слева - то ничего не прибавляем, а если справа - то плюс 180 градусов
        vectors[i>>1].a = plusPI + (180/3.14) * acosf((mainVector[0] * a + mainVector[1] * b) / sqrtf((powf(mainVector[0], 2) + powf(mainVector[1], 2)) * (powf(a, 2) + powf(b, 2)))); // Угол находим по формуле скалярного произведения векторов (из неё его проще всего выразить)
        vectors[i>>1].x = coord[i], vectors[i>>1].y = coord[i+1];
    }
    for (int i = 1; i < n-1; i++) // Пузырьковая сортировка для расположения точек в нужном порядке
        for (int j = i+1; j < n; j++)
            if (vectors[j].a <= vectors[i].a) {
                    newVector tmp = vectors[j];
                    vectors[j] = vectors[i];
                    vectors[i] = tmp;
            }
    for (int i = 0; i < n-1; i++)
        perimeter += sqrtf(powf(vectors[i+1].x - vectors[i].x, 2) + powf(vectors[i+1].y - vectors[i].y, 2));
    return perimeter + sqrtf(powf(vectors[0].x- vectors[n-1].x, 2) + powf(vectors[0].y - vectors[n-1].y, 2)); // Не забываем прибавить значение последней стороны (в цикле оно не считается)
}
int main() {
    float rect[] = {1,5,7,1,7,5,1,1}, star[] = {3.97, 0.82, 2.26, 3.69, 5.39, 2.16, 2.03, 2.11, 5.36, 4.06}, enneagon[] = {76, 67.1, -8.3, 18, 55, 93.3, 77, 33, 21.3, 99, -20, 50, -8.3, 82, 55, 6.7, 21.3, 0.76};
    printf("The perimeter of rectangle is %f\nThe perimeter of star is %f\nThe perimeter of enneagon is %f\n", traverse_clockwise(rect,  (sizeof (rect)/sizeof (float))>>1), traverse_clockwise(star, (sizeof (star)/sizeof (float))>>1), traverse_clockwise(enneagon, (sizeof (enneagon)/sizeof (float))>>1));
    return 0;
}*/

/* 1 ревизия
#include <stdio.h> // Контрольная работа №5. Сделал Пилипенко Александр, 1 ПМ, 4 гр. АДМО
#include <math.h>
float maxDif(float coord[], int type, int n) {
    float min = 0, max = 0;
    for (int i = 0; i < n - 1; i += 2)
        type == 'x' ? (min = (coord[i] < min) ? coord[i] : min, max = (coord[i] > max) ? coord[i] : max) : (min = (coord[i+1] < min) ? coord[i+1] : min, max = (coord[i+1] > max) ? coord[i+1] : max);
    return max - min;
}
int closest_point(float coord[], int i, int n) {
    int c = 0;
    float minDifX = maxDif(coord, 'x', n), minDifY = maxDif(coord, 'y', n);
    for (int j = 0; j < n-1; j+=2) {
        if ((coord[i] != coord[j])&&(coord[i+1] != coord[j+1])) {
            float difX = ((coord[i]   - coord[j])   > 0) ? (coord[i]   - coord[j])   : -(coord[i]   - coord[j]);
            float difY = ((coord[i+1] - coord[j+1]) > 0) ? (coord[i+1] - coord[j+1]) : -(coord[i+1] - coord[j+1]);
            if ((difX < minDifX) && (difY < minDifY))
                c = j, minDifX = difX, minDifY = difY;
        }
    }
    return c;
}
float traverse_clockwise(float coord[], int n) {
    float perimeter = 0, vectorsArr[4][2] = {0};
    int iPrev = 0;
    for (int i = 0; i < n-1; i+=2) {
            float x = coord[i]   - coord[closest_point(coord, i, n)];
            float y = coord[i+1] - coord[closest_point(coord, i, n)+1];
            for (int j = 0; j < n; j++) {
                if ((vectorsArr[j][0] == x)&&(vectorsArr[j][1] == y))
                    break;
                if ((!vectorsArr[j][0])&&(!vectorsArr[j][1])) {
                    vectorsArr[j][0] = x, vectorsArr[j][1] = y, iPrev = i;
                    perimeter += sqrt(pow(x, 2) + pow(y, 2));
                }
            }
        }
    return perimeter;
}
int main() {
    const int N = 4;
    float rect[] = {1,5,7,1,7,5,1,1};
//    float star[] = {3.97, 0.82, 2.26, 3.69, 5.39, 2.16, 2.03, 2.11, 5.36, 4.06};
//    float enneagon[] = {76, 67.1, -8.3, 18, 55, 93.3, 77, 33, 21.3, 99, -20, 50, -8.3, 82, 55, 6.7, 21.3, 0.76};

    printf("The perimeter of rectangle is %f\n", traverse_clockwise(rect, N));
//    printf("The perimeter of star is %f\n", traverse_clockwise(star, N));
//    printf("The perimeter of enneagon is %f\n", traverse_clockwise(enneagon, N));
    return 0;
}

*/