/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *centralwidget;
    QPushButton *boton_continuar;
    QLineEdit *dato_ip;
    QLineEdit *dato_puerto;
    QLineEdit *dato_nombre;
    QLabel *label_nombre;
    QLabel *label_puerto;
    QLabel *label_ip;
    QLabel *label_titulo;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *label_partidas;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(800, 600);
        Login->setMaximumSize(QSize(800, 600));
        centralwidget = new QWidget(Login);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        boton_continuar = new QPushButton(centralwidget);
        boton_continuar->setObjectName(QString::fromUtf8("boton_continuar"));
        boton_continuar->setGeometry(QRect(230, 480, 251, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        boton_continuar->setFont(font);
        dato_ip = new QLineEdit(centralwidget);
        dato_ip->setObjectName(QString::fromUtf8("dato_ip"));
        dato_ip->setGeometry(QRect(250, 130, 331, 31));
        dato_puerto = new QLineEdit(centralwidget);
        dato_puerto->setObjectName(QString::fromUtf8("dato_puerto"));
        dato_puerto->setGeometry(QRect(250, 180, 331, 31));
        dato_nombre = new QLineEdit(centralwidget);
        dato_nombre->setObjectName(QString::fromUtf8("dato_nombre"));
        dato_nombre->setGeometry(QRect(250, 80, 331, 31));
        label_nombre = new QLabel(centralwidget);
        label_nombre->setObjectName(QString::fromUtf8("label_nombre"));
        label_nombre->setGeometry(QRect(90, 70, 151, 61));
        QFont font1;
        font1.setPointSize(20);
        label_nombre->setFont(font1);
        label_puerto = new QLabel(centralwidget);
        label_puerto->setObjectName(QString::fromUtf8("label_puerto"));
        label_puerto->setGeometry(QRect(90, 170, 161, 51));
        label_puerto->setFont(font1);
        label_ip = new QLabel(centralwidget);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));
        label_ip->setGeometry(QRect(90, 130, 101, 31));
        label_ip->setFont(font1);
        label_titulo = new QLabel(centralwidget);
        label_titulo->setObjectName(QString::fromUtf8("label_titulo"));
        label_titulo->setGeometry(QRect(190, -30, 341, 111));
        QFont font2;
        font2.setFamily(QString::fromUtf8("URW Bookman"));
        font2.setPointSize(32);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        label_titulo->setFont(font2);
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(50, 270, 591, 201));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 575, 199));
        scrollArea->setWidget(scrollAreaWidgetContents);
        label_partidas = new QLabel(centralwidget);
        label_partidas->setObjectName(QString::fromUtf8("label_partidas"));
        label_partidas->setGeometry(QRect(50, 230, 231, 31));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font3.setPointSize(17);
        font3.setBold(true);
        font3.setWeight(75);
        label_partidas->setFont(font3);
        Login->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Login);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        Login->setMenuBar(menubar);
        statusbar = new QStatusBar(Login);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Login->setStatusBar(statusbar);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QMainWindow *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", nullptr));
        boton_continuar->setText(QApplication::translate("Login", "CONTINUAR", nullptr));
        label_nombre->setText(QApplication::translate("Login", "NOMBRE :", nullptr));
        label_puerto->setText(QApplication::translate("Login", "PUERTO : ", nullptr));
        label_ip->setText(QApplication::translate("Login", "TU IP :", nullptr));
        label_titulo->setText(QApplication::translate("Login", "WOLFESTEIN", nullptr));
        label_partidas->setText(QApplication::translate("Login", "Partidas Disponibles :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
