#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExpValidator>
#include <QTimer>
#include <QTime>

QPixmap *pix_array; // Картинка, визуализирующая работу шифров

QTimer* time_res; // Время, по истченеии которого рамка области "Результат" будет подсвечиавться зеленым
                  // После нажатия кнопки "Зашифровать"/"Расшифровать"

QString* style_keys; // Стиль для виджетов

int table_4 [5][5]= {{11, 24, 7, 20, 3},
                     {4, 12, 25, 8, 16},
                     {17, 5, 13, 21, 9},
                     {10, 18, 1, 14, 22},
                     {23, 6, 19, 2, 15}}; // Таблица ключей магического квадрата

QString table_5 [6] = {"апрстё",
                       "лбыьжу",
                       "мявз,ф",
                       "н.иг х",
                       "ойэюдц",
                       "къщшче"}; // Таблица символов полибианского квадрата

QString alpha = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"; // Строка-алфавит (С РУССКОЙ БУКВОЙ "Ё") из строчных русских букв
                                                     // Для шифров Цезаря, Гронсфельда и Виженера

QString table_9a [7] = {"жщнюр",
                        "итьцб",
                        "яме.с",
                        "выпч ",
                        ":дуок",
                        "зэфгш",
                        "ха,лъ"}; // Первая таблица для шифра Уитстона

QString table_9b [7] = {"ичгят",
                        ",жьмо",
                        "зюрвщ",
                        "ц:пел",
                        "ъан.х",
                        "эксшд",
                        "бфуы "}; // Вторая таблица для шифра Уитстона

