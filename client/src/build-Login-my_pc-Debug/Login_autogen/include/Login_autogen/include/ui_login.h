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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *centralwidget;
    QPushButton *button_join;
    QLineEdit *dato_ip;
    QLineEdit *dato_puerto;
    QPushButton *button_create;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Login->sizePolicy().hasHeightForWidth());
        Login->setSizePolicy(sizePolicy);
        Login->setMaximumSize(QSize(800, 600));
        Login->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(Login);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        button_join = new QPushButton(centralwidget);
        button_join->setObjectName(QString::fromUtf8("button_join"));
        button_join->setGeometry(QRect(600, 530, 171, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        button_join->setFont(font);
        dato_ip = new QLineEdit(centralwidget);
        dato_ip->setObjectName(QString::fromUtf8("dato_ip"));
        dato_ip->setGeometry(QRect(600, 380, 171, 41));
        dato_puerto = new QLineEdit(centralwidget);
        dato_puerto->setObjectName(QString::fromUtf8("dato_puerto"));
        dato_puerto->setGeometry(QRect(600, 430, 171, 41));
        button_create = new QPushButton(centralwidget);
        button_create->setObjectName(QString::fromUtf8("button_create"));
        button_create->setGeometry(QRect(600, 480, 171, 41));
        button_create->setFont(font);
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
        button_join->setText(QApplication::translate("Login", "JOIN MATCH", nullptr));
        button_create->setText(QApplication::translate("Login", "CREATE MATCH", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
