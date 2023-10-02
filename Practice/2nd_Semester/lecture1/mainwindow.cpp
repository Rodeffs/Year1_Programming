#include "mainwindow.h"
#include "ui_mainwindow.h"

// !!! ВАЖНО: подключаем отдельно нужные нам библиотеки
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // !!! ВАЖНО - прописать эти две строки для трекинга мыши:
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#if 0 // !!! ВАЖНО - что писали до этого:
void MainWindow::paintEvent(QPaintEvent *) // функция внутри класса mainwindow
{
    // qDebug("vkcdjvljmlcgfdlg;dfg;"); - дебагинг, при каждом изменении окна выводится это сообщение

    /* !!! paintEvent вызывается НЕПРЕДСКАЗУЕМОЕ число раз в НЕПРЕДСКАЗУЕМОЕ время, поэтому в него НЕЛЬЗЯ помещать никакую логику !!! */


    QPainter painter(this); // в данном случае this (этот) указывает на то, что рисуем на экране, хотя можно и на ихображени


    // Рисуем крест там, где кликнули мышкой:
//    if (clicked) {
//        painter.drawLine(x-15, y+15, x+15, y-15); // здесь используется обратная система координат, т.е. x идёт вправо, а y вниз
//        painter.drawLine(x+15, y+15, x-15, y-15);
//    }


//    QBrush brush(Qt::red); - задаём цвет кисточки (заливки) одним из готовых цветов
    QBrush brush (QColor(0, 128, 128)); // задаём цвет кисточки (заливки) любым цветом в кодировки RGB

    QPen pen (Qt::red, 3); // задаём цвет карандаша (обводки), второй параметр отвечает за толщину

    QPen pen1 (Qt::DotLine); // задаём стиль
    pen1.setWidth(3);
    pen1.setColor(Qt::red);

    /* Возможные стили:
        NoPen,
        SolidLine,
        DashLine,
        DotLine,
        DashDotLine,
        DashDotDotLine,
        CustomDashLine
    */

    painter.setPen(pen1);  // применяем цвет карандаша (обводки)
    painter.setBrush(brush); // применяем цвет кисточки (заливки)
    painter.drawRect(100, 100, 200, 50);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    if (event->buttons() & Qt::LeftButton) - узнаём, какая кнопка мыши была нажата
//        qDebug("LMB click");

//    if (event->modifiers() & Qt::ControlModifier) - модификаторы (Ctrl, Alt, Shift)
//        qDebug("Control click");


    clicked = true; // т.к. mousePressEvent срабатывает раньше всего и рисует крест до того, как мы нажали мышку, то делаем проверку, дабы этого не случилось

    //    x = event->x(); - находим координаты, где кликнули мышкой
    //    y = event->y();
    QString message = QString("x = %1; y = %2").arg(event->x()).arg(event->y()); // .arg() - форматирование строки, таким образом нам не нужно писать тип данный, а просто %1 (первый arg), %2 (второй arg) и так далее

    message += QString("; x+y=");
    message += "; x+y="; // аналогично
    message += QString::number(100); // таким образом можем добавить число к строке

//    QMessageBox::information(this, "Cursor coordinates", message); // выводит диалоговое окно с задаными параметрами

    qDebug()<<message; // таким образом выводим в консоль


    // Выводим все модификаторы одной строкой:
    QString msg = QString("");
    msg += (event->modifiers() & Qt::ControlModifier) ? "Control " : "";
    msg += (event->modifiers() & Qt::AltModifier) ? "Alt " : "";
    msg += (event->modifiers() & Qt::ShiftModifier) ? "Shift " : "";
    msg += "Click";
    qDebug()<<msg;


    repaint(); // перерисовываем
}
#endif  // конец невыполнимого участка кода

#if 0
void MainWindow::paintEvent(QPaintEvent *) // функция внутри класса mainwindow
{
    QPainter painter(this);


    // Добавление текстуры:
//    QImage grass("C:/Users/ALPilipenko/Desktop/img/grass16x16.GIF"); - абсолютный путь, может отличаться
    QImage grass(":/rsc/img/grass16x16.GIF"); // добавление через относительные пути

    /* Гайд, как добавить изображения в Qt:

    1. Переносим папку с изображениями в корневую папку
    2. ПКМ по папке проекта слева (в данном случае lecture1) -> Добавить новый -> Qt -> Файл ресурсов
    3. Даём ему имя
    4. Теперь, когда он слева в меню, ПКМ по нему -> Добавить существ. каталог -> Выбираем эту папку
    5. В коде указываем относительные пути, см. выше
    6. ПКМ опять по папке проекта -> Запустить qmake
    7. Запускаем проект. Готово!
    */

    QBrush brush;
    brush.setTextureImage(grass);
    painter.setBrush(brush);
    painter.drawRect(contentsRect()); // таким образом трава займёт всё поле, не зависимо от размера


    // Добавление изображения:
    QImage flower(":/rsc/img/flower.jpg");
    painter.drawImage(QRect(100, 50, 29, 300), flower); // вставляем изображение, первый параметри её масштабирует (последние два числа в QRect())
}
#endif

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPen pen (Qt::blue, 1); // задаём стиль рамки
    QBrush brush (QColor(0, 0, 255, 50)); // задаём стиль заливки через метод QColor (первые 3 параметра - это RGB кодировка, а последний - прозрачность)
    painter.setPen(pen);
    painter.setBrush(brush);

    if (clicked)
        painter.drawRect(x, y, x1-x, y1-y);
}

void MainWindow::mousePressEvent(QMouseEvent *event) // когда нажимаем по мыши
{
    clicked = true;
    x = event->x();
    y = event->y();

    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) // когда отпускаем мышь
{
    clicked = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) // когда двигаем мышь
{
    x1 = event->x();
    y1 = event->y();

    repaint();
}