MainWindow::MainWindow(QWidget *parent) // Формирование начанльного окна
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Установка иконки
    QIcon icon(":/Resources/Images/icon.png");
    setWindowIcon(icon);
    //

    ui->Message->setStyleSheet("border: 1.5px solid black");
    ui->Result->setStyleSheet("border: 1.5px solid grey");

    // Добавление в выпадающий список строк с названием методов
    QStringList methods;
    methods.push_back("Скитала");
    methods.push_back("Шифрующие таблицы");
    methods.push_back("Двойная перестановка");
    methods.push_back("Магичесикй квадрат");
    methods.push_back("Полибианский квадрат");
    methods.push_back("Шифр Цезаря");
    methods.push_back("Шифр Гронсфельда");
    methods.push_back("Система Виженера");
    methods.push_back("Шифр Уитстона");
    ui->Method->addItems(methods);
    //

    // Добавление в массив картинок с изображением работы методов
    pix_array = new QPixmap[9];
    pix_array[0] = *new QPixmap(":/Resources/Images/1.png");
    pix_array[1] = *new QPixmap(":/Resources/Images/2.png");
    pix_array[2] = *new QPixmap(":/Resources/Images/3.png");
    pix_array[3] = *new QPixmap(":/Resources/Images/4.png");
    pix_array[4] = *new QPixmap(":/Resources/Images/5.png");
    pix_array[5] = *new QPixmap(":/Resources/Images/6.png");
    pix_array[6] = *new QPixmap(":/Resources/Images/7.png");
    pix_array[7] = *new QPixmap(":/Resources/Images/8.png");
    pix_array[8] = *new QPixmap(":/Resources/Images/9.png");
    //

    style_keys = new QString(ui->Key_A->styleSheet());

    //Установка таймера для подсвечивания области "Результат" зеленым цветом
    time_res = new QTimer();
    time_res->setInterval(1500);
    //

    connect(ui->Method, SIGNAL(currentIndexChanged(int)), this, SLOT(selected_method()));
    connect(time_res, SIGNAL(timeout()), this, SLOT(update_res()));
    selected_method();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selected_method(){ // Выбор метода шифрования (согласно значению выбранного индекса в выпадающем списке)
    switch(ui->Method->currentIndex())
    {
    case 0:
    {
        key_A_valid.setRegExp(QRegExp("[2-9]{1}"));
        ui->Key_A->setValidator(&key_A_valid);
        ui->Key_A->setEnabled(true);
        ui->Key_A_Valid->setEnabled(true);
        ui->Key_B->setFrame(false);
        ui->Key_B->setEnabled(false);
        ui->Key_B_Valid->setEnabled(false);
        ui->Key_B_Valid->clear();
        message_valid.setRegExp(QRegExp("^(.){36}$"));
        ui->Message->setValidator(&message_valid);
        ui->Message->clear();
        ui->Message->setStyleSheet("border: 1.5px solid yellow");
        ui->Message_Valid->setText("Введите исходное сообщение (не менее 6 символов):");
        ui->Key_A_Valid->setText("Введите ключ (кол-во столбцов, цифра от 2 до 9):");
        ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
        ui->Key_A->clear();
        ui->Key_B->clear();
        ui->Key_B->setStyleSheet(*style_keys);
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        connect(ui->Message, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->Key_A, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->PB1, SIGNAL(clicked()), this, SLOT(on_clicked_1()));
        connect(ui->PB2, SIGNAL(clicked()), this, SLOT(on_clicked_2()));
        break;
    }
    case 1:
    {
        key_A_valid.setRegExp(QRegExp("[1-7]{7}"));
        ui->Key_A->setValidator(&key_A_valid);
        ui->Key_A->setEnabled(true);
        ui->Key_A_Valid->setEnabled(true);
        ui->Key_B->setFrame(false);
        ui->Key_B->setEnabled(false);
        ui->Key_B_Valid->setEnabled(false);
        message_valid.setRegExp(QRegExp("^(.){35}$"));
        ui->Message->setValidator(&message_valid);
        ui->Message->clear();
        ui->Message->setStyleSheet("border: 1.5px solid yellow");
        ui->Message_Valid->setText("Введите исходное сообщение (не менее 6-ти символов):");
        ui->Key_A_Valid->setText("Введите ключ (порядок перестановки столбцов, неповторяющиеся цифры от 1 до 7):");
        ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
        ui->Key_A->clear();
        ui->Key_B->clear();
        ui->Key_B->setStyleSheet(*style_keys);
        ui->Key_B_Valid->clear();
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        connect(ui->Message, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->Key_A, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->PB1, SIGNAL(clicked()), this, SLOT(on_clicked_1()));
        connect(ui->PB2, SIGNAL(clicked()), this, SLOT(on_clicked_2()));
        break;
    }
    case 2:
    {
        ui->Key_A->setFrame(true);
        ui->Key_A->setEnabled(true);
        ui->Key_A_Valid->setEnabled(true);
        key_A_valid.setRegExp(QRegExp("[1-5]{5}"));
        ui->Key_A->setValidator(&key_A_valid);
        ui->Key_B->setFrame(true);
        ui->Key_B->setEnabled(true);
        ui->Key_B_Valid->setEnabled(true);
        key_B_valid.setRegExp(QRegExp("[1-5]{5}"));
        ui->Key_B->setValidator(&key_B_valid);
        message_valid.setRegExp(QRegExp("^(.){25}$"));
        ui->Message->setValidator(&message_valid);
        ui->Message->clear();
        ui->Message->setStyleSheet("border: 1.5px solid yellow");
        ui->Message_Valid->setText("Введите исходное сообщение (не менее 4-ех символов):");
        ui->Key_A_Valid->setText("Введите ключ 1 (порядок перестановки столбцов, неповторяющиеся цифры от 1 до 5):");
        ui->Key_B_Valid->setText("Введите ключ 2 (порядок перестановки строк, неповторяющиеся цифры от 1 до 5):");
        ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
        ui->Key_A->clear();
        ui->Key_B->setStyleSheet("border: 1.5px solid yellow");
        ui->Key_B->clear();
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        connect(ui->Message, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->Key_A, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->Key_B, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->PB1, SIGNAL(clicked()), this, SLOT(on_clicked_1()));
        connect(ui->PB2, SIGNAL(clicked()), this, SLOT(on_clicked_2()));
        break;
    }
    case 3:
    {
        ui->Key_A->setFrame(false);
        ui->Key_A->setEnabled(false);
        ui->Key_A_Valid->setEnabled(false);
        ui->Key_B->setFrame(false);
        ui->Key_B->setEnabled(false);
        ui->Key_B_Valid->setEnabled(false);
        ui->Key_A->setStyleSheet(*style_keys);
        ui->Key_B->setStyleSheet(*style_keys);
        ui->Key_A_Valid->clear();
        ui->Key_B_Valid->clear();
        message_valid.setRegExp(QRegExp("^(.){25}$"));
        ui->Message->setValidator(&message_valid);
        ui->Message->clear();
        ui->Message->setStyleSheet("border: 1.5px solid yellow");
        ui->Message_Valid->setText("Введите исходное сообщение (не менее 5-ти символов):");
        ui->Key_A->clear();
        ui->Key_B->clear();
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        connect(ui->Message, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->Key_A, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->PB1, SIGNAL(clicked()), this, SLOT(on_clicked_1()));
        connect(ui->PB2, SIGNAL(clicked()), this, SLOT(on_clicked_2()));
        break;
    }
    case 4:
    {
        ui->Key_A->setFrame(false);
        ui->Key_A->setEnabled(false);
        ui->Key_A_Valid->setEnabled(false);
        ui->Key_B->setFrame(false);
        ui->Key_B->setEnabled(false);
        ui->Key_B_Valid->setEnabled(false);
        ui->Key_A->setStyleSheet(*style_keys);
        ui->Key_B->setStyleSheet(*style_keys);
        ui->Key_A_Valid->clear();
        ui->Key_B_Valid->clear();
        message_valid.setRegExp(QRegExp("^[а-яё., ]{18}$"));
        ui->Message->setValidator(&message_valid);
        ui->Message->clear();
        ui->Message->setStyleSheet("border: 1.5px solid yellow");
        ui->Message_Valid->setText("Введите исходное сообщение (не менее 6-ти символов, которыми могут являться строчные буквы русского алфавита, точка, запятая и пробел):");
        ui->Key_A->clear();
        ui->Key_B->clear();
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        connect(ui->Message, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->Key_A, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->PB1, SIGNAL(clicked()), this, SLOT(on_clicked_1()));
        connect(ui->PB2, SIGNAL(clicked()), this, SLOT(on_clicked_2()));
        break;
    }
    case 5:
    {
        ui->Key_A->setFrame(true);
        ui->Key_A->setEnabled(true);
        ui->Key_A_Valid->setEnabled(true);
        key_A_valid.setRegExp(QRegExp("[0-9]{1}"));
        ui->Key_B->setFrame(false);
        ui->Key_B->setEnabled(false);
        ui->Key_B_Valid->setEnabled(false);
        ui->Key_B->setStyleSheet(*style_keys);
        ui->Key_A_Valid->clear();
        ui->Key_B_Valid->clear();
        message_valid.setRegExp(QRegExp("^[а-яё]{18}$"));
        ui->Message->setValidator(&message_valid);
        ui->Message->clear();
        ui->Message->setStyleSheet("border: 1.5px solid yellow");
        ui->Message_Valid->setText("Введите исходное сообщение (не менее 6-ти символов, которыми могут являться строчные буквы русского алфавита):");
        ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
        ui->Key_A_Valid->setText("Введите ключ (цифра):");
        ui->Key_A->clear();
        ui->Key_B->clear();
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        connect(ui->Message, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->Key_A, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->PB1, SIGNAL(clicked()), this, SLOT(on_clicked_1()));
        connect(ui->PB2, SIGNAL(clicked()), this, SLOT(on_clicked_2()));
        break;
    }
    case 6:
    {
        ui->Key_A->setFrame(true);
        ui->Key_A->setEnabled(true);
        ui->Key_A_Valid->setEnabled(true);
        key_A_valid.setRegExp(QRegExp("[0-9]{6}"));
        ui->Key_B->setFrame(false);
        ui->Key_B->setEnabled(false);
        ui->Key_B_Valid->setEnabled(false);
        ui->Key_B->setStyleSheet(*style_keys);
        ui->Key_A_Valid->clear();
        ui->Key_B_Valid->clear();
        message_valid.setRegExp(QRegExp("^[а-яё]{18}$"));
        ui->Message->setValidator(&message_valid);
        ui->Message->clear();
        ui->Message->setStyleSheet("border: 1.5px solid yellow");
        ui->Message_Valid->setText("Введите исходное сообщение (не менее 6-ти символов, которыми могут являться строчные буквы русского алфавита):");
        ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
        ui->Key_A_Valid->setText("Введите ключ (не мнеее 2-ух цифр):");
        ui->Key_A->clear();
        ui->Key_B->clear();
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        connect(ui->Message, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->Key_A, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->PB1, SIGNAL(clicked()), this, SLOT(on_clicked_1()));
        connect(ui->PB2, SIGNAL(clicked()), this, SLOT(on_clicked_2()));
        break;
    }
    case 7:
    {
        ui->Key_A->setFrame(true);
        ui->Key_A->setEnabled(true);
        ui->Key_A_Valid->setEnabled(true);
        key_A_valid.setRegExp(QRegExp("[а-яё]{9}"));
        ui->Key_B->setFrame(false);
        ui->Key_B->setEnabled(false);
        ui->Key_B_Valid->setEnabled(false);
        ui->Key_B->setStyleSheet(*style_keys);
        ui->Key_A_Valid->clear();
        ui->Key_B_Valid->clear();
        message_valid.setRegExp(QRegExp("^[а-яё]{18}$"));
        ui->Message->setValidator(&message_valid);
        ui->Message->clear();
        ui->Message->setStyleSheet("border: 1.5px solid yellow");
        ui->Message_Valid->setText("Введите исходное сообщение (не менее 6-ти символов, которыми могут являться строчные буквы русского алфавита):");
        ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
        ui->Key_A_Valid->setText("Введите ключ (не мнеее 3-ёх символов, которыми могут являться строчные буквы русского алфавита):");
        ui->Key_A->clear();
        ui->Key_B->clear();
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        connect(ui->Message, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->Key_A, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->PB1, SIGNAL(clicked()), this, SLOT(on_clicked_1()));
        connect(ui->PB2, SIGNAL(clicked()), this, SLOT(on_clicked_2()));
        break;
    }
    case 8:
    {
        ui->Key_A->setFrame(false);
        ui->Key_A->setEnabled(false);
        ui->Key_A_Valid->setEnabled(false);
        ui->Key_B->setFrame(false);
        ui->Key_B->setEnabled(false);
        ui->Key_B_Valid->setEnabled(false);
        ui->Key_A->setStyleSheet(*style_keys);
        ui->Key_B->setStyleSheet(*style_keys);
        ui->Key_A_Valid->clear();
        ui->Key_B_Valid->clear();
        message_valid.setRegExp(QRegExp("^[а-еж-ик-я.,: ]{16}$"));
        ui->Message->setValidator(&message_valid);
        ui->Message->clear();
        ui->Message->setStyleSheet("border: 1.5px solid yellow");
        ui->Message_Valid->setText("Введите исходное сообщение (не менее 4-ех символов, которыми могут являться строчные буквы русского алфавита (кроме ё, й), точка, запятая, двоеточие и пробел):");
        ui->Key_A->clear();
        ui->Key_B->clear();
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        connect(ui->Message, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->Key_A, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
        connect(ui->PB1, SIGNAL(clicked()), this, SLOT(on_clicked_1()));
        connect(ui->PB2, SIGNAL(clicked()), this, SLOT(on_clicked_2()));
        break;
    }
    }
ui->Picture->setPixmap(pix_array[ui->Method->currentIndex()]); // Установка картинки, соответствующей шифру
}

void MainWindow::on_changed(){ // Процесс валидации при любом изменении исходного сообщения или ключа
    switch(ui->Method->currentIndex())
    {
    case 0:
    {
        bool message = false;
        bool key_1 = true;
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        if (ui->Message->text().length() < 6)
        {
            ui->Message->setStyleSheet("border: 1.5px solid yellow");
            ui->Message_Valid->setText("Введите исходное сообщение (не менее 6-ти символов):");
            message = true;
        }
        else
        {
            ui->Message->setStyleSheet("border: 1.5px solid green");
            ui->Message_Valid->setText("Исходное сообщение готово!");
        }
        key_1 = false;
        if (ui->Key_A->text().length() == 0)
        {
            ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
            ui->Key_A_Valid->setText("Введите ключ (кол-во столбцов, цифра от 2 до 9):");
            key_1 = true;
        }
        if (key_1 != true)
        {
        ui->Key_A->setStyleSheet("border: 1.5px solid green");
        ui->Key_A_Valid->setText("Ключ готов!");
        }
        if (message == false && key_1 == false)
        {
            ui->PB1->setEnabled(true);
            ui->PB2->setEnabled(true);
        }
        break;
    }
    case 1:
    {
        bool message = false;
        bool key_1 = true;
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        if (ui->Message->text().length() < 6)
        {
            ui->Message->setStyleSheet("border: 1.5px solid yellow");
            ui->Message_Valid->setText("Введите исходное сообщение (не менее 6-ти символов):");
            message = true;
        }
        else
        {
            ui->Message->setStyleSheet("border: 1.5px solid green");
            ui->Message_Valid->setText("Исходное сообщение готово!");
        }
        key_1 = false;
        if (ui->Key_A->text().length() == 0)
        {
            ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
            ui->Key_A_Valid->setText("Введите ключ (порядок перестановки столбцов, неповторяющиеся цифры от 1 до 7):");
            key_1 = true;
        }
        if (key_1 == false)
        {
        for (int i = 0; i < ui->Key_A->text().length() - 1; i++)
        {
            int count = 0;
            for (int j = i + 1; j < ui->Key_A->text().length(); j++)
                if (ui->Key_A->text()[i] == ui->Key_A->text()[j])
                    count++;
              if (count > 0)
              {
                  ui->Key_A->setStyleSheet("border: 1.5px solid red");
                  ui->Key_A_Valid->setText("Ключ: Цифры не должны повторяться!");
                  key_1 = true;
                  break;
              }
         }
        }
        if (key_1 == false)
        {
            if (ui->Key_A->text().length() < 2)
            {
                ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
                QString str_len = "Ключ: Кол-во цифр должно быть не меньше 2!";
                ui->Key_A_Valid->setText(str_len);;
                key_1 = true;
            }
            else
            {
                for (int i = 0; i < ui->Key_A->text().length(); i++)
                {
                    if (ui->Key_A->text().indexOf(QString::number(i + 1)) == -1)
                    {
                        ui->Key_A->setStyleSheet("border: 1.5px solid red");
                        QString str_len = "Ключ: Пропущена цифра '";
                        str_len += QString::number(i + 1);
                        str_len += "'!";
                        ui->Key_A_Valid->setText(str_len);;
                        key_1 = true;
                        break;
                    }
                }
                if (key_1 != true)
                {
                ui->Key_A->setStyleSheet("border: 1.5px solid green");
                ui->Key_A_Valid->setText("Ключ готов!");
                }
            }
        }
        if (message == false && key_1 == false)
        {
            ui->PB1->setEnabled(true);
            ui->PB2->setEnabled(true);
        }
        break;
    }
    case 2:
    {
    bool message = false;
    bool key_1 = true;
    bool key_2 = true;
    ui->PB1->setEnabled(false);
    ui->PB2->setEnabled(false);
    if (ui->Message->text().length() < 4)
    {
        ui->Message->setStyleSheet("border: 1.5px solid yellow");
        ui->Message_Valid->setText("Введите исходное сообщение (не менее 4-ех символов):");
        message = true;
    }
    else
    {
        ui->Message->setStyleSheet("border: 1.5px solid green");
        ui->Message_Valid->setText("Исходное сообщение готово!");
    }
    key_1 = false;
    if (ui->Key_A->text().length() == 0)
    {
        ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
        ui->Key_A_Valid->setText("Введите ключ 1 (порядок перестановки столбцов, неповторяющиеся цифры от 1 до 5):");
        key_1 = true;
    }
    if (key_1 == false)
    {
    for (int i = 0; i < ui->Key_A->text().length() - 1; i++)
    {
        int count = 0;
        for (int j = i + 1; j < ui->Key_A->text().length(); j++)
            if (ui->Key_A->text()[i] == ui->Key_A->text()[j])
                count++;
          if (count > 0)
          {
              ui->Key_A->setStyleSheet("border: 1.5px solid red");
              ui->Key_A_Valid->setText("Ключ 1: Цифры не должны повторяться!");
              key_1 = true;
              break;
          }
     }
    }
    if (key_1 == false)
    {
        if (ui->Key_A->text().length() < 2)
        {
            ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
            QString str_len = "Ключ 1: Кол-во цифр должно быть не меньше 2!";
            ui->Key_A_Valid->setText(str_len);;
            key_1 = true;
        }
        else
        {
            for (int i = 0; i < ui->Key_A->text().length(); i++)
            {
                if (ui->Key_A->text().indexOf(QString::number(i + 1)) == -1)
                {
                    ui->Key_A->setStyleSheet("border: 1.5px solid red");
                    QString str_len = "Ключ 1: Пропущена цифра '";
                    str_len += QString::number(i + 1);
                    str_len += "'!";
                    ui->Key_A_Valid->setText(str_len);;
                    key_1 = true;
                    break;
                }
            }
            if (key_1 != true)
            {
            ui->Key_A->setStyleSheet("border: 1.5px solid green");
            ui->Key_A_Valid->setText("Ключ 1 готов!");
            }
        }
    }
    key_2 = false;
    if (ui->Key_B->text().length() == 0)
    {
        ui->Key_B->setStyleSheet("border: 1.5px solid yellow");
        ui->Key_B_Valid->setText("Введите ключ 2 (порядок перестановки строк, неповторяющиеся цифры от 1 до 5):");
        key_2 = true;
    }
    if (key_2 == false)
    {
    for (int i = 0; i < ui->Key_B->text().length() - 1; i++)
    {
        int count = 0;
        for (int j = i + 1; j < ui->Key_B->text().length(); j++)
            if (ui->Key_B->text()[i] == ui->Key_B->text()[j])
                count++;
          if (count > 0)
          {
              ui->Key_B->setStyleSheet("border: 1.5px solid red");
              ui->Key_B_Valid->setText("Ключ 2: Цифры не должны повторяться!");
              key_2 = true;
              break;
          }
     }
    }
    if (key_2 == false)
    {
        if (ui->Key_B->text().length() < 2)
        {
            ui->Key_B->setStyleSheet("border: 1.5px solid yellow");
            QString str_len = "Ключ 2: Кол-во цифр должно быть не меньше 2";
            ui->Key_B_Valid->setText(str_len);;
            key_2 = true;
        }
        else
        {
            for (int i = 0; i < ui->Key_B->text().length(); i++)
            {
                if (ui->Key_B->text().indexOf(QString::number(i + 1)) == -1)
                {
                    ui->Key_B->setStyleSheet("border: 1.5px solid red");
                    QString str_len = "Ключ 2: Пропущена цифра '";
                    str_len += QString::number(i + 1);
                    str_len += "'!";
                    ui->Key_B_Valid->setText(str_len);;
                    key_2 = true;
                    break;
                }
            }
            if (key_2 != true)
            {
            ui->Key_B->setStyleSheet("border: 1.5px solid green");
            ui->Key_B_Valid->setText("Ключ 2 готов!");
            }
        }
    }
    if (message == false && key_1 == false && key_2 == false)
    {
        ui->PB1->setEnabled(true);
        ui->PB2->setEnabled(true);
    }
    break;
    }
    case 3:
    {
        bool message = false;
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        if (ui->Message->text().length() < 5)
        {
            ui->Message->setStyleSheet("border: 1.5px solid yellow");
            ui->Message_Valid->setText("Введите исходное сообщение (не менее 5-ти символов):");
            message = true;
        }
        else
        {
            ui->Message->setStyleSheet("border: 1.5px solid green");
            ui->Message_Valid->setText("Исходное сообщение готово!");
        }
        if (message == false)
        {
            ui->PB1->setEnabled(true);
            ui->PB2->setEnabled(true);
        }
        break;
    }
    case 4:
    {
        bool message = false;
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        if (ui->Message->text().length() < 6)
        {
            ui->Message->setStyleSheet("border: 1.5px solid yellow");
            ui->Message_Valid->setText("Введите исходное сообщение (не менее 6-ти символов, которыми могут являться строчные буквы русского алфавита, точка, запятая и пробел):");
            message = true;
        }
        else
        {
            ui->Message->setStyleSheet("border: 1.5px solid green");
            ui->Message_Valid->setText("Исходное сообщение готово!");
        }
        if (message == false)
        {
            ui->PB1->setEnabled(true);
            ui->PB2->setEnabled(true);
        }
        break;
    }
    case 5:
    {
        bool message = false;
        bool key_1 = true;
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        if (ui->Message->text().length() < 6)
        {
            ui->Message->setStyleSheet("border: 1.5px solid yellow");
            ui->Message_Valid->setText("Введите исходное сообщение (не менее 6-ти символов, которыми могут являться строчные буквы русского алфавита):");
            message = true;
        }
        else
        {
            ui->Message->setStyleSheet("border: 1.5px solid green");
            ui->Message_Valid->setText("Исходное сообщение готово!");
        }
        key_1 = false;
        if (ui->Key_A->text().length() == 0)
        {
            ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
            ui->Key_A_Valid->setText("Введите ключ (цифра):");
            key_1 = true;
        }
        if (key_1 != true)
        {
        ui->Key_A->setStyleSheet("border: 1.5px solid green");
        ui->Key_A_Valid->setText("Ключ готов!");
        }
        if (message == false && key_1 == false)
        {
            ui->PB1->setEnabled(true);
            ui->PB2->setEnabled(true);
        }
        break;
    }
    case 6:
    {
        bool message = false;
        bool key_1 = true;
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        if (ui->Message->text().length() < 6)
        {
            ui->Message->setStyleSheet("border: 1.5px solid yellow");
            ui->Message_Valid->setText("Введите исходное сообщение (не менее 6-ти символов, которыми могут являться строчные буквы русского алфавита):");
            message = true;
        }
        else
        {
            ui->Message->setStyleSheet("border: 1.5px solid green");
            ui->Message_Valid->setText("Исходное сообщение готово!");
        }
        key_1 = false;
        if (ui->Key_A->text().length() < 2)
        {
            ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
            ui->Key_A_Valid->setText("Введите ключ (не мнеее 2-ух цифр):");
            key_1 = true;
        }
        if (key_1 != true)
        {
        ui->Key_A->setStyleSheet("border: 1.5px solid green");
        ui->Key_A_Valid->setText("Ключ готов!");
        }
        if (message == false && key_1 == false)
        {
            ui->PB1->setEnabled(true);
            ui->PB2->setEnabled(true);
        }
        break;
    }
    case 7:
    {
        bool message = false;
        bool key_1 = true;
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        if (ui->Message->text().length() < 9)
        {
            ui->Message->setStyleSheet("border: 1.5px solid yellow");
            ui->Message_Valid->setText("Введите исходное сообщение (не менее 9-ти символов, которыми могут являться строчные буквы русского алфавита):");
            message = true;
        }
        else
        {
            ui->Message->setStyleSheet("border: 1.5px solid green");
            ui->Message_Valid->setText("Исходное сообщение готово!");
        }
        key_1 = false;
        if (ui->Key_A->text().length() < 3)
        {
            ui->Key_A->setStyleSheet("border: 1.5px solid yellow");
            ui->Key_A_Valid->setText("Введите ключ (не мнеее 3-ёх символов, которыми могут являться строчные буквы русского алфавита):");
            key_1 = true;
        }
        if (key_1 != true)
        {
        ui->Key_A->setStyleSheet("border: 1.5px solid green");
        ui->Key_A_Valid->setText("Ключ готов!");
        }
        if (message == false && key_1 == false)
        {
            ui->PB1->setEnabled(true);
            ui->PB2->setEnabled(true);
        }
        break;
    }
    case 8:
    {
        bool message = false;
        ui->PB1->setEnabled(false);
        ui->PB2->setEnabled(false);
        if (ui->Message->text().length() < 4)
        {
            ui->Message->setStyleSheet("border: 1.5px solid yellow");
            ui->Message_Valid->setText("Введите исходное сообщение (не менее 4-ех символов, которыми могут являться строчные буквы русского алфавита, точка, запятая и пробел):");
            message = true;
        }
        else
        {
            ui->Message->setStyleSheet("border: 1.5px solid green");
            ui->Message_Valid->setText("Исходное сообщение готово!");
        }
        if (message == false)
        {
            ui->PB1->setEnabled(true);
            ui->PB2->setEnabled(true);
        }
        break;
    }
    }
}

void MainWindow::on_clicked_1(){ // Шифрование (согласно значению выбранного индекса в выпадающем списке)
    switch(ui->Method->currentIndex()){
    case 0: // Метод Скитала
    {
        QString message((((ui->Message->text().length() / (ui->Key_A->text()[0].unicode() - 48))
                      + ((ui->Message->text().length() % (ui->Key_A->text()[0].unicode() - 48)) > 0 ? 1 : 0)))
                     * (ui->Key_A->text()[0].unicode() - 48), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            message[i] = ui->Message->text()[i];
        QString result(message);
        for (int i = 0; i < message.length(); i++)
            result[i] =  message[((i % (ui->Key_A->text()[0].unicode() - 48)) * (message.length() / (ui->Key_A->text()[0].unicode() - 48))) + (i / (ui->Key_A->text()[0].unicode() - 48))];
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(result);
        time_res->start();
        break;
    }
    case 1: // Метод с использованием шифрующих таблиц
    {
        QString message((((ui->Message->text().length() / ui->Key_A->text().length())
                      + ((ui->Message->text().length() % ui->Key_A->text().length()) > 0 ? 1 : 0)))
                     * ui->Key_A->text().length(), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            message[i] = ui->Message->text()[i];
        QString* table = new QString[ui->Key_A->text().length()];
        QString result(message);
        for (int i = 0; i < message.length(); i++)
            table[i / (message.length() / ui->Key_A->text().length())][i % (message.length() / ui->Key_A->text().length())] = message[i];//result[i];
        int *key_a = new int[ui->Key_A->text().length()];
        for (int i = 0; i < ui->Key_A->text().length(); i++)
            key_a[i] = 0;
        for (int i = 0; i < ui->Key_A->text().length(); i++)
            key_a[ui->Key_A->text().indexOf(QString::number(i + 1), 0)] = i + 1;
        for (int i = 0; i < ui->Key_A->text().length(); i++)
        {
            for (int j = 0; j < ui->Key_A->text().length() - i - 1; j++)
            {
                if (key_a[j] > key_a[j + 1])
                {
                    QString buff = table[j];
                    table[j] = table[j + 1];
                    table[j + 1] = buff;
                    int b = key_a[j];
                    key_a[j] = key_a[j + 1];
                    key_a[j + 1] = b;
                }
            }
        }
        for (int i = 0; i < message.length(); i++)
            message[i] = table[i / (message.length() / ui->Key_A->text().length())][i % (message.length() / ui->Key_A->text().length())];
        for (int i = 0; i < message.length(); i++)
            result[i] = message[((i % (ui->Key_A->text().length())) * (message.length() / ui->Key_A->text().length())) + (i / (ui->Key_A->text().length()))];
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(result);
        time_res->start();
        break;

    }
    case 2: // Метод с использованием двойной перестановки
    {
        QString message((ui->Message->text().length() / (ui->Key_A->text().length() * ui->Key_B->text().length())
                         + ((ui->Message->text().length() % (ui->Key_A->text().length() * ui->Key_B->text().length())) > 0 ? 1 : 0))
                        * (ui->Key_A->text().length() * ui->Key_B->text().length()), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            message[i] = ui->Message->text()[i];
    QString result(message.length());
    int *key_a = new int[ui->Key_A->text().length()];
    for (int i = 0; i < ui->Key_A->text().length(); i++)
        key_a[i] = 0;
    int* key_b = new int[ui->Key_B->text().length()];
    for (int i = 0; i < ui->Key_A->text().length(); i++)
        key_a[ui->Key_A->text().indexOf(QString::number(i + 1), 0)] = i + 1;
    for (int i = 0; i < ui->Key_B->text().length(); i++)
        key_b[ui->Key_B->text().indexOf(QString::number(i + 1), 0)] = i + 1;
    for (int i = 0; i < message.length(); i++)
        result[((i / (ui->Key_B->text().length() * ui->Key_A->text().length())) * (ui->Key_B->text().length() * ui->Key_A->text().length()))
                + ((key_b[(i / ui->Key_A->text().length()) % ui->Key_B->text().length()] - 1) * ui->Key_A->text().length())
                + key_a[i % ui->Key_A->text().length()] - 1] = message[i];
    ui->Result->setStyleSheet("border: 1.5px solid green");
    ui->Result->setText(result);
    time_res->start();
    break;
    }
    case 3: // Метод с использованием магического квадрата
    {
        QString message(25, (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            message[table_4[i / 5][i % 5] - 1] = ui->Message->text()[i];
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    case 4: // Метод с использованием полибианскогого квадрата
    {
        QString message(ui->Message->text().length(), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            for (int j = 0; j < 6; j++)
                for (int k = 0; k < 6; k++)
                    if (ui->Message->text() [i] == table_5[j][k])
                    {
                        message[i] = table_5[(j + 1) % 6][k];
                        j = 6;
                        break;
                    }
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    case 5: // Метод Цезаря
    {
        QString message(ui->Message->text().length(), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            for (int j = 0; j < 33; j++)
                        if (alpha[j] == (QChar)(ui->Message->text()[i]))
                        {
                            message[i] = alpha[(j + (ui->Key_A->text()[0].unicode() - 48)) % 33];
                            break;
                        }
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    case 6: // Метод Гронсфельда
    {
        QString message(ui->Message->text().length(), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            for (int j = 0; j < 33; j++)
                        if (alpha[j] == (QChar)(ui->Message->text()[i]))
                        {
                            message[i] = alpha[(j + (ui->Key_A->text()[i % ui->Key_A->text().length()].unicode() - 48)) % 33];
                            break;
                        }
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    case 7: // Метод Виженера
    {
        QString message(ui->Message->text().length(), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            message[i] = alpha[(alpha.indexOf(ui->Message->text()[i]) + alpha.indexOf(ui->Key_A->text()[i % ui->Key_A->text().length()])) % 33];
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    case 8: // Метод Уитстона
    {
        int row1, col1, row2, col2;
        QString message(ui->Message->text().length(), (QChar)('*'));
        for (int i = 0; i < (ui->Message->text().length() / 2); i++)
        {
            bool b1 = true, b2 = true;
            for (int j = 0; j < 7; j++)
                for (int k = 0; k < 5; k++)
                {
                    if (ui->Message->text()[2 * i] == table_9a[j][k])
                    {
                        row1 = j;
                        col2 = k;
                        b1 = false;
                    }
                    if (ui->Message->text()[(2 * i) + 1] == table_9b[j][k])
                    {
                        row2 = j;
                        col1 = k;
                        b2 = false;
                    }
                    if (b1 == false && b2 == false)
                    {
                        j = 6;
                        k = 4;
                        break;
                    }
                }
            if (row1 == row2)
            {
                message[(2 * i)] = table_9b[row1][col2];
                message[(2 * i) + 1] = table_9a[row2][col1];
            }
            else
            {
                message[2 * i] = table_9b[row1][col1];
                message[(2 * i) + 1] = table_9a[row2][col2];
            }
        }
        // В случае если кол-во символов в исходном сеебщении нечетное
        // Вычесляются координаты (позиции в строке и столбце первой таблицы) последнего символа
        // Берется символ из второй таблицы согласно найденным координатам
        if (ui->Message->text().length() % 2 != 0)
        {
            int row, col;
            for (int j = 0; j < 7; j++)
                for (int k = 0; k < 5; k++)
                {
                    if (ui->Message->text()[ui->Message->text().length() - 1] == table_9a[j][k])
                    {
                        row = j;
                        col = k;
                        message[ui->Message->text().length() - 1] = table_9b[j][k];
                        j = 6;
                        k = 4;
                    }
                }
        }
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    }
}

void MainWindow::on_clicked_2(){ // Дешифрование (согласно значению выбранного индекса в выпадающем списке)
    switch(ui->Method->currentIndex()){
    case 0: // Метод Скитала
    {
        QString message((((ui->Message->text().length() / (ui->Key_A->text()[0].unicode() - 48))
                      + ((ui->Message->text().length() % (ui->Key_A->text()[0].unicode() - 48)) > 0 ? 1 : 0)))
                     * (ui->Key_A->text()[0].unicode() - 48), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            message[i] = ui->Message->text()[i];
        QString result(message);
        for (int i = 0; i < message.length(); i++)
            result[i] =  message[((i % (message.length() / (ui->Key_A->text()[0].unicode() - 48))) * ((ui->Key_A->text()[0].unicode() - 48))) + (i / (message.length() / (ui->Key_A->text()[0].unicode() - 48)))];
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(result);
        time_res->start();
        break;
    }
    case 1: // Метод с использованием шифрующих таблиц
    {
        QString message((((ui->Message->text().length() / ui->Key_A->text().length())
                      + ((ui->Message->text().length() % ui->Key_A->text().length()) > 0 ? 1 : 0)))
                     * ui->Key_A->text().length(), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            message[i] = ui->Message->text()[i];
        QString result(message);
        for (int i = 0; i < message.length(); i++)
            result[i] = message[((i % (message.length() / ui->Key_A->text().length())) * (ui->Key_A->text().length())) + (i / (message.length() / ui->Key_A->text().length()))];//table_2[i / (message.length() / ui->Key_A->text().length())][i % (message.length() / ui->Key_A->text().length())]
        QString* table = new QString[ui->Key_A->text().length()];
        for (int i = 0; i < message.length(); i++)
            table[i / (message.length() / ui->Key_A->text().length())][i % (message.length() / ui->Key_A->text().length())] = result[i];//message[i] = table_2[i / (message.length() / ui->Key_A->text().length())][i % (message.length() / ui->Key_A->text().length())];//[i % (message.length() / ui->Key_A->text().length())][i / ui->Key_A->text().length()];
        int *key_a = new int[ui->Key_A->text().length()];
        for (int i = 0; i < ui->Key_A->text().length(); i++)
            key_a[i] = 0;
        // Существует несколько алгоритмов данного дешифрования, мной был реализован следующий
        // При шифровании одна из задач заключалась в перестановке столбцов согласно заданному цифровому ключу
        // В дешифровании же необходимо получить из исходного ключа такой, согласно которому перестановка стобцов дала бы первоначальный (дешифрованный) рзультат
        // Процесс дешифрования обратен шифрованию
        // Значит и процесс получения такого ключа будет обратен процессу считывания исходного ключа из области "Ключ"
        // В процессе считывания основного ключа мы размещали параметр от 0 до n согласно его позиции в области "Ключ"
        // Значит в обратном процессе параметр от 0 до n будем размещать в согласно текущему значению в исходном ключе
        // Под текущим значением в исходном ключе понимается значение согласно позиции, равной текущему значению параметра
        // Аналогичный лагоритм применяется также в дешифровании двойной перестановкой и магическим квадратом
        for (int i = 0; i < ui->Key_A->text().length(); i++)
            key_a[(int)(ui->Key_A->text()[i].unicode()) - 48 - 1] = i + 1;
        for (int i = 0; i < ui->Key_A->text().length(); i++)
        {
            for (int j = 0; j < ui->Key_A->text().length() - i - 1; j++)
            {
                if (key_a[j] > key_a[j + 1])
                {
                    QString buff = table[j];
                    table[j] = table[j + 1];
                    table[j + 1] = buff;
                    int b = key_a[j];
                    key_a[j] = key_a[j + 1];
                    key_a[j + 1] = b;
                }
            }
        }
        for (int i = 0; i < message.length(); i++)
            message[i] = table[i / (message.length() / ui->Key_A->text().length())][i % (message.length() / ui->Key_A->text().length())];// = message[i];//result[i];
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    case 2: // Метод с использованием двойной перестановки
    {
    QString message((ui->Message->text().length() / (ui->Key_A->text().length() * ui->Key_B->text().length())
                     + ((ui->Message->text().length() % (ui->Key_A->text().length() * ui->Key_B->text().length())) > 0 ? 1 : 0))
                    * (ui->Key_A->text().length() * ui->Key_B->text().length()), (QChar)('*'));
    for (int i = 0; i < ui->Message->text().length(); i++)
        message[i] = ui->Message->text()[i];
QString result(message.length());
int *key_a = new int[ui->Key_A->text().length()];
for (int i = 0; i < ui->Key_A->text().length(); i++)
    key_a[i] = 0;
int* key_b = new int[ui->Key_B->text().length()];
for (int i = 0; i < ui->Key_A->text().length(); i++)
    key_a[ui->Key_A->text().indexOf(QString::number(i + 1), 0)] = i + 1;
for (int i = 0; i < ui->Key_B->text().length(); i++)
    key_b[ui->Key_B->text().indexOf(QString::number(i + 1), 0)] = i + 1;
for (int i = 0; i < message.length(); i++)
    result[i] = message[((i / (ui->Key_B->text().length() * ui->Key_A->text().length())) * (ui->Key_B->text().length() * ui->Key_A->text().length()))
            + ((key_b[(i / ui->Key_A->text().length()) % ui->Key_B->text().length()] - 1) * ui->Key_A->text().length())//((key_b[(i % (ui->Key_A->text().length() * ui->Key_B->text().length()))/ ui->Key_B->text().length()] - 1)* keyb.length())
            + key_a[i % ui->Key_A->text().length()] - 1];
    ui->Result->setStyleSheet("border: 1.5px solid green");
    ui->Result->setText(result);
    time_res->start();
    break;
    }
    case 3: // Метод с использованием магического квадрата
    {
        QString message(25, (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            for (int j = 0; j < 5; j++)
                for (int k = 0; k < 5; k++)
                    if (table_4[j][k] == i + 1)
                    {
                        message[(j * 5) + k] = ui->Message->text()[i];
                        j = 4;
                        break;
                    }
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    case 4: // Метод с использованием полиианского квадрата
    {
        QString message(ui->Message->text().length(), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            for (int j = 0; j < 6; j++)
                for (int k = 0; k < 6; k++)
                    if (ui->Message->text() [i] == table_5[j][k])
                    {
                        message[i] = table_5[(6 + (j - 1)) % 6][k];
                        j = 5;
                        break;
                    }
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    case 5: // Метод Цезаря
    {
        QString message(ui->Message->text().length(), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            for (int j = 0; j < 33; j++)
                        if (alpha[j] == (QChar)(ui->Message->text()[i]))
                        {
                            // Прибавка к найденной позиции числа 33 гарантирует, что мы не получим отрицательных чисел
                            // Аналогичный алгоритм применяется также в дешифровании Гронсфельда и Виженера
                            message[i] = alpha[(33 + j - (ui->Key_A->text()[0].unicode() - 48)) % 33];
                            break;
                        }
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    case 6: // Метод Гронсфельда
    {
        QString message(ui->Message->text().length(), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            for (int j = 0; j < 33; j++)
                        if (alpha[j] == (QChar)(ui->Message->text()[i]))
                        {
                            message[i] = alpha[(33 + j - (ui->Key_A->text()[i % ui->Key_A->text().length()].unicode() - 48)) % 33];
                            break;
                        }
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    case 7: // Метод Виженера
    {
        QString message(ui->Message->text().length(), (QChar)('*'));
        for (int i = 0; i < ui->Message->text().length(); i++)
            message[i] = alpha[(33 + alpha.indexOf(ui->Message->text()[i]) - alpha.indexOf(ui->Key_A->text()[i % ui->Key_A->text().length()])) % 33];
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    case 8: // Метод Уитстона
    {
        int row1, col1, row2, col2;
        QString message(ui->Message->text().length(), (QChar)('*'));
        for (int i = 0; i < (ui->Message->text().length() / 2); i++)
        {
            bool b1 = true, b2 = true;
            for (int j = 0; j < 7; j++)
                for (int k = 0; k < 5; k++)
                {
                    if (ui->Message->text()[2 * i] == table_9b[j][k])
                    {
                        row1 = j;
                        col2 = k;
                        b1 = false;
                    }
                    if (ui->Message->text()[(2 * i) + 1] == table_9a[j][k])
                    {
                        row2 = j;
                        col1 = k;
                        b2 = false;
                    }
                    if (b1 == false && b2 == false)
                    {
                        j = 6;
                        k = 4;
                        break;
                    }
                }
            if (row1 == row2)
            {
                message[(2 * i)] = table_9a[row1][col2];
                message[(2 * i) + 1] = table_9b[row2][col1];
            }
            else
            {
                message[2 * i] = table_9a[row1][col1];
                message[(2 * i) + 1] = table_9b[row2][col2];
            }
        }
        // В случае если кол-во символов в исходном сеебщении нечетное
        // Вычесляются координаты (позиции в строке и столбце второй таблицы) последнего символа
        // Берется символ из первой таблицы согласно найденным координатам
        if (ui->Message->text().length() % 2 != 0)
        {
            int row, col;
            for (int j = 0; j < 7; j++)
                for (int k = 0; k < 5; k++)
                {
                    if (ui->Message->text()[ui->Message->text().length() - 1] == table_9b[j][k])
                    {
                        row = j;
                        col = k;
                        message[ui->Message->text().length() - 1] = table_9a[j][k];
                        j = 6;
                        k = 4;
                    }
                }
        }
        ui->Result->setStyleSheet("border: 1.5px solid green");
        ui->Result->setText(message);
        time_res->start();
        break;
    }
    }
}

void MainWindow::update_res(){ // Подсвечивание области "Результат" зеленым цветом на 1.5 секунды
     ui->Result->setStyleSheet("border: 1.5px solid grey");
}
