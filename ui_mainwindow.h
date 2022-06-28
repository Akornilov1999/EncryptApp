/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *Result_Valid;
    QPushButton *PB2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *PB1;
    QComboBox *Method;
    QSpacerItem *verticalSpacer_4;
    QLabel *Picture;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer;
    QLineEdit *Message;
    QLineEdit *Key_B;
    QLabel *Message_Valid;
    QLabel *Key_B_Valid;
    QLabel *Key_A_Valid;
    QLineEdit *Result;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *Key_A;
    QLabel *Method_Valid;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(674, 713);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(8);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("Images/icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setFont(font);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Result_Valid = new QLabel(centralwidget);
        Result_Valid->setObjectName(QString::fromUtf8("Result_Valid"));
        Result_Valid->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Result_Valid->sizePolicy().hasHeightForWidth());
        Result_Valid->setSizePolicy(sizePolicy2);
        Result_Valid->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(Result_Valid, 13, 0, 1, 2);

        PB2 = new QPushButton(centralwidget);
        PB2->setObjectName(QString::fromUtf8("PB2"));
        QSizePolicy sizePolicy3(QSizePolicy::Ignored, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(PB2->sizePolicy().hasHeightForWidth());
        PB2->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(PB2, 16, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 6, 0, 1, 1);

        PB1 = new QPushButton(centralwidget);
        PB1->setObjectName(QString::fromUtf8("PB1"));
        sizePolicy3.setHeightForWidth(PB1->sizePolicy().hasHeightForWidth());
        PB1->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(PB1, 16, 0, 1, 1);

        Method = new QComboBox(centralwidget);
        Method->setObjectName(QString::fromUtf8("Method"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(Method->sizePolicy().hasHeightForWidth());
        Method->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(Method, 2, 0, 1, 2);

        verticalSpacer_4 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_4, 12, 0, 1, 1);

        Picture = new QLabel(centralwidget);
        Picture->setObjectName(QString::fromUtf8("Picture"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(Picture->sizePolicy().hasHeightForWidth());
        Picture->setSizePolicy(sizePolicy5);
        Picture->setMinimumSize(QSize(626, 245));
        Picture->setScaledContents(true);

        gridLayout->addWidget(Picture, 0, 0, 1, 2);

        verticalSpacer_5 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_5, 15, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        Message = new QLineEdit(centralwidget);
        Message->setObjectName(QString::fromUtf8("Message"));
        sizePolicy4.setHeightForWidth(Message->sizePolicy().hasHeightForWidth());
        Message->setSizePolicy(sizePolicy4);
        Message->setAcceptDrops(true);
        Message->setAutoFillBackground(false);
        Message->setEchoMode(QLineEdit::Normal);
        Message->setReadOnly(false);
        Message->setClearButtonEnabled(true);

        gridLayout->addWidget(Message, 5, 0, 1, 2);

        Key_B = new QLineEdit(centralwidget);
        Key_B->setObjectName(QString::fromUtf8("Key_B"));
        sizePolicy4.setHeightForWidth(Key_B->sizePolicy().hasHeightForWidth());
        Key_B->setSizePolicy(sizePolicy4);
        Key_B->setClearButtonEnabled(true);

        gridLayout->addWidget(Key_B, 11, 0, 1, 2);

        Message_Valid = new QLabel(centralwidget);
        Message_Valid->setObjectName(QString::fromUtf8("Message_Valid"));
        sizePolicy2.setHeightForWidth(Message_Valid->sizePolicy().hasHeightForWidth());
        Message_Valid->setSizePolicy(sizePolicy2);
        Message_Valid->setLayoutDirection(Qt::LeftToRight);
        Message_Valid->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(Message_Valid, 4, 0, 1, 2);

        Key_B_Valid = new QLabel(centralwidget);
        Key_B_Valid->setObjectName(QString::fromUtf8("Key_B_Valid"));
        sizePolicy2.setHeightForWidth(Key_B_Valid->sizePolicy().hasHeightForWidth());
        Key_B_Valid->setSizePolicy(sizePolicy2);
        Key_B_Valid->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(Key_B_Valid, 10, 0, 1, 2);

        Key_A_Valid = new QLabel(centralwidget);
        Key_A_Valid->setObjectName(QString::fromUtf8("Key_A_Valid"));
        sizePolicy2.setHeightForWidth(Key_A_Valid->sizePolicy().hasHeightForWidth());
        Key_A_Valid->setSizePolicy(sizePolicy2);
        Key_A_Valid->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(Key_A_Valid, 7, 0, 1, 2);

        Result = new QLineEdit(centralwidget);
        Result->setObjectName(QString::fromUtf8("Result"));
        Result->setEnabled(true);
        sizePolicy4.setHeightForWidth(Result->sizePolicy().hasHeightForWidth());
        Result->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(Result, 14, 0, 1, 2);

        verticalSpacer_3 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 9, 0, 1, 1);

        Key_A = new QLineEdit(centralwidget);
        Key_A->setObjectName(QString::fromUtf8("Key_A"));
        sizePolicy4.setHeightForWidth(Key_A->sizePolicy().hasHeightForWidth());
        Key_A->setSizePolicy(sizePolicy4);
        Key_A->setClearButtonEnabled(true);

        gridLayout->addWidget(Key_A, 8, 0, 1, 2);

        Method_Valid = new QLabel(centralwidget);
        Method_Valid->setObjectName(QString::fromUtf8("Method_Valid"));
        sizePolicy2.setHeightForWidth(Method_Valid->sizePolicy().hasHeightForWidth());
        Method_Valid->setSizePolicy(sizePolicy2);
        Method_Valid->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(Method_Valid, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 674, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\321\210\320\270\321\204\321\200\321\203\320\271\320\272\320\260", nullptr));
        Result_Valid->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
        PB2->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\210\320\270\321\204\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        PB1->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\321\210\320\270\321\204\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        Picture->setText(QString());
        Message_Valid->setText(QString());
        Key_B_Valid->setText(QString());
        Key_A_Valid->setText(QString());
        Method_Valid->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\274\320\265\321\202\320\276\320\264 \321\210\320\270\321\204\321\200\320\276\320\262\320\260\320\275\320\270\321\217:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
